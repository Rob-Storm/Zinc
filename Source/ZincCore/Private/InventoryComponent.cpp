#include "InventoryComponent.h"
#include "UObject/Object.h"

#include "ItemActor.h"

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

void UInventoryComponent::RemoveItem(UItemSlot* Slot)
{
	if(!Slot)
	{
		return;
	}

	if(!Slot->Item)
	{
		return;
	}

	UItemData* SlotData = Slot->Item;

	int32 DataIndex = ItemList.Find(SlotData);

	if(!ItemList.IsValidIndex(DataIndex))
	{
		return;
	}

	ItemList.RemoveAt(DataIndex);
	OnInventoryContentsChanged.Broadcast(ItemList);

	if(SelectedItem == Slot)
	{
		SetSelectedItem(Slot);
	}

	SetSlotItem(ItemSlotList.Find(Slot), nullptr);
}

AItemActor* UInventoryComponent::DropItem(UItemData* Item)
{
	if(!Item)
	{
		return nullptr;
	}

	FVector Location(GetOwner()->GetActorLocation());
	FRotator Rotation(GetOwner()->GetActorRotation());
	FActorSpawnParameters SpawnInfo;

	AItemActor* SpawnedActor = GetWorld()->SpawnActor<AItemActor>(ItemActorClass, Location, Rotation, SpawnInfo);

	SpawnedActor->SetItemData(Item);

	return SpawnedActor;
}

void UInventoryComponent::SetSlotItem(int32 SlotIndex, UItemData* Item)
{
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

void UInventoryComponent::SetSelectedItem(UItemSlot* ItemSlot)
{
	if(!ItemSlot)
	{
		return;
	}

	int32 SlotIndex = ItemSlotList.Find(ItemSlot);

	SelectedItem = ItemSlot;

	OnSelectedItemChanged.Broadcast(ItemSlot, SlotIndex);
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