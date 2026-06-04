#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InventoryComponent.h"

#include "ZincCharacter.generated.h"

UCLASS()
class AZincCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	AZincCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UInventoryComponent> InventoryComponent;
	
};
