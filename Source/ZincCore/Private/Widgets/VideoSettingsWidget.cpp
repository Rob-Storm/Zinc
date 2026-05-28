#include "Widgets/VideoSettingsWidget.h"
#include "GameFramework/GameUserSettings.h"

void UVideoSettingsWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UVideoSettingsWidget::SetQualityPreset(int Level)
{
	TObjectPtr<UGameUserSettings> Setting = UGameUserSettings::GetGameUserSettings();

	Setting->SetViewDistanceQuality(Level);
	Setting->SetShadowQuality(Level);
	Setting->SetGlobalIlluminationQuality(Level);
	Setting->SetReflectionQuality(Level);
	Setting->SetAntiAliasingQuality(Level);
	Setting->SetTextureQuality(Level);
	Setting->SetVisualEffectQuality(Level);
	Setting->SetPostProcessingQuality(Level);
	Setting->SetFoliageQuality(Level);
	Setting->SetShadingQuality(Level);
}