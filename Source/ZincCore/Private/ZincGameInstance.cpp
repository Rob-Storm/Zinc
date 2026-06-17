#include "ZincGameInstance.h"
#include "UObject/UObjectGlobals.h"
#include "UObject/Object.h"

void UZincGameInstance::Init()
{
	Super::Init();

#if !UE_BUILD_SHIPPING

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Press ~ to bring up the console"));

#endif
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