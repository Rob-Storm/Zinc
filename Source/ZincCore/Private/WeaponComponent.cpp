#include "WeaponComponent.h"
#include "ZincCharacter.h"
#include "Damageable.h"
#include "ProcessChecker.h"
#include "WeaponProjectile.h"
#include "WeaponModel.h"
#include "Camera/CameraComponent.h"

#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"

void UWeaponComponent::SetCurrentWeapon(UWeaponData* NewWeapon)
{
	// stop the reload timer handle so the player can't cheese the reload delay
	GetWorld()->GetTimerManager().ClearTimer(ReloadDelayHandle);
	CurrentWeapon = NewWeapon;

	if(WeaponActor)
	{
		WeaponActor->Destroy();
	}

	if(!CurrentWeapon)
	{
		OnWeaponChanged.Broadcast(nullptr, 0, 0);
		return;
	}

	AttachWeaponActor();

	int32 CurrentAmmo = CurrentAmmoMap.FindRef(CurrentWeapon);
	int32 ReserveAmmo = ReserveAmmoMap.FindRef(CurrentWeapon->AmmoType);

	OnWeaponChanged.Broadcast(CurrentWeapon, CurrentAmmo, ReserveAmmo);
}

void UWeaponComponent::TryFire()
{
	if(!CurrentWeapon)
	{
		return;
	}
	
	if(!CanShoot)
	{
		return;
	}

	if(CurrentWeapon->WeaponType == EWeaponType::Melee)
	{
		FireMelee();

		return;
	}

	if(!CurrentAmmoMap.Contains(CurrentWeapon))
	{
		CurrentAmmoMap.Add(CurrentWeapon, 0);

		if(CanReload())
		{
			UGameplayStatics::PlaySoundAtLocation(this, CurrentWeapon->ReloadSound, GetOwner()->GetActorLocation());

			GetWorld()->GetTimerManager().SetTimer(ReloadDelayHandle, this, &UWeaponComponent::Reload, CurrentWeapon->FireRate, false, -1.f);
		}

		return;
	}

	int32 AmmoCount = CurrentAmmoMap[CurrentWeapon];

	if(AmmoCount == 0)
	{
		if(CanReload())
		{
			GetWorld()->GetTimerManager().SetTimer(ReloadDelayHandle, this, &UWeaponComponent::Reload, CurrentWeapon->FireRate, false, -1.f);
		}
		else
		{
			UGameplayStatics::PlaySoundAtLocation(this, DryFireSound, GetOwner()->GetActorLocation());
		}
	}
	else
	{
		AmmoCount--;
		CurrentAmmoMap.Add(CurrentWeapon, AmmoCount);
		OnCurrentAmmoChanged.Broadcast(AmmoCount);

		Fire();
		WeaponActor->PlayEffects(CurrentWeapon->FireEffect);

		OnShoot.Broadcast(CurrentWeapon, CurrentAmmoMap[CurrentWeapon]);
	}

	CanShoot = false;

	GetWorld()->GetTimerManager().SetTimer(ShootDelayHandle, this, &UWeaponComponent::ResetShoot, CurrentWeapon->FireRate, false, -1.f);

}

void UWeaponComponent::Fire()
{	
	switch(CurrentWeapon->WeaponType)
	{
		case EWeaponType::Hitscan:
			FireHitscan();
			break;
		case EWeaponType::Projectile:
			FireProjectile();
			break;
	};
}

void UWeaponComponent::FireHitscan()
{
	FVector HitLocation;
	FRotator HitRotation;
	AActor* DamageActor;

	UGameplayStatics::PlaySoundAtLocation(this, CurrentWeapon->UseSound, GetOwner()->GetActorLocation());

	if(!FireTrace(UProcessChecker::IsEditor(), DamageActor, HitLocation, HitRotation))
	{
		return;
	}

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetOwner(), SurfaceHitEffect, HitLocation, HitRotation);

	if(!DamageActor)
	{
		return;
	}

	AZincCharacter* OwningCharacter = Cast<AZincCharacter>(GetOwner());

	IDamageable::Execute_Damage(DamageActor, CurrentWeapon->Damage, CurrentWeapon->AmmoType->DamageType, OwningCharacter);
}

void UWeaponComponent::FireProjectile()
{
	FVector Location(GetComponentLocation());
	FRotator Rotation(GetComponentRotation());

	FTransform SpawnTransform(Rotation, Location);

	FActorSpawnParameters SpawnInfo;

	SpawnInfo.Owner = GetOwner();
	SpawnInfo.Instigator = Cast<APawn>(GetOwner());

	AWeaponProjectile* SpawnedActor = GetWorld()->SpawnActorDeferred<AWeaponProjectile>(CurrentWeapon->ProjectileClass, SpawnTransform, SpawnInfo.Owner, SpawnInfo.Instigator);

	if(SpawnedActor)
	{
		SpawnedActor->WeaponData = CurrentWeapon;

		UGameplayStatics::FinishSpawningActor(SpawnedActor, SpawnTransform);
	}

	UGameplayStatics::PlaySoundAtLocation(this, CurrentWeapon->UseSound, GetOwner()->GetActorLocation());
}

void UWeaponComponent::FireMelee()
{
	// Might change later, just need something for now

	FireHitscan();

	CanShoot = false;

	GetWorld()->GetTimerManager().SetTimer(ShootDelayHandle, this, &UWeaponComponent::ResetShoot, CurrentWeapon->FireRate, false, -1.f);
}

void UWeaponComponent::Reload()
{
	UAmmoType* CurrentAmmoType = CurrentWeapon->AmmoType;

	if(!ReserveAmmoMap.Contains(CurrentAmmoType))
	{
		return;
	}

	int32 CurrentAmmo = CurrentAmmoMap[CurrentWeapon];
	int32 ReserveAmmo = ReserveAmmoMap[CurrentWeapon->AmmoType];

	if(ReserveAmmo <= CurrentWeapon->MagazineSize - CurrentAmmo)
	{
		CurrentAmmo += ReserveAmmo;
		ReserveAmmo = 0;

		ReserveAmmoMap.Add(CurrentAmmoType, 0);
		CurrentAmmoMap.Add(CurrentWeapon, CurrentAmmo);
	}
	else
	{
		ReserveAmmo -= (CurrentWeapon->MagazineSize - CurrentAmmo);

		ReserveAmmoMap.Add(CurrentAmmoType, ReserveAmmo);
		CurrentAmmoMap.Add(CurrentWeapon, CurrentWeapon->MagazineSize);
	}

	OnReload.Broadcast(CurrentAmmoMap[CurrentWeapon], ReserveAmmoMap[CurrentWeapon->AmmoType]);
}

void UWeaponComponent::AddAmmo(UAmmoType* Ammo, int32 Amount)
{
	if(!ReserveAmmoMap.Contains(Ammo))
	{
		ReserveAmmoMap.Add(Ammo, Amount);
		OnReserveAmmoChanged.Broadcast(Amount);

		return;
	}

	int32 AmmoCount = ReserveAmmoMap[Ammo];

	AmmoCount += Amount;

	ReserveAmmoMap.Add(Ammo, AmmoCount);

	OnReserveAmmoChanged.Broadcast(AmmoCount);
}

void UWeaponComponent::AddCurrentWeaponAmmo(UWeaponData* Weapon, int32 Amount)
{
	if(!CurrentAmmoMap.Contains(Weapon))
	{
		CurrentAmmoMap.Add(Weapon, Amount);
		OnCurrentAmmoChanged.Broadcast(Amount);

		return;
	}

	int32 AmmoCount = CurrentAmmoMap[Weapon];

	AmmoCount += Amount;

	CurrentAmmoMap.Add(Weapon, AmmoCount);
	OnCurrentAmmoChanged.Broadcast(AmmoCount);
}

bool UWeaponComponent::FireTrace(bool DebugTrace, AActor* &OutHitActor, FVector &OutHitLocation, FRotator &OutHitRotation)
{

	/* Ideas:
 	 *
 	 * Hit effects for surfaces (e.g. decals, niagara, etc.)
 	 * AI Sound detection?
 	 *
 	 */

	if(!CurrentWeapon)
	{
		return false;
	}

	FVector StartLocation;
	FVector EndLocation;
	FVector ForwardVector;
	FHitResult Result;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(GetOwner());
	FCollisionResponseParams ResponseParams;

	if(DebugTrace)
	{
		FName TraceTag("ShootTraceTag");
		GetWorld()->DebugDrawTraceTag = TraceTag;

		QueryParams.TraceTag = TraceTag;
	}

	if(UseCameraForTrace)
	{
		UCameraComponent* Camera = GetOwner()->FindComponentByClass<UCameraComponent>();
		StartLocation = Camera->GetComponentLocation();
		ForwardVector = Camera->GetForwardVector();
	}
	else
	{
		StartLocation = this->GetComponentLocation();
		ForwardVector = this->GetForwardVector();
	}

	EndLocation = StartLocation + (ForwardVector * CurrentWeapon->Range);

	bool HitAnything = GetWorld()->LineTraceSingleByChannel(Result, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility, QueryParams, ResponseParams);

	OutHitLocation = Result.Location;
	OutHitRotation = Result.Normal.GetSafeNormal().Rotation();

	IDamageable* DamageInterface = Cast<IDamageable>(Result.GetActor());
	if(DamageInterface)
	{
		OutHitActor = Result.GetActor();
	}
	else
	{
		OutHitActor = nullptr;
	}

	return HitAnything;
}

void UWeaponComponent::AttachWeaponActor()
{
	if(!CurrentWeapon->WeaponActorClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("WeaponActorClass not set in Current Weapon!"))

		return;
	}

	FVector Location(GetComponentLocation());
	FRotator Rotation(GetComponentRotation());

	FTransform SpawnTransform(Rotation, Location);

	FActorSpawnParameters SpawnInfo;

	SpawnInfo.Owner = GetOwner();
	SpawnInfo.Instigator = Cast<APawn>(GetOwner());

	WeaponActor = GetWorld()->SpawnActor<AWeaponModel>(CurrentWeapon->WeaponActorClass, SpawnTransform, SpawnInfo);

	FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules::SnapToTargetNotIncludingScale;
	AttachmentRules.bWeldSimulatedBodies = true;

	WeaponActor->AttachToComponent(this, AttachmentRules);
}