#include "TeleportDestination.h"
#include "UObject/Object.h"

ATeleportDestination::ATeleportDestination()
{
	GetCapsuleComponent()->InitCapsuleSize(40.0f, 92.0f);
	GetCapsuleComponent()->SetShouldUpdatePhysicsVolume(false);

	#if WITH_EDITOR

    static ConstructorHelpers::FObjectFinder<UTexture2D> Good(TEXT("/Engine/EditorResources/Waypoint.Waypoint"));

    if (Good.Succeeded())
    {
        GetGoodSprite()->SetSprite(Good.Object);
    }

    static ConstructorHelpers::FObjectFinder<UTexture2D> Bad(TEXT("/Game/Zinc/Texture/Editor/TeleportWarning.TeleportWarning"));

    if (Bad.Succeeded())
    {
        GetBadSprite()->SetSprite(Bad.Object);
        GetBadSprite()->SetVisibility(false);
    }

#endif
}