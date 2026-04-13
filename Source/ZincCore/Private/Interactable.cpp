#include "Interactable.h"

void IInteractable::Interact_Implementation(ACharacter* CallingCharacter)
{

}

FText IInteractable::GetInteractText_Implementation() const
{
	return FText::FromString("interact with object");
}
