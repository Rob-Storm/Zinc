#pragma once

#include "CoreMinimal.h"
#include "GameFramework/WorldSettings.h"

#include "ZincWorldSettings.generated.h"

UCLASS()
class AZincWorldSettings : public AWorldSettings
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Music")
	TObjectPtr<USoundBase> AmbientMusic;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Music")
	TObjectPtr<USoundBase> AlternateAmbientMusic;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Music")
	TObjectPtr<USoundBase> AlertMusic;
	
};
