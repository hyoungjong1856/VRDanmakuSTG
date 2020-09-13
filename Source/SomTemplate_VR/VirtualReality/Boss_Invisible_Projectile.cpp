// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.


#include "Boss_Invisible_Projectile.h"
#include "Engine/Classes/Components/SphereComponent.h"
#include "Engine/Classes/GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Math/Vector.h"
#include "TP_VirtualRealityPawn_Motion.h"
#include "TP_VirtualRealityPawn_GamePad.h"
#include "ConstructorHelpers.h"

// Sets default values
ABoss_Invisible_Projectile::ABoss_Invisible_Projectile()
{

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovementComponent->InitialSpeed = 3000.0f;
	ProjectileMovementComponent->MaxSpeed = 3000.0f;

	LifeTime = 0.0f;
}

// Called when the game starts or when spawned
void ABoss_Invisible_Projectile::BeginPlay()
{
	Super::BeginPlay();
	
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnOverlapBegin);
}

// Called every frame
void ABoss_Invisible_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Check_Destroy();
	
	FVector PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

	if ((GetActorLocation() - PlayerLocation).Size() < 10000)
		SetActorHiddenInGame(false);

	else
		SetActorHiddenInGame(true);

	//UE_LOG(LogTemp, Warning, TEXT("distinction x: %f, y: %f, z: %f\n"), GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z);
	//UE_LOG(LogTemp, Warning, TEXT("distinction2 x: %f, y: %f, z: %f\n"), PlayerLocation.X, PlayerLocation.Y, PlayerLocation.Z);
	//UE_LOG(LogTemp, Warning, TEXT("distinction %f \n"), (GetActorLocation() - PlayerLocation).Size());
	//UE_LOG(LogTemp, Warning, TEXT("distinction %f \n"), (GetActorLocation() - PlayerLocation).Size());


}

