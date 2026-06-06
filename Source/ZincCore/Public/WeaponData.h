#pragma once

#include "CoreMinimal.h"
#include "ItemData.h"

#include "WeaponData.generated.h"

UCLASS()
class UWeaponData : public UItemData
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Data")
	TObjectPtr<class UAmmoType> AmmoType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Data")
	int32 MagazineSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Data")
	int32 Damage;

	/** The maximum range of the weapon in Unreal units */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Data")
	float Range;

	/** The delay between shots in seconds*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Data")
	float FireRate;

	/** The static mesh to be used as the first person view model. If nullptr, the world model will be used instead */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Data")
	TObjectPtr<UStaticMesh> ViewModel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Data")
	TObjectPtr<USoundBase> ReloadSound;
	
};
