#include "WeaponComponent.h"
#include "ZincCharacter.h"
#include "Damageable.h"
#include "ProcessChecker.h"

#include "Kismet/GameplayStatics.h"

void UWeaponComponent::TryFire()
{
	if(!CurrentWeapon)
	{
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
		Fire();
		AmmoCount--;
		CurrentAmmoMap.Add(CurrentWeapon, AmmoCount);

	}
}

void UWeaponComponent::Fire()
{
	AActor* DamageActor = FireTrace(UProcessChecker::IsEditor());

	UGameplayStatics::PlaySoundAtLocation(this, CurrentWeapon->UseSound, GetOwner()->GetActorLocation());

	OnShoot.Broadcast(CurrentWeapon, CurrentAmmoMap[CurrentWeapon]);

	if(!DamageActor)
	{
		return;
	}

	IDamageable* DamageInterface = Cast<IDamageable>(DamageActor);

	AZincCharacter* OwningCharacter = Cast<AZincCharacter>(GetOwner());

	IDamageable::Execute_Damage(DamageActor, CurrentWeapon->Damage, CurrentWeapon->AmmoType->DamageType, OwningCharacter);
}

void UWeaponComponent::Reload()
{
	UAmmoType* CurrentAmmoType = CurrentWeapon->AmmoType;

	if(!ReserveAmmoMap.Contains(CurrentAmmoType))
	{
		return;
	}

	int32 CurrentAmmo = CurrentAmmoMap[CurrentWeapon];
	int32 ReserveAmmo = ReserveAmmoMap[CurrentAmmoType];

	if(ReserveAmmo <= CurrentWeapon->MagazineSize - CurrentAmmo)
	{
		CurrentAmmo = ReserveAmmo;
		ReserveAmmo = 0;

		ReserveAmmoMap.Add(CurrentAmmoType, 0);
		CurrentAmmoMap.Add(CurrentWeapon, CurrentAmmo);

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Current partially reloaded"));

		OnReload.Broadcast();
	}
	else
	{
		ReserveAmmo -= (CurrentWeapon->MagazineSize - CurrentAmmo);

		ReserveAmmoMap.Add(CurrentAmmoType, ReserveAmmo);
		CurrentAmmoMap.Add(CurrentWeapon, CurrentWeapon->MagazineSize);

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Current fully reloaded"));

		OnReload.Broadcast();
	}

	UGameplayStatics::PlaySoundAtLocation(this, CurrentWeapon->ReloadSound, GetOwner()->GetActorLocation());
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