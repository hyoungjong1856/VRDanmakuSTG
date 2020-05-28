// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Boss.generated.h"

UCLASS()
class SOMTEMPLATE_VR_API ABoss : public AActor
{
	GENERATED_BODY()

private:
	
	UPROPERTY(EditAnywhere)
	FVector Offset;
	
	UPROPERTY(EditAnywhere, Category = Boss_Projectile)
	TSubclassOf<class AProjectile> Pattern_1_Projectile;

	UPROPERTY(EditAnywhere, Category = Boss_Projectile)
	TSubclassOf<class AProjectile> Pattern_2_Rain_Projectile;

	UPROPERTY(EditAnywhere, Category = Boss_Projectile)
	TSubclassOf<class AProjectile> Pattern_2_Projectile;

	double Pattern_1_timer;
	double Pattern_2_timer;
	double Pattern_3_timer;
	double Pattern_4_timer;

	int Pattern_2_Windmill_Rotation;
	
public:	
	// Sets default values for this actor's properties
	ABoss();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Boss")
	int Boss_MaxHP;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Boss")
	int Boss_CurrentHP;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Body;
	
	
	int GetBossMaxHp();

	int GetBossCurrentHp();

	void SetBossCurrentHp(int hp);
	
	void Pattern_1();
	void Pattern_2();
	void Pattern_3();
	void Pattern_4();

	void Test();
};
