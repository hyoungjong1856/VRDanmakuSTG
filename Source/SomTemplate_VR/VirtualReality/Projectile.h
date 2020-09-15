// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TP_VirtualRealityPawn_Motion.h"
#include "Particles/ParticleSystemComponent.h"
#include "Projectile.generated.h"

class ATP_VirtualRealityPawn_Motion;

UCLASS()
class SOMTEMPLATE_VR_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	class USphereComponent* CollisionComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	class UStaticMeshComponent* ProjectileMeshComponent;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	class UProjectileMovementComponent* ProjectileMovementComponent;

	USphereComponent* getCollisionComponent();
	UStaticMeshComponent* getProjectileMeshComponent();
	UProjectileMovementComponent* getProjectileMovementComponent();

	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	int Damage;

	int LifeTime_Counter;

	virtual void Check_Destroy();

	void FireInDirection(const FVector& ShootDirection);

	class UParticleSystemComponent* ProjectileParticle;

	// declare overlap begin function
	UFUNCTION()
	virtual void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
