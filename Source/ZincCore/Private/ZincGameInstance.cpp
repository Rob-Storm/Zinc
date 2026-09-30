#include "ZincGameInstance.h"
#include "UObject/UObjectGlobals.h"
#include "UObject/Object.h"

void UZincGameInstance::Init()
{
	Super::Init();

	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UZincGameInstance::HandlePostLoadMap);

	LoadData();

#if !UE_BUILD_SHIPPING

	#if PLATFORM_ANDROID || PLATFORM_IOS

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("4 Finger Tap to bring up the console"));

	#else

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Press ~ to bring up the console"));

	#endif

#endif
}

void UZincGameInstance::UnlockLevel_Implementation(const FString& LevelName)
{
	UE_LOG(LogTemp, Log, TEXT("Unlocked level '%s'"), *LevelName);
	UnlockedLevels.Add(LevelName);

	SaveData();

	OnLevelUnlocked.Broadcast(LevelName);
}

void UZincGameInstance::ShowError(FText Caption, FText Message, bool ReturnControl)
{
	UErrorUI* ErrorWidget = CreateWidget<UErrorUI>(GetWorld(), ErrorWidgetClass);

	if(ErrorWidget)
	{
		ErrorWidget->CaptionText = Caption;
		ErrorWidget->MessageText = Message;
		ErrorWidget->ReturnControl = ReturnControl;

		ErrorWidget->PopulateUI();
		ErrorWidget->AddToViewport();
	}
}

void UZincGameInstance::HandlePostLoadMap(UWorld* Map)
{
	TSoftObjectPtr<UWorld> LoadedLevel(Map);
	OnPostLoadMap(LoadedLevel);
}