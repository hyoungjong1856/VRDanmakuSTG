// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.h"
#include "Boss.h"
#include "Player_Normal_Projectile.generated.h"

class ABoss;

UCLASS()
class SOMTEMPLATE_VR_API APlayer_Normal_Projectile : public AProjectile
{
	GENERATED_BODY()

private:
	ABoss* Boss;
	
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

	UFUNCTION()
	void PNP_OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
