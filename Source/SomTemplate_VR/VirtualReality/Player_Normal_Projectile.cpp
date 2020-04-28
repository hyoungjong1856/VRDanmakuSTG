// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#include "Projectile.h"
#include "Player_Normal_Projectile.h"

// Sets default values
APlayer_Normal_Projectile::APlayer_Normal_Projectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//AProjectile::getCollisionComponent()->OnComponentBeginOverlap.AddDynamic(this, &APlayer_Normal_Projectile::OnOverlapBegin);
}

// Called when the game starts or when spawned
void APlayer_Normal_Projectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayer_Normal_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayer_Normal_Projectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Player Projectile"));
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		//Destroy();
		
	}
}

