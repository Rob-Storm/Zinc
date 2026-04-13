#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "MainUI.generated.h"

UENUM(BlueprintType)
enum EHudLayer
{
	Game,
	GameMenu,
	Menu,
	Modal
};

UCLASS(Blueprintable, BlueprintType)
class UMainUI : public UUserWidget
{
	GENERATED_BODY()
	
	virtual void NativeConstruct() override;

public:

	/*
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Main UI")
	void AddWidget(UUserWidget* Widget, EHudLayer Layer);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Main UI")
	void PopWidget(UUserWidget* Widget);
	*/
	
};
