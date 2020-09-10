// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <list>
#include <vector>
#include "Boss.generated.h"

class ATP_VirtualRealityPawn_Motion;

UCLASS()
class SOMTEMPLATE_VR_API ABoss : public AActor
{
	GENERATED_BODY()

private:
	ABoss();

	static ABoss* Boss_Instance;
	
	UPROPERTY(EditAnywhere)
	FVector Offset;
	
	UPROPERTY(EditAnywhere, Category = Boss_Projectile)
	TSubclassOf<class AProjectile> Pattern_1_Projectile;

	UPROPERTY(EditAnywhere, Category = Boss_Projectile)
	TSubclassOf<class AProjectile> Pattern_2_Rain_Projectile;

	UPROPERTY(EditAnywhere, Category = Boss_Projectile)
	TSubclassOf<class AProjectile> Pattern_2_Projectile;

	UPROPERTY(EditAnywhere, Category = Boss_Projectile)
	TSubclassOf<class AProjectile> Pattern_3_Projectile;

	UPROPERTY(EditAnywhere, Category = Boss_Projectile)
	TSubclassOf<class AProjectile> Pattern_4_First_Projectile;

	UPROPERTY(EditAnywhere, Category = Boss_Projectile)
	TSubclassOf<class AProjectile> Pattern_4_Second_Projectile;

	UPROPERTY(EditAnywhere, Category = Boss_Projectile)
	TSubclassOf<class AProjectile> Pattern_4_Third_Projectile;

	// Boss Pattern variable
	int CurrentPattern;

	double Pattern_Timer;

	int Pattern_2_Windmill_Rotation;

	int Pattern_4_Windmill_Rotation;

	std::vector<AProjectile*> Pattern_4_First_Projectile_Vector;
	std::vector<AProjectile*> Pattern_4_Second_Projectile_Vector;
	std::vector<AProjectile*> Pattern_4_Third_Projectile_Vector;


	// Boss Movement variable
	ATP_VirtualRealityPawn_Motion* Player_Pawn;

	FVector Boss_Initial_Position;

	int Boss_PreHP;

	int RandVector_Num;
	int Pre_RandVector_Num;

	float Movement_Speed;

	int Movement_Timer;
	
	int Dash_Counter;

	bool Is_Moving;

	FVector PlayerLocation;
	float Distance_P_To_B;
	FVector Direction_Vector;
	
public:	
	// Sets default values for this actor's properties
	//ABoss();

	
	static ABoss* GetInstance();

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

	void Pattern_1_Movement();
	void Pattern_2_Movement();
	void Pattern_3_Movement();
	void Pattern_4_Movement();

	FVector Random_Vector(int random_value);

	void Test();
};
