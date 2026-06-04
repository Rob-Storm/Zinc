#include "ItemChecker.h"
#include "UObject/Object.h"
#include "Kismet/GameplayStatics.h"

#include "ZincPlayer.h"
#include "ItemData.h"
#include "ItemSlot.h"

AItemChecker::AItemChecker()
{
	Billboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
	RootComponent = Billboard;
}


void AItemChecker::CheckForItem()
{
	if(!Item)
	{
		UE_LOG(LogTemp, Warning, TEXT("Item is not valid in AItemChecker"));
		return;
	}

	AZincPlayer* Player = Cast<AZincPlayer>(UGameplayStatics::GetPlayerPawn(this, 0));

	if(!Player)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerPawn is not a Subclass of AZincPlayer"));
		return;
	}

	UItemSlot* OutSlot;

	if(Player->InventoryComponent->HasItem(Item, OutSlot))
	{
		OnHasItem.Broadcast();

		if(RemoveItemOnCheck)
		{
			Player->InventoryComponent->RemoveItem(OutSlot);
		}
	}
	else
	{
		OnDoesNotHaveItem.Broadcast();
	}
}

void AItemChecker::RegisterIOEvents(FActorIOEventList& EventRegistry)
{
	EventRegistry.RegisterEvent(FActorIOEvent()
		.SetId(TEXT("AItemChecker::OnHasItem"))
		.SetDisplayName(INVTEXT("OnHasItem"))
		.SetTooltipText(INVTEXT("Event when the has the specified item"))
		.SetMulticastDelegate(this, &OnHasItem));

	EventRegistry.RegisterEvent(FActorIOEvent()
		.SetId(TEXT("AItemChecker::OnDoesNotHaveItem"))
		.SetDisplayName(INVTEXT("OnDoesNotHaveItem"))
		.SetTooltipText(INVTEXT("Event when the does not have the specified item"))
		.SetMulticastDelegate(this, &OnDoesNotHaveItem));
}

void AItemChecker::RegisterIOFunctions(FActorIOFunctionList& FunctionRegistry)
{
	FunctionRegistry.RegisterFunction(FActorIOFunction()
		.SetId(TEXT("AItemChecker::CheckForItem"))
		.SetDisplayName(INVTEXT("CheckForItem"))
		.SetTooltipText(INVTEXT("Checks if the player has the specified item"))
		.SetFunction(TEXT("CheckForItem")));
}

#if WITH_EDITOR

bool AItemChecker::CanEditChange(const FProperty* InProperty) const
{
	const bool ParentVal = Super::CanEditChange(InProperty);

	if(InProperty->GetFName() == GET_MEMBER_NAME_CHECKED(AItemChecker, RemoveItemOnCheck))
	{
		return ParentVal && Item;
	}
	else
	{
		return ParentVal;
	}
}

#endif