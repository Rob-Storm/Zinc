#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/BillboardComponent.h"

#include "SoundscapeData.h"

#include "ActorIOInterface.h"

#include "Soundscape.generated.h"

UCLASS()
class ASoundscape : public AActor, public IActorIOInterface
{
	GENERATED_BODY()

public:

	ASoundscape();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UBillboardComponent> Billboard;

	/** The soundscape data asset to be played upon activation */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Soundscape")
	TObjectPtr<USoundscapeData> Soundscape;

	UFUNCTION(BlueprintCallable, Category="Soundscape")
	void ActivateSoundscape();

	virtual void RegisterIOEvents(FActorIOEventList& EventRegistry) override;
	virtual void RegisterIOFunctions(FActorIOFunctionList& FunctionRegistry) override;
	
};
