#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "Damageable.h"

#include "AmmoType.generated.h"

UCLASS()
class UAmmoType : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ammo Type")
	FText Name = FText::FromString(this->GetName());

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ammo Type")
	TObjectPtr<UTexture2D> Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ammo Type")
	int32 MaxAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ammo Type")
	TEnumAsByte<EDamageType> DamageType;
	
};
