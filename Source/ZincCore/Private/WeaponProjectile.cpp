#include "WeaponProjectile.h"
#include "UObject/Object.h"

#include "ZincCharacter.h"
#include "WeaponData.h"
#include "AmmoType.h"
#include "Damageable.h"

AWeaponProjectile::AWeaponProjectile()
{
	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	RootComponent = Collider;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));

	Billboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));

	StaticMesh->SetupAttachment(RootComponent);
	Billboard->SetupAttachment(RootComponent);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));

	ProjectileMovement->InitialSpeed = 2500.f;
	ProjectileMovement->MaxSpeed = 2500.f;

	Collider->SetNotifyRigidBodyCollision(true);

	Collider->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	Collider->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	Collider->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);

}

void AWeaponProjectile::BeginPlay()
{
	Super::BeginPlay();

	if(!WeaponData)
	{
		UE_LOG(LogTemp, Warning, TEXT("Weapon data not set on AWeaponProjectile actor, destroying"))
		Destroy();
		return;
	}

	Collider->OnComponentHit.AddDynamic(this, &AWeaponProjectile::OnHit);
	Collider->OnComponentBeginOverlap.AddDynamic(this, &AWeaponProjectile::OnBeginOverlap);

	Collider->IgnoreActorWhenMoving(GetOwner(), true);

	SetLifeSpan(WeaponData->Range);

}

void AWeaponProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if(OtherActor->GetClass()->ImplementsInterface(UDamageable::StaticClass()))
	{
		IDamageable::Execute_Damage(OtherActor, WeaponData->Damage, WeaponData->AmmoType->DamageType, Cast<AZincCharacter>(GetOwner()));		
	}

	if(DestroyOnCollision)
	{
		Destroy();
	}
}

void AWeaponProjectile::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->GetClass()->ImplementsInterface(UDamageable::StaticClass()))
	{
		IDamageable::Execute_Damage(OtherActor, WeaponData->Damage, WeaponData->AmmoType->DamageType, Cast<AZincCharacter>(GetOwner()));		
	}

	if(DestroyOnCollision)
	{
		Destroy();
	}
}