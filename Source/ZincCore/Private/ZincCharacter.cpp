#include "ZincCharacter.h"
#include "UObject/Object.h"

AZincCharacter::AZincCharacter()
{
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory Component"));
}