// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.


#include "Projectile.h"
#include "Engine/Classes/Components/SphereComponent.h"
#include "Engine/Classes/GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	CollisionComponent->InitSphereRadius(15.0f);
	RootComponent = CollisionComponent;

	ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PROJECTILE_BODY"));
	ProjectileMeshComponent->SetupAttachment(CollisionComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
	ProjectileMovementComponent->InitialSpeed = 10000.0f;
	ProjectileMovementComponent->MaxSpeed = 10000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;

	// Set no gravity
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> PT_BODY(TEXT("/Game/VirtualRealityBP/Sphere.Sphere"));

	if (PT_BODY.Succeeded())
	{
		ProjectileMeshComponent->SetStaticMesh(PT_BODY.Object);
		ProjectileMeshComponent->SetGenerateOverlapEvents(true);
	}

	Damage = 1;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	//CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnOverlapBegin);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

USphereComponent* AProjectile::getCollisionComponent()
{
	return CollisionComponent;
}

UStaticMeshComponent* AProjectile::getProjectileMeshComponent()
{
	return ProjectileMeshComponent;
}

UProjectileMovementComponent* AProjectile::getProjectileMovementComponent()
{
	return ProjectileMovementComponent;
}

void AProjectile::Check_Destroy()
{
	LifeTime_Counter++;
	if (LifeTime_Counter > 500)
		Destroy();
}

void AProjectile::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

void AProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{	
	
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && (OtherActor->GetClass()->GetName().Equals(TEXT("TP_VirtualRealityPawn_Motion"))))
	{
		Destroy();
		UE_LOG(LogClass, Warning, TEXT("name : %s"),*OverlappedComp->GetName());
		UE_LOG(LogClass, Warning, TEXT("name : %s"), *OtherActor->GetName());
		UE_LOG(LogClass, Warning, TEXT("name : %s"), *OtherActor->GetClass()->GetName());
		UE_LOG(LogClass, Warning, TEXT("name : %s"), *OtherComp->GetName());

		Cast<ATP_VirtualRealityPawn_Motion>(OtherActor)->SetPlayerCurrentHP(Cast<ATP_VirtualRealityPawn_Motion>(OtherActor)->GetPlayerCurrentHP() - Damage);
		UE_LOG(LogClass, Warning, TEXT("Player HP : %d"), Cast<ATP_VirtualRealityPawn_Motion>(OtherActor)->GetPlayerCurrentHP());
		UE_LOG(LogClass, Warning, TEXT("Player LIFE : %d"), Cast<ATP_VirtualRealityPawn_Motion>(OtherActor)->GetPlayerCurrentLife());
	}
}

