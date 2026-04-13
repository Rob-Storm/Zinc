#include "ReadableActor.h"
#include "UObject/Object.h"

AReadableActor::AReadableActor()
{
	Model = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Model"));
	RootComponent = Model;
}

void AReadableActor::Interact_Implementation(ACharacter* CallingCharacter)
{

}

void AReadableActor::RegisterIOEvents(FActorIOEventList& EventRegistry)
{
	EventRegistry.RegisterEvent(FActorIOEvent()
		.SetId(TEXT("AReadableActor::OnRead"))
		.SetDisplayName(INVTEXT("OnRead"))
		.SetTooltipText(INVTEXT("Event when the document is read"))
		.SetMulticastDelegate(this, &OnRead));
}

void AReadableActor::RegisterIOFunctions(FActorIOFunctionList& FunctionRegistry)
{
}

#if WITH_EDITOR

void AReadableActor::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	FName PropertyName = (PropertyChangedEvent.Property != nullptr)
		? PropertyChangedEvent.Property->GetFName()
		: NAME_None;

	if (PropertyName == GET_MEMBER_NAME_CHECKED(AReadableActor, ReadableData))
	{
		if (ReadableData && ReadableData->ModelOverride)
		{
			Model->SetStaticMesh(ReadableData->ModelOverride);
		}
	}
}

#endif