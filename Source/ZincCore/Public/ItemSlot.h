#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"

#include "ItemSlot.generated.h"

class UItemData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSlotItemChangedSignature, UItemData*, Item);

UCLASS(Blueprintable, BlueprintType)
class UItemSlot : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="ItemSlot")
	FOnSlotItemChangedSignature OnSlotItemChanged;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ItemSlot")
	TObjectPtr<UItemData> Item;

	UFUNCTION(BlueprintCallable, Category="ItemSlot")
	void SetItem(UItemData* NewItem)
	{
		Item = NewItem;

		OnSlotItemChanged.Broadcast(NewItem);
	}

	UFUNCTION(BlueprintPure, BlueprintCallable, Category="ItemSlot")
	bool IsEmpty() const
	{
		return !Item;
	}
};
