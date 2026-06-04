#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "Interactable.generated.h"

class AZincCharacter;

UINTERFACE()
class ZINCCORE_API UInteractable : public UInterface
{
	GENERATED_BODY()
};

class ZINCCORE_API IInteractable
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interactable")
	void Interact(AZincCharacter* CallingCharacter);
	
	virtual void Interact_Implementation(AZincCharacter* CallingCharacter);

	/** Custom interaction text, follows 'Right Click to'. Default is 'interact with object' */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interactable")
	FText GetInteractText() const;
	
	virtual FText GetInteractText_Implementation() const;
};