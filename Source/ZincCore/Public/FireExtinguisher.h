#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "FireExtinguisher.generated.h"

UCLASS()
class AFireExtinguisher : public AActor
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UStaticMeshComponent> Model;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Fire Extinguisher")
	float Range;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Fire Extinguisher")
	void Use();
	
};
