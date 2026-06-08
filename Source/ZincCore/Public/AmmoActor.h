#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"

#include "Interactable.h"
#include "AmmoType.h"

#include "AmmoActor.generated.h"

UCLASS(PrioritizeCategories = "Ammo")
class AAmmoActor : public AActor, public IInteractable
{
	GENERATED_BODY()

public:

	//	AAmmoActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UStaticMeshComponent> Model;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ammo")
	TObjectPtr<UAmmoType> AmmoType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ammo")
	int32 Amount;

	//virtual void Interact_Implementation(AZincCharacter* CallingCharacter) override;
	
};
