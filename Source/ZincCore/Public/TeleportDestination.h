#pragma once

#include "CoreMinimal.h"
#include "Engine/NavigationObjectBase.h"

#include "Components/BillboardComponent.h"
#include "Components/CapsuleComponent.h"

#include "TeleportDestination.generated.h"

UCLASS(Blueprintable, BlueprintType)
class ATeleportDestination : public ANavigationObjectBase
{
	GENERATED_BODY()

public:

	ATeleportDestination();
	
};