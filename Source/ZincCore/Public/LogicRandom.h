#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/BillboardComponent.h"

#include "ActorIOInterface.h"

#include "LogicRandom.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRandomValueGeneratedSignature, int32, Value);

UCLASS(PrioritizeCategories = "Random")
class ALogicRandom : public AActor, public IActorIOInterface
{
	GENERATED_BODY()

public:

	ALogicRandom();

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="ZincCore")
	FOnRandomValueGeneratedSignature OnRandomValueGenerated;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UBillboardComponent> Billboard;

	UFUNCTION(BlueprintCallable, Category="Random")
	void GenerateValue(int32 MinValue = 0, int32 MaxValue = 1);

	UFUNCTION(BlueprintCallable, Category="Random")
	void ProcessEvent_OnGenerateValue(int32 Value);

	virtual void RegisterIOEvents(FActorIOEventList& EventRegistry) override;
	virtual void RegisterIOFunctions(FActorIOFunctionList& FunctionRegistry) override;
	
};
