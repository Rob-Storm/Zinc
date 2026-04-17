#include "ZincGameInstance.h"

void UZincGameInstance::Init()
{
	Super::Init();

#if !UE_BUILD_SHIPPING

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Press ~ to bring up the console"));

#endif
}