// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.
// SomWorks :D // MIT LICENSE // Epic VR Template Convert C++ Open Source Project.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Engine/GameInstance.h"
#include "UserConstant.h"
#include <map>
#include "TP_VirtualRealityPawn_Motion.generated.h"


UCLASS()
class SOMTEMPLATE_VR_API ATP_VirtualRealityPawn_Motion : public APawn
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VRTemplate|Components", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* RootScene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VRTemplate|Components", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* CameraBase;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VRTemplate|Components", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* VRCamera;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> PlayerHUDClass;

	UPROPERTY()
	class UWidgetComponent* Player_HUD;

	class UStaticMeshComponent* CollisionMeshComponent;
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VRTemplate|Variables", meta = (AllowPrivateAccess = "true"))
	class ATP_MotionController* LeftController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VRTemplate|Variables", meta = (AllowPrivateAccess = "true"))
	class ATP_MotionController* RightController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VRTemplate|Variables", meta = (AllowPrivateAccess = "true"))
	float ThumbDeadzone;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VRTemplate|Variables", meta = (AllowPrivateAccess = "true"))
	bool bRightStickDown;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VRTemplate|Variables", meta = (AllowPrivateAccess = "true"))
	bool bLeftStickDown;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VRTemplate|Variables", meta = (AllowPrivateAccess = "true"))
	float DefaultPlayerHeight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VRTemplate|Variables", meta = (AllowPrivateAccess = "true"))
	bool bUseControllerRollToRotate;
	
	typedef struct Movement_Control_Variable
	{
		float Movement_Speed;
		Player_Direction Previous_State;
		Player_Direction Current_State;
	} Movement_Control_Variable;
	
	Movement_Control_Variable X_Axis, Y_Axis, Z_Axis;

	bool IsPause;

	bool IsOutOfBoundary;

	int Time_Update_counter;

	FVector Position_When_Pressed;
	FVector Position_When_Released;

	bool WeaponMode;

	int Player_CurrentHP;
	int Player_MaxHP;

	int Player_CurrentLife;
	int Player_MaxLife;

	// Ranking
	int Score;

	std::map<int, FString> RankingData;

protected:
	
public:
	// Sets default values for this pawn's properties
	ATP_VirtualRealityPawn_Motion();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Resets HMD orientation and position in VR
	void OnResetVR();

	// Player movement function when have input
	void DirectionUp(float NewAxisValue);
	void DirectionDown(float NewAxisValue);
	void MotionControllerThumbLeft_Y(float NewAxisValue);
	void MotionControllerThumbLeft_X(float NewAxisValue);
	void MotionControllerThumbRight_Y(float NewAxisValue);
	void MotionControllerThumbRight_X(float NewAxisValue);

	// Control player's acceleration movement
	void AccelerationMovementControl(Movement_Control_Variable* Axis, FVector DirectionVector, float AxisValue);
	
	// Fire projectile
	UFUNCTION()
	void Fire();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GamePlay)
	FVector MuzzleOffset;

	UPROPERTY(EditAnywhere, Category = Projectile)
	TSubclassOf<class AProjectile> ProjectileClass;

	void Boundary_Check(float *AxisValue);

	void Pause();

	void Attack_Mode_Change_Press();
	void Attack_Mode_Change_Release();

	UFUNCTION(BlueprintCallable)
	void SetPlayerCurrentHP(int hp);

	UFUNCTION(BlueprintCallable)
	int GetPlayerCurrentHP();

	UFUNCTION(BlueprintCallable)
	void SetPlayerCurrentLife(int life);

	UFUNCTION(BlueprintCallable)
	int GetPlayerCurrentLife();

	UFUNCTION(BlueprintCallable)
	void SetScore(int score);

	UFUNCTION(BlueprintCallable)
	int GetScore();

	UFUNCTION(BlueprintCallable)
	int GetRankingScore(int index);

	UFUNCTION(BlueprintCallable)
	FString GetRankingName(int index);

	void SelfDamage();

	void Test();
	
};
