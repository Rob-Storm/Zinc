#pragma once

#include "CoreMinimal.h"
#include "ItemData.h"

#include "WeaponData.generated.h"

UCLASS()
class UWeaponData : public UItemData
{
	GENERATED_BODY()

public:

	UWeaponData();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Data")
	TObjectPtr<class UAmmoType> AmmoType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Data")
	int32 MagazineSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Data")
	int32 Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Data")
	float Range;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Data")
	TObjectPtr<UStaticMesh> ViewModel;
	
};
