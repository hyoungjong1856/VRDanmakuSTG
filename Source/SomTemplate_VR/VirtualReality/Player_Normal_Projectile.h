// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.h"
#include "Boss.h"
#include "Particles/ParticleSystemComponent.h"
#include "Player_Normal_Projectile.generated.h"

class ABoss;

UCLASS()
class SOMTEMPLATE_VR_API APlayer_Normal_Projectile : public AProjectile
{
	GENERATED_BODY()

private:
	TArray<AActor*> FoundActors;

	ATP_VirtualRealityPawn_Motion* Player;

	class UParticleSystemComponent* PlayerProjectileParticle;

	// Sound
	UPROPERTY()
	class USoundWave* PlayerBulletCollisionSound;
	
public:	
	// Sets default values for this actor's properties
	APlayer_Normal_Projectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Check_Destroy() override;

	virtual void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
