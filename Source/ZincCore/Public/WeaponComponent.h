#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "GameFramework/Actor.h"

#include "WeaponData.h"

#include "WeaponComponent.generated.h"

/* Todo:
 * Ammo
 * Reloading
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponChangedSignature, UWeaponData*, NewWeapon);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnShootSignature, int32, CurrentAmmo, UWeaponData*, ShotWeapon);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnReloadSignature);

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
	FOnReloadSignature OnReload;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Component")
	TObjectPtr<UWeaponData> CurrentWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Component")
	TMap<UWeaponData*, int32> AmmoWeaponMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Component")
	TObjectPtr<USoundBase> DryFireSound;

	UFUNCTION(BlueprintCallable, Category="Weapon Component")
	void SetCurrentWeapon(UWeaponData* NewWeapon)
	{
		CurrentWeapon = NewWeapon;

		OnWeaponChanged.Broadcast(CurrentWeapon);
	}

	UFUNCTION(BlueprintCallable, Category="Weapon Component")
	void TryFire();

	UFUNCTION(BlueprintCallable, Category="Weapon Component")
	void Fire();

	UFUNCTION(BlueprintCallable, Category="Weapon Component")
	void Reload();

	/** Runs a line trace and returns the hit actor that implements the IDamageable Interface */
	UFUNCTION(BlueprintCallable, Category="Weapon Component")
	AActor* FireTrace(bool DebugTrace);

};
