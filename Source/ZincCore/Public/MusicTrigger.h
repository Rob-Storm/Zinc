#pragma once

#include "CoreMinimal.h"
#include "Trigger.h"

#include "Music.h"

#include "ZincGameMode.h"

#include "MusicTrigger.generated.h"

UCLASS(Blueprintable, BlueprintType)
class AMusicTrigger : public ATrigger
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Music")
	TObjectPtr<UMusic> EnterTrack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Music")
	TObjectPtr<UMusic> ExitTrack;
	
};
