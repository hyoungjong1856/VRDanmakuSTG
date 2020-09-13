// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.


#include "Boss_Normal_Projectile_1.h"
#include "Engine/Classes/Components/SphereComponent.h"
#include "Engine/Classes/GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"

// Sets default values
ABoss_Normal_Projectile_1::ABoss_Normal_Projectile_1()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovementComponent->InitialSpeed = 3000.0f;
	ProjectileMovementComponent->MaxSpeed = 3000.0f;

	LifeTime = 0.0f;
}

// Called when the game starts or when spawned
void ABoss_Normal_Projectile_1::BeginPlay()
{
	Super::BeginPlay();

	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnOverlapBegin);
}

// Called every frame
void ABoss_Normal_Projectile_1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Check_Destroy();
}
/*
void ABoss_Normal_Projectile_1::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && (OtherActor->GetClass()->GetName().Equals(TEXT("TP_VirtualRealityPawn_Motion"))))
	{
		Destroy();
		UE_LOG(LogClass, Warning, TEXT("name : %s"),*OverlappedComp->GetName());
		UE_LOG(LogClass, Warning, TEXT("name : %s"), *OtherActor->GetName());
		UE_LOG(LogClass, Warning, TEXT("name : %s"), *OtherComp->GetName());

		Cast<ATP_VirtualRealityPawn_Motion>(OtherActor)->SetPlayerCurrentHP(Cast<ATP_VirtualRealityPawn_Motion>(OtherActor)->GetPlayerCurrentHP() - Damage);
		UE_LOG(LogClass, Warning, TEXT("Player HP : %d"), Cast<ATP_VirtualRealityPawn_Motion>(OtherActor)->GetPlayerCurrentHP());
		UE_LOG(LogClass, Warning, TEXT("Player LIFE : %d"), Cast<ATP_VirtualRealityPawn_Motion>(OtherActor)->GetPlayerCurrentLife());
	}
}*/

