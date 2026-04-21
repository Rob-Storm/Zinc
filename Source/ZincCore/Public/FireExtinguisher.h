#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Interactable.h"

#include "FireExtinguisher.generated.h"

UCLASS()
class AFireExtinguisher : public AActor, public IInteractable
{
	GENERATED_BODY()

public:

	AFireExtinguisher();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UStaticMeshComponent> Model;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Fire Extinguisher")
	float Range;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Fire Extinguisher")
	void Use();

	virtual FText GetInteractText_Implementation() const
	{
		return INVTEXT("equip fire extinguisher");
	}
	
};
