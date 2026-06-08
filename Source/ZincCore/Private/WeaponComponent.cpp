#include "WeaponComponent.h"
#include "ZincCharacter.h"
#include "Damageable.h"
#include "ProcessChecker.h"
#include "WeaponProjectile.h"

#include "Kismet/GameplayStatics.h"

void UWeaponComponent::TryFire()
{
	if(!CurrentWeapon)
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
			Reload();
		}

		return;
	}

	int32 AmmoCount = CurrentAmmoMap[CurrentWeapon];

	if(AmmoCount == 0)
	{
		if(CanReload())
		{
			Reload();
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

		Fire();

		OnShoot.Broadcast(CurrentWeapon, CurrentAmmoMap[CurrentWeapon]);
	}
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
	AActor* DamageActor = FireTrace(UProcessChecker::IsEditor());

	UGameplayStatics::PlaySoundAtLocation(this, CurrentWeapon->UseSound, GetOwner()->GetActorLocation());

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

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Current partially reloaded"));
	}
	else
	{
		ReserveAmmo -= (CurrentWeapon->MagazineSize - CurrentAmmo);

		ReserveAmmoMap.Add(CurrentAmmoType, ReserveAmmo);
		CurrentAmmoMap.Add(CurrentWeapon, CurrentWeapon->MagazineSize);

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Current fully reloaded"));
	}

	UGameplayStatics::PlaySoundAtLocation(this, CurrentWeapon->ReloadSound, GetOwner()->GetActorLocation());

	OnReload.Broadcast(CurrentAmmoMap[CurrentWeapon], ReserveAmmoMap[CurrentWeapon->AmmoType]);
}

void UWeaponComponent::AddAmmo(UAmmoType* Ammo, int32 Amount)
{
	if(!ReserveAmmoMap.Contains(Ammo))
	{
		ReserveAmmoMap.Add(Ammo, Amount);

		return;
	}

	int32 AmmoCount = ReserveAmmoMap[Ammo];

	AmmoCount += Amount;

	ReserveAmmoMap.Add(Ammo, AmmoCount);

	OnAmmoChanged.Broadcast(Ammo, AmmoCount);
}

AActor* UWeaponComponent::FireTrace(bool DebugTrace)
{
	if(!CurrentWeapon)
	{
		return nullptr;
	}

	FVector StartLocation;
	FVector EndLocation;
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

	StartLocation = this->GetComponentLocation();
	EndLocation = StartLocation + (this->GetForwardVector() * CurrentWeapon->Range);

	GetWorld()->LineTraceSingleByChannel(Result, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility, QueryParams, ResponseParams);

	IDamageable* DamageInterface = Cast<IDamageable>(Result.GetActor());
	if(DamageInterface)
	{
		return Result.GetActor();
	}
	else
	{
		return nullptr;
	}
}