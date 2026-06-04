#include "TeleportDestination.h"
#include "UObject/Object.h"

ATeleportDestination::ATeleportDestination()
{
	GetCapsuleComponent()->InitCapsuleSize(40.0f, 92.0f);
	GetCapsuleComponent()->SetShouldUpdatePhysicsVolume(false);

	#if WITH_EDITOR

    static ConstructorHelpers::FObjectFinder<UTexture2D> Good(TEXT("/Game/Zinc/Texture/Editor/TeleportDestinationIcon.TeleportDestinationIcon"));

    if (Good.Succeeded())
    {
        GetGoodSprite()->SetSprite(Good.Object);
        GetGoodSprite()->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));

    }

    static ConstructorHelpers::FObjectFinder<UTexture2D> Bad(TEXT("/Game/Zinc/Texture/Editor/TeleportDestinationWarningIcon.TeleportDestinationWarningIcon"));

    if (Bad.Succeeded())
    {
        GetBadSprite()->SetSprite(Bad.Object);
        GetBadSprite()->SetVisibility(false);
    }

#endif
}