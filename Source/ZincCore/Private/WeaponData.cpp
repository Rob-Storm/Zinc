#include "WeaponData.h"

#if WITH_EDITOR

void UWeaponData::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	FName PropertyName = (PropertyChangedEvent.Property != nullptr)
		? PropertyChangedEvent.Property->GetFName()
		: NAME_None;

	if (PropertyName == GET_MEMBER_NAME_CHECKED(UWeaponData, FireRate))
	{
		if(FireRate <= 0.f)
		{
			FireRate = 1.f;
		}
	}


	if (PropertyName == GET_MEMBER_NAME_CHECKED(UWeaponData, ReloadDelay))
	{
		if(ReloadDelay <= 0.f)
		{
			ReloadDelay = 1.f;
		}
	}
}

#endif