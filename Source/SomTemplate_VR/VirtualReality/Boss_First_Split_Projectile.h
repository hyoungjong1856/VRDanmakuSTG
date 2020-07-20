// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.h"
#include "Boss_First_Split_Projectile.generated.h"

UCLASS()
class SOMTEMPLATE_VR_API ABoss_First_Split_Projectile : public AProjectile
{
	GENERATED_BODY()

private:
	float LifeTime;
	
public:	
	// Sets default values for this actor's properties
	ABoss_First_Split_Projectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
