#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "ItemData.h"
#include "ItemSlot.h"

#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSelectedItemChangedSignature, UItemSlot*, NewSelectedItem, int32, ItemSlotIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInventoryContentsChangedSignature, TArray<UItemData*>, Items);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInventorySizeChangedSignature, int32, NewSize);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnArrayInitializedSignature, const TArray<UItemSlot*>&, Slots);

UCLASS(Blueprintable, BlueprintType)
class UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="Inventory")
	FOnSelectedItemChangedSignature OnSelectedItemChanged;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="Inventory")
	FOnInventoryContentsChangedSignature OnInventoryContentsChanged;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="Inventory")
	FOnInventorySizeChangedSignature OnInventorySizeChanged;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="Inventory")
	FOnArrayInitializedSignature OnArrayInitialized;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory")
	int32 MaxItems = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory")
	TArray<UItemSlot*> ItemSlotList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory")
	TArray<UItemData*> ItemList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory")
	TObjectPtr<UItemSlot> SelectedItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory")
	int32 SelectedItemIndex = 0;

	/** Checks if the inventory has a specified item and returns the first instance of that item's slot otherwise, OutSlot will be nullptr */
	UFUNCTION(BlueprintCallable, Category="Inventory")
	bool HasItem(UItemData* Item, UItemSlot*& OutSlot) const
	{
		for(UItemSlot* Slot : ItemSlotList)
		{
			if(Slot->Item == Item)
			{
				OutSlot = Slot;
				return true;
			}
			else
			{
				continue;
			}
		}

		OutSlot = nullptr;
		return false;
	}

	UFUNCTION(BlueprintCallable, Category="Inventory")
	bool CanAddItem(UItemData* Item) const;

	UFUNCTION(BlueprintCallable, Category="Inventory")
	void AddItem(UItemData* Item);

	UFUNCTION(BlueprintCallable, Category="Inventory")
	void RemoveItem(UItemSlot* Slot);

	UFUNCTION(BlueprintCallable, Category="Inventory")
	AItemActor* DropItem(UItemData* Item);

	UFUNCTION(BlueprintCallable, Category="Inventory")
	void SetSlotItem(int32 SlotIndex, UItemData* Item);

	UFUNCTION(BlueprintCallable, Category="Inventory")
	void IncreaseInventorySize();

	UFUNCTION(BlueprintCallable, Category="Inventory")
	void SetSelectedItem(UItemSlot* ItemSlot);

	UFUNCTION(BlueprintCallable, Category="Inventory")
	void SetSelectedItemFromIndex(int32 ItemIndex);

	UFUNCTION(BlueprintCallable, Category="Inventory")
	void IncrementSelectedItem();

	UFUNCTION(BlueprintCallable, Category="Inventory")
	void DecrementSelectedItem();

protected:

	virtual void BeginPlay() override;
};
