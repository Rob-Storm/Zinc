#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"

#include "Components/AudioComponent.h"

#include "ZincGameMode.generated.h"

UCLASS()
class AZincGameMode : public AGameMode
{
	GENERATED_BODY()

public:

	AZincGameMode();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UAudioComponent> SoundscapePlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Audio")
	TObjectPtr<class USoundscapeData> CurrentSoundscape;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Audio")
	void PlaySoundscape(class USoundscapeData* Data);
	
};
