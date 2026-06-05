#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "ItemData.generated.h"

UCLASS(Blueprintable, BlueprintType)
class UItemData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item Data")
	FText ItemName = FText::FromString(this->GetName());

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item Data")
	TObjectPtr<UTexture2D> ItemIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item Data")
	TObjectPtr<UStaticMesh> WorldModel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item Data")
	TObjectPtr<USoundBase> PickupSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item Data")
	TObjectPtr<USoundBase> UseSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item Data")
	TObjectPtr<USoundBase> DropSound;
	
};
