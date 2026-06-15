#include "AmmoActor.h"
#include "UObject/Object.h"

#include "ZincPlayer.h"

AAmmoActor::AAmmoActor()
{
	Model = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Model"));
	RootComponent = Model;

	Model->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void AAmmoActor::Interact_Implementation(AZincCharacter* CallingCharacter)
{
	AZincPlayer* Player = Cast<AZincPlayer>(CallingCharacter);

	if(!Player)
	{
		return;
	}

	Player->WeaponComponent->AddAmmo(AmmoType, Amount);

	Destroy();
}