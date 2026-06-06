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

	UAmmoType* CurrentAmmoType = CurrentWeapon->AmmoType;

	if(!CurrentAmmoMap.Contains(CurrentAmmoType))
	{
		return;
	}

	int32 AmmoCount = CurrentAmmoMap[CurrentAmmoType];

	if(AmmoCount == 0)
	{
		// dry fire or reload if have reserve ammo

		UGameplayStatics::PlaySoundAtLocation(this, DryFireSound, GetOwner()->GetActorLocation());
	}
	else
	{
		Fire();
		AmmoCount--;
		CurrentAmmoMap.Add(CurrentAmmoType, AmmoCount);

	}
}

void UWeaponComponent::Fire()
{
	AActor* DamageActor = FireTrace(UProcessChecker::IsEditor());

	UGameplayStatics::PlaySoundAtLocation(this, CurrentWeapon->UseSound, GetOwner()->GetActorLocation());

	OnShoot.Broadcast();

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

}

void UWeaponComponent::AddAmmo(UAmmoType* Ammo, int32 Amount)
{
	if(!CurrentAmmoMap.Contains(Ammo))
	{
		CurrentAmmoMap.Add(Ammo, Amount);

		return;
	}

	int32 AmmoCount = CurrentAmmoMap[Ammo];

	AmmoCount += Amount;

	CurrentAmmoMap.Add(Ammo, AmmoCount);

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