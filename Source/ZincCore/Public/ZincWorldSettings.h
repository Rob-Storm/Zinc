#pragma once

#include "CoreMinimal.h"
#include "GameFramework/WorldSettings.h"

#include "Music.h"

#include "ZincWorldSettings.generated.h"

UCLASS()
class AZincWorldSettings : public AWorldSettings
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Music")
	TObjectPtr<UMusic> AmbientMusic;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Music")
	TObjectPtr<UMusic> AlternateAmbientMusic;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Music")
	TObjectPtr<UMusic> AlertMusic;
	
};
