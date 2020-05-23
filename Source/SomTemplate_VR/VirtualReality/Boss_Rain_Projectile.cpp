// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.


#include "Boss_Rain_Projectile.h"
#include "Engine/Classes/Components/SphereComponent.h"
#include "Engine/Classes/GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"

// Sets default values
ABoss_Rain_Projectile::ABoss_Rain_Projectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMeshComponent->SetRelativeScale3D(FVector(0.4f, 0.4f, 0.4f));

	ProjectileMovementComponent->InitialSpeed = 3000.0f;
	ProjectileMovementComponent->MaxSpeed = 3000.0f;
}

// Called when the game starts or when spawned
void ABoss_Rain_Projectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABoss_Rain_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

