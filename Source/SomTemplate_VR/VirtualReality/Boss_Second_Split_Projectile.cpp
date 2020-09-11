// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.


#include "Boss_Second_Split_Projectile.h"
#include "Engine/Classes/Components/SphereComponent.h"
#include "Engine/Classes/GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"

// Sets default values
ABoss_Second_Split_Projectile::ABoss_Second_Split_Projectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovementComponent->InitialSpeed = 3000.0f;
	ProjectileMovementComponent->MaxSpeed = 3000.0f;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> PT_BODY(TEXT("/Game/VirtualRealityBP/Cube.Cube"));

	if (PT_BODY.Succeeded())
	{
		ProjectileMeshComponent->SetStaticMesh(PT_BODY.Object);
	}
}

// Called when the game starts or when spawned
void ABoss_Second_Split_Projectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABoss_Second_Split_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Check_Destroy();
}

