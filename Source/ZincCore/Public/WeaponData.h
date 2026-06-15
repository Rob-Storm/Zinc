#pragma once

#include "CoreMinimal.h"
#include "ItemData.h"

#include "WeaponData.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	Hitscan,
	Projectile,
	Melee
};

UCLASS()
class UWeaponData : public UItemData
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Data")
	EWeaponType WeaponType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Data", meta=(EditCondition="WeaponType != EWeaponType::Melee", EditConditionHides))
	TObjectPtr<class UAmmoType> AmmoType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Data", meta=(EditCondition="WeaponType == EWeaponType::Projectile", EditConditionHides))
	TSubclassOf<class AWeaponProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Data")
	TObjectPtr<class UNiagaraSystem> FireEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Data")
	TSubclassOf<class AWeaponActor> WeaponActorClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Data", meta=(EditCondition="WeaponType != EWeaponType::Melee", EditConditionHides))
	int32 MagazineSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Data")
	int32 Damage;

	/** The amount of Pitch applied to the camera after shooting */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Data")
	float Recoil;

	/** The maximum range of the weapon in Unreal units. If using a projectile weapon, the range will be used as the projectile actor's lifetime, in seconds */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Data")
	float Range;

	/** The delay between shots in seconds */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Data")
	float FireRate = 1.f;

	/** The length of a reload in seconds*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Data", meta=(EditCondition="WeaponType != EWeaponType::Melee", EditConditionHides))
	float ReloadDelay = 1.f;

	/** The static mesh to be used as the first person view model. If nullptr, the world model will be used instead */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Data")
	TObjectPtr<UStaticMesh> ViewModel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Data", meta=(EditCondition="WeaponType != EWeaponType::Melee", EditConditionHides))
	TObjectPtr<USoundBase> ReloadSound;

protected:

#if WITH_EDITOR

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;


#endif

	
};
