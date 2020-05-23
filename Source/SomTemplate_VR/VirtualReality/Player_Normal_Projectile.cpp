// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#include "Player_Normal_Projectile.h"
#include "Engine/Classes/Components/SphereComponent.h"
#include "Engine/Classes/GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"

// Sets default values
APlayer_Normal_Projectile::APlayer_Normal_Projectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UE_LOG(LogTemp, Warning, TEXT("Player Projectile spawn"));
}

// Called when the game starts or when spawned
void APlayer_Normal_Projectile::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Player Projectile BeginPlay"));
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &APlayer_Normal_Projectile::PNP_OnOverlapBegin);

}

// Called every frame
void APlayer_Normal_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayer_Normal_Projectile::PNP_OnOverlapBegin(UPrimitiveComponent* OverlappedComp, 
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, 
	const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && (OtherActor->GetClass()->GetName().Equals(TEXT("Boss"))))
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Projectile overlap"));
		UE_LOG(LogClass, Warning, TEXT("Overlap %s"), *OtherActor->GetName());
		//C_Boss.setBossCurrentHp(C_Boss.getBossCurrentHp() - 5);
		//UE_LOG(LogClass, Warning, TEXT("Boss HP : %d"), C_boss.getBossCurrentHp());
		Destroy();
		
	}
}

