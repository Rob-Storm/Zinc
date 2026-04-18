#include "LogicRandom.h"
#include "UObject/Object.h"

#include "Kismet/KismetMathLibrary.h"

ALogicRandom::ALogicRandom()
{
	Billboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
	RootComponent = Billboard;
}

void ALogicRandom::GenerateValue(int32 MinValue, int32 MaxValue)
{
	int32 Value = UKismetMathLibrary::RandomIntegerInRange(MinValue, MaxValue);
	OnRandomValueGenerated.Broadcast(Value);
}

void ALogicRandom::ProcessEvent_OnGenerateValue(int32 Value)
{
	FActionExecutionContext& ExecContext = FActionExecutionContext::Get(this);
	ExecContext.SetNamedArgument(TEXT("$RandValue"), FString::FromInt(Value));
}

void ALogicRandom::RegisterIOEvents(FActorIOEventList& EventRegistry)
{
	EventRegistry.RegisterEvent(FActorIOEvent()
		.SetId(TEXT("ALogicRandom::OnRandomValueGenerated"))
		.SetDisplayName(INVTEXT("OnRandomValueGenerated"))
		.SetTooltipText(INVTEXT("Event when a random value has been generated"))
		.SetMulticastDelegate(this, &OnRandomValueGenerated)
		.SetEventProcessor(this, FName(TEXT("ProcessEvent_OnGenerateValue"))));
}

void ALogicRandom::RegisterIOFunctions(FActorIOFunctionList& FunctionRegistry)
{
	FunctionRegistry.RegisterFunction(FActorIOFunction()
		.SetId(TEXT("ALogicRandom::GenerateValue"))
		.SetDisplayName(INVTEXT("GenerateValue"))
		.SetTooltipText(INVTEXT("Generates a random int32 between MinValue and MaxValue"))
		.SetFunction(TEXT("GenerateValue")));
}
