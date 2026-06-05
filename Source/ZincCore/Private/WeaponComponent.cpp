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

	if(!AmmoWeaponMap.Contains(CurrentWeapon))
	{
		return;
	}

	int32 AmmoCount = AmmoWeaponMap[CurrentWeapon];

	if(AmmoCount == 0)
	{
		// dry fire or reload if have reserve ammo

		UGameplayStatics::PlaySoundAtLocation(this, DryFireSound, GetOwner()->GetActorLocation());
	}
	else
	{
		Fire();
		AmmoCount--;
		AmmoWeaponMap.Add(CurrentWeapon, AmmoCount);
	}
}

void UWeaponComponent::Fire()
{
	AActor* DamageActor = FireTrace(UProcessChecker::IsEditor());

	UGameplayStatics::PlaySoundAtLocation(this, CurrentWeapon->UseSound, GetOwner()->GetActorLocation());

	if(!DamageActor)
	{
		return;
	}

	IDamageable* DamageInterface = Cast<IDamageable>(DamageActor);

	AZincCharacter* OwningCharacter = Cast<AZincCharacter>(GetOwner());

	IDamageable::Execute_Damage(DamageActor, CurrentWeapon->Damage, EDamageType::Custom, OwningCharacter);
}

void UWeaponComponent::Reload()
{

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