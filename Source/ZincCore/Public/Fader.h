#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/BillboardComponent.h"

#include "ActorIOInterface.h"

#include "Fader.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFadeStartedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFadeFinishedSignature);

UCLASS(PrioritizeCategories = "Fader")
class AFader : public AActor, public IActorIOInterface
{
	GENERATED_BODY()

public:

	AFader();

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="Events")
	FOnFadeStartedSignature OnFadeStarted;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="Events")
	FOnFadeFinishedSignature OnFadeFinished;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UBillboardComponent> Billboard;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Fader")
	FLinearColor FadeColorStart;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Fader")
	FLinearColor FadeColorEnd;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Fader")
	void Fade(float Time = 5.f, bool DeleteOnFinish = false);

	virtual void RegisterIOEvents(FActorIOEventList& EventRegistry) override;
	virtual void RegisterIOFunctions(FActorIOFunctionList& FunctionRegistry) override;
	
};
