#include "WeaponModel.h"
#include "UObject/Object.h"

#include "NiagaraFunctionLibrary.h"

AWeaponModel::AWeaponModel()
{	
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Model"));
	StaticMesh->SetupAttachment(RootComponent);

	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	EffectsPoint = CreateDefaultSubobject<USceneComponent>(TEXT("EffectsPoint"));
	EffectsPoint->SetupAttachment(StaticMesh);

	LightEffect = CreateDefaultSubobject<UPointLightComponent>(TEXT("Light"));
	LightEffect->SetupAttachment(EffectsPoint);

	LightEffect->SetVisibility(false);
	LightEffect->SetLightFColor(FColor(250, 200, 0, 255));
	LightEffect->SetAttenuationRadius(500.f);
}

void AWeaponModel::PlayEffects(UNiagaraSystem* Effect)
{
	UNiagaraFunctionLibrary::SpawnSystemAttached(
		Effect,
		EffectsPoint,
		NAME_None,
		FVector(0),
		FRotator(0),
		EAttachLocation::SnapToTarget,
		true,
		true,
		ENCPoolMethod::None,
		false
		);

	if(UseMuzzleFlash)
	{
		LightEffect->SetVisibility(true);
		GetWorld()->GetTimerManager().SetTimer(LightEffectHandle, this, &AWeaponModel::DisableLight, 0.1f, false, -1.f);
	}
}