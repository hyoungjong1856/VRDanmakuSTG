// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.h"
#include "TP_VirtualRealityPawn_Motion.h"
#include "Boss_Normal_Projectile_1.generated.h"

class ATP_VirtualRealityPawn_Motion;

UCLASS()
class SOMTEMPLATE_VR_API ABoss_Normal_Projectile_1 : public AProjectile
{
	GENERATED_BODY()

private:
	float LifeTime;
	
public:	
	// Sets default values for this actor's properties
	ABoss_Normal_Projectile_1();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//UFUNCTION()
	//void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
