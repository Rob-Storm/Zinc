#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "Interactable.generated.h"

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
	void Interact(ACharacter* CallingCharacter);
	
	virtual void Interact_Implementation(ACharacter* CallingCharacter);

	/** Custom interaction text, follows 'Right Click to'. Default is 'interact with object' */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interactable")
	FText GetInteractText() const;
	
	virtual FText GetInteractText_Implementation() const;
};