#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "ZincGameInstance.generated.h"

UCLASS()
class UZincGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	virtual void Init() override;
	
};
