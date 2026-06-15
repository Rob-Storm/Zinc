#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "GameFramework/Actor.h"

#include "TimerManager.h"

#include "WeaponData.h"
#include "AmmoType.h"

#include "WeaponComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnWeaponChangedSignature, UWeaponData*, NewWeapon, int32, CurrentAmmo, int32, ReserveAmmo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnShootSignature, UWeaponData*, ShotWeapon, int32, CurrentAmmo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAmmoChangedSignature, UAmmoType*, ChangedAmmo, int32, CurrentAmmo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnReloadSignature, int32, CurrentAmmo, int32, ReserveAmmo);

UCLASS(Blueprintable, BlueprintType)
class UWeaponComponent : public USceneComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="Weapon Component")
	FOnWeaponChangedSignature OnWeaponChanged;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="Weapon Component")
	FOnShootSignature OnShoot;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="Weapon Component")
	FOnAmmoChangedSignature OnAmmoChanged;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="Weapon Component")
	FOnReloadSignature OnReload;

	/** If true, will try to get a UCameraComponent pointer from the owner, does not effect projectile weapons */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Component")
	bool UseCameraForTrace = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Component")
	TObjectPtr<UWeaponData> CurrentWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Component")
	TMap<UAmmoType*, int32> ReserveAmmoMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Component")
	TMap<UWeaponData*, int32> CurrentAmmoMap;

	/** The sound played when attemping to fire a weapon with no ammo */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Component")
	TObjectPtr<USoundBase> DryFireSound;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Weapon Component")
	TObjectPtr<class AWeaponActor> WeaponActor;

	UFUNCTION(BlueprintCallable, Category="Weapon Component")
	void SetCurrentWeapon(UWeaponData* NewWeapon);

	UFUNCTION(BlueprintCallable, Category="Weapon Component")
	void TryFire();

	UFUNCTION(BlueprintCallable, Category="Weapon Component")
	void Fire();

	UFUNCTION(BlueprintCallable, Category="Weapon Component")
	void FireHitscan();

	UFUNCTION(BlueprintCallable, Category="Weapon Component")
	void FireProjectile();

	UFUNCTION(BlueprintCallable, Category="Weapon Component")
	void FireMelee();

	UFUNCTION(BlueprintCallable, Category="Weapon Component")
	bool CanReload() const
	{
		if(!ReserveAmmoMap.Contains(CurrentWeapon->AmmoType))
		{
			return false;
		}

		return ReserveAmmoMap[CurrentWeapon->AmmoType] > 0;
	}

	UFUNCTION(BlueprintCallable, Category="Weapon Component")
	void Reload();

	UFUNCTION(BlueprintCallable, Category="Weapon Component")
	void AddAmmo(UAmmoType* Ammo, int32 Amount);

	/** Runs a line trace and returns the hit actor that implements the IDamageable Interface */
	UFUNCTION(BlueprintCallable, Category="Weapon Component")
	AActor* FireTrace(bool DebugTrace);

private:

	UPROPERTY()
	bool CanShoot = true;

	UPROPERTY()
	FTimerHandle ShootDelayHandle;

	UPROPERTY()
	FTimerHandle ReloadDelayHandle;

	UFUNCTION()
	void ResetShoot()
	{
		CanShoot = true;
	}

	UFUNCTION()
	void AttachWeaponActor();

};
