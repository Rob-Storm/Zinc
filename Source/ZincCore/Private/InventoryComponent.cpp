#include "InventoryComponent.h"
#include "UObject/Object.h"

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	for(int32 i = 0; i < MaxItems; i++)
	{
		ItemSlotList.Add(NewObject<UItemSlot>(this));
	}

	OnArrayInitialized.Broadcast(ItemSlotList);
}

bool UInventoryComponent::CanAddItem(UItemData* Item) const
{
	if(!Item)
	{
		return false;
	}

	return ItemList.Num() < MaxItems;
}

void UInventoryComponent::AddItem(UItemData* Item)
{
	if(!Item)
	{
		return;
	}

	ItemList.Add(Item);

	for(UItemSlot* Slot : ItemSlotList)
	{
		if(Slot->Item)
		{
			continue;
		}
		else
		{
			Slot->SetItem(Item);
			break;
		}
	}

	OnInventoryContentsChanged.Broadcast(ItemList);
}

void UInventoryComponent::UInventoryComponent::RemoveItem(UItemData* Item)
{
	if(!Item)
	{
		return;
	}

	int32 ItemRemoveIndex = ItemList.Find(Item);

	if(ItemRemoveIndex == -1)
	{
		return;
	}

	ItemList.RemoveAt(ItemRemoveIndex);

	OnInventoryContentsChanged.Broadcast(ItemList);
}

void UInventoryComponent::SetSlotItem(int32 SlotIndex, UItemData* Item)
{
	if(!Item)
	{
		return;
	}

	if(!ItemSlotList.IsValidIndex(SlotIndex))
	{
		return;
	}

	ItemSlotList[SlotIndex]->SetItem(Item);
}

void UInventoryComponent::IncreaseInventorySize()
{
	MaxItems++;

	OnInventorySizeChanged.Broadcast(MaxItems);
}

void UInventoryComponent::SetSelectedItem(UItemSlot* Item)
{
	if(!Item)
	{
		return;
	}

	int32 SlotIndex = ItemSlotList.Find(Item);

	SelectedItem = Item;

	OnSelectedItemChanged.Broadcast(Item, SlotIndex);
}

void UInventoryComponent::SetSelectedItemFromIndex(int32 ItemIndex)
{
	int32 Index;

	if(!SelectedItem)
	{
		Index = 0;
	}
	else
	{
		Index = ItemIndex;
	}

	if(!ItemSlotList.IsValidIndex(Index))
	{
		return;
	}

	SelectedItem = ItemSlotList[Index];

	OnSelectedItemChanged.Broadcast(SelectedItem, Index);
}

void UInventoryComponent::IncrementSelectedItem()
{
	if(SelectedItemIndex == (MaxItems - 1))
	{
		SelectedItemIndex = 0;
	}
	else
	{
		SelectedItemIndex++;
	}

	SetSelectedItemFromIndex(SelectedItemIndex);
}

void UInventoryComponent::DecrementSelectedItem()
{
	if(SelectedItemIndex == 0)
	{
		SelectedItemIndex = MaxItems - 1;
	}
	else
	{
		SelectedItemIndex--;
	}

	SetSelectedItemFromIndex(SelectedItemIndex);
}