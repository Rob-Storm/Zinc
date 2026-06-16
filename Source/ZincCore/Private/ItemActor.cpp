#include "ItemActor.h"
#include "UObject/Object.h"
#include "ZincCharacter.h"
#include "ZincPlayer.h"
#include "WeaponData.h"

AItemActor::AItemActor()
{
	Model = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Model"));
	RootComponent = Model;
}

void AItemActor::Interact_Implementation(AZincCharacter* CallingCharacter)
{
	if(!CallingCharacter->InventoryComponent->CanAddItem(ItemData))
	{
		return;
	}

	CallingCharacter->InventoryComponent->AddItem(ItemData);

	OnItemPickedUp.Broadcast();

	AZincPlayer* Player = Cast<AZincPlayer>(CallingCharacter);

	if(Player)
	{
		UWeaponData* WeaponData = Cast<UWeaponData>(ItemData);
		if(WeaponData)
		{
			Player->WeaponComponent->AddCurrentWeaponAmmo(WeaponData, AmmoInWeapon);
		}
	}

	Destroy();
}

void AItemActor::RegisterIOEvents(FActorIOEventList& EventRegistry)
{
	EventRegistry.RegisterEvent(FActorIOEvent()
		.SetId(TEXT("AItemActor::OnItemPickedUp"))
		.SetDisplayName(INVTEXT("OnItemPickedUp"))
		.SetTooltipText(INVTEXT("Event when the has been picked up"))
		.SetMulticastDelegate(this, &OnItemPickedUp));
}

void AItemActor::RegisterIOFunctions(FActorIOFunctionList& FunctionRegistry)
{
	FunctionRegistry.RegisterFunction(FActorIOFunction()
		.SetId(TEXT("AItemActor::SetCanPickUpState"))
		.SetDisplayName(INVTEXT("SetCanPickUpState"))
		.SetTooltipText(INVTEXT("Sets the CanPickUp state"))
		.SetFunction(TEXT("SetCanPickUpState")));
}

#if WITH_EDITOR

void AItemActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	FName PropertyName = (PropertyChangedEvent.Property != nullptr)
		? PropertyChangedEvent.Property->GetFName()
		: NAME_None;

	if (PropertyName == GET_MEMBER_NAME_CHECKED(AItemActor, ItemData))
	{
		if (ItemData && ItemData->WorldModel)
		{
			Model->SetStaticMesh(ItemData->WorldModel);
		}
	}
}

bool AItemActor::CanEditChange(const FProperty* InProperty) const
{
	const bool ParentVal = Super::CanEditChange(InProperty);

	if(InProperty->GetFName() == GET_MEMBER_NAME_CHECKED(AItemActor, AmmoInWeapon))
	{
		UWeaponData* WeaponData = Cast<UWeaponData>(ItemData);

		return ParentVal && WeaponData;
	}
	else
	{
		return ParentVal;
	}
}

#endif