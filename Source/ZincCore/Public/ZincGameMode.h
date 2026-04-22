#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"

#include "Music.h"

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UAudioComponent> MusicPlayer;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Audio")
	TObjectPtr<class USoundscapeData> CurrentSoundscape;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Audio")
	void PlaySoundscape(class USoundscapeData* Data);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Audio")
	void PlayAlertMusic();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Audio")
	void StopAlertMusic();
};
