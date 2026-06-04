#include "ItemActor.h"
#include "UObject/Object.h"

AItemActor::AItemActor()
{
	Model = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Model"));
	RootComponent = Model;
}

void AItemActor::Interact_Implementation(AZincCharacter* CallingCharacter)
{

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

#endif