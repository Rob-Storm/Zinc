#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Components/PointLightComponent.h"

#include "TimerManager.h"

#include "WeaponActor.generated.h"

UCLASS(Blueprintable, BlueprintType, Abstract, PrioritizeCategories = "Weapon Actor")
class AWeaponActor : public AActor
{
	GENERATED_BODY()

public:

	AWeaponActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UStaticMeshComponent> StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<USceneComponent> EffectsPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UPointLightComponent> LightEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Actor")
	FTimerHandle LightEffectHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Actor")
	bool UseMuzzleFlash = true;

	UFUNCTION(BlueprintCallable, Category="Weapon Actor")
	void PlayEffects(class UNiagaraSystem* Effect);

private:

	UFUNCTION()
	void DisableLight()
	{
		LightEffect->SetVisibility(false);
	}
	
};
