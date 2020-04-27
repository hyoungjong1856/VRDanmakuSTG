// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.
// SomWorks :D // MIT LICENSE // Epic VR Template Convert C++ Open Source Project.

#include "TP_VirtualRealityPawn_Motion.h"
#include "TP_MotionController.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "GameFramework/InputSettings.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/SceneComponent.h"
#include "MotionControllerComponent.h"
#include "Projectile.h"

// Sets default values
ATP_VirtualRealityPawn_Motion::ATP_VirtualRealityPawn_Motion()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	UE_LOG(LogTemp, Warning, TEXT("player initialize"));
	// SomWorks :D // Create Components Initialize
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	CameraBase = CreateDefaultSubobject<USceneComponent>(TEXT("VROrigin"));
	VRCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	RootComponent = RootScene;
	CameraBase->SetupAttachment(RootComponent);
	VRCamera->SetupAttachment(CameraBase);

	ThumbDeadzone = 0.7f;
	bRightStickDown = false;
	bLeftStickDown = false;
	DefaultPlayerHeight = 180.0f;
	bUseControllerRollToRotate = false;

	// Member Variable (Movement_Speed, Player_Direction, Previous_State)
	X_Axis = { 0.0f, Player_Direction::RIGHT, Player_Direction::RIGHT };
	Y_Axis = { 0.0f, Player_Direction::FORWARD, Player_Direction::FORWARD };
	Z_Axis = { 0.0f, Player_Direction::UP, Player_Direction::UP };

}

// Called when the game starts or when spawned
void ATP_VirtualRealityPawn_Motion::BeginPlay()
{
	Super::BeginPlay();
	//UE_LOG(LogTemp, Warning, TEXT("플레이어게임시작"));
	// Epic Comment :D // Setup Player Height for various Platforms (PS4, Vive, Oculus)
	FName DeviceName = UHeadMountedDisplayFunctionLibrary::GetHMDDeviceName();

	if (DeviceName == "SteamVR" || DeviceName == "OculusHMD")
	{
		// Epic Comment :D // Windows (Oculus / Vive)
		UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(EHMDTrackingOrigin::Floor);
	}
	else
	{
		// Epic Comment :D // PS4
		UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(EHMDTrackingOrigin::Eye);
		CameraBase->AddLocalOffset(FVector(0.0f, 0.0f, DefaultPlayerHeight));

		// Epic Comment :D // Force Enable. PS Move lacks thumbstick input, this option lets user adjust pawn orientation during teleport using controller Roll motion.
		bUseControllerRollToRotate = true;
	}

	// Epic Comment :D // Spawn and attach both motion controllers

	const FTransform SpawnTransform = FTransform(FRotator(0.0f, 0.0f, 0.0f), FVector(0.0f, 0.0f, 0.0f), FVector(1.0f, 1.0f, 1.0f)); // = FTransform::Identity;
	FAttachmentTransformRules AttachRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, false);

	// Epic Comment :D // "Hand" is available by checking "Expose on Spawn" in the variable on BP_MotionController.
	// SomWorks :D //  Expose on Spawn Variable parameter setup in c++ -> Use SpawnActorDeferred
	LeftController = GetWorld()->SpawnActorDeferred<ATP_MotionController>(ATP_MotionController::StaticClass(), SpawnTransform, this, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	if (LeftController)
	{
		// SomWorks :D // ...setstuff here..then finish spawn..
		LeftController->Hand = EControllerHand::Left;
		LeftController->FinishSpawning(SpawnTransform); // UGameplayStatics::FinishSpawningActor(LeftController, SpawnTransform);
		LeftController->AttachToComponent(CameraBase, AttachRules);
	}

	RightController = GetWorld()->SpawnActorDeferred<ATP_MotionController>(ATP_MotionController::StaticClass(), SpawnTransform, this, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	if (RightController)
	{
		RightController->Hand = EControllerHand::Right;
		RightController->FinishSpawning(SpawnTransform);
		RightController->AttachToComponent(CameraBase, AttachRules);
	}
}

// Called every frame
void ATP_VirtualRealityPawn_Motion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATP_VirtualRealityPawn_Motion::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up gameplay key bindings
	check(PlayerInputComponent);

	// SomWorks :D // Bind Recenter VR events
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ATP_VirtualRealityPawn_Motion::OnResetVR);

	// Player Movement Input Axises
	PlayerInputComponent->BindAxis(TEXT("DirectionUp"), this, &ATP_VirtualRealityPawn_Motion::DirectionUp);
	PlayerInputComponent->BindAxis(TEXT("DirectionDown"), this, &ATP_VirtualRealityPawn_Motion::DirectionDown);
	PlayerInputComponent->BindAxis(TEXT("MotionControllerThumbLeft_Y"), this, &ATP_VirtualRealityPawn_Motion::MotionControllerThumbLeft_Y);
	PlayerInputComponent->BindAxis(TEXT("MotionControllerThumbLeft_X"), this, &ATP_VirtualRealityPawn_Motion::MotionControllerThumbLeft_X);
	PlayerInputComponent->BindAxis(TEXT("MotionControllerThumbRight_Y"), this, &ATP_VirtualRealityPawn_Motion::MotionControllerThumbRight_Y);
	PlayerInputComponent->BindAxis(TEXT("MotionControllerThumbRight_X"), this, &ATP_VirtualRealityPawn_Motion::MotionControllerThumbRight_X);

	// Fire Input
	InputComponent->BindAction("Fire", IE_Pressed, this, &ATP_VirtualRealityPawn_Motion::Fire);



}

void ATP_VirtualRealityPawn_Motion::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

/**
* @brief when have input player move accelerate, 
*		 when have not input player move decelerate
*
* @param float NewAxisValue : input value
*/
void ATP_VirtualRealityPawn_Motion::DirectionUp(float NewAxisValue)
{
	// When have input
	if (!(NewAxisValue == 0.0f))
	{
		if (NewAxisValue > 0.0f) {
			Z_Axis.Previous_State = Z_Axis.Current_State;
			Z_Axis.Current_State = Player_Direction::UP;
		}
		AccelerationMovementControl(&Z_Axis, GetActorUpVector(), NewAxisValue);
	}

	// When have not input
	if ((NewAxisValue == 0.0f) && !(Z_Axis.Movement_Speed == 0.0f) && (Z_Axis.Current_State == Player_Direction::UP)) {
		Z_Axis.Movement_Speed -= MOVEMENT_DECELERATION_SPEED;
		if (Z_Axis.Movement_Speed < 0)
			Z_Axis.Movement_Speed = 0.0f;
		RootScene->AddWorldOffset(GetActorUpVector() * Z_Axis.Movement_Speed);
	}
}

void ATP_VirtualRealityPawn_Motion::DirectionDown(float NewAxisValue)
{
	// When have input
	if (!(NewAxisValue == 0.0f))
	{
		if (NewAxisValue < 0.0f) {
			Z_Axis.Previous_State = Z_Axis.Current_State;
			Z_Axis.Current_State = Player_Direction::DOWN;
		}
		AccelerationMovementControl(&Z_Axis, GetActorUpVector(), NewAxisValue);
	}
	
	// When have not input
	if ((NewAxisValue == 0.0f) && !(Z_Axis.Movement_Speed == 0.0f) && (Z_Axis.Current_State == Player_Direction::DOWN)) {
		Z_Axis.Movement_Speed -= MOVEMENT_DECELERATION_SPEED;
		if (Z_Axis.Movement_Speed < 0)
			Z_Axis.Movement_Speed = 0.0f;

		RootScene->AddWorldOffset(GetActorUpVector() * -1 * Z_Axis.Movement_Speed);
	}
}

void ATP_VirtualRealityPawn_Motion::MotionControllerThumbLeft_Y(float NewAxisValue)
{
	// When have input
	if (!(NewAxisValue == 0.0f))
	{
		if (NewAxisValue > 0.0f) {
			Y_Axis.Previous_State = Y_Axis.Current_State;
			Y_Axis.Current_State = Player_Direction::FORWARD;
		}
		else
		{
			Y_Axis.Previous_State = Y_Axis.Current_State;
			Y_Axis.Current_State = Player_Direction::BACK;
		}
		AccelerationMovementControl(&Y_Axis, GetActorForwardVector(), NewAxisValue);
	}

	// When have not input
	if ((NewAxisValue == 0.0f) && !(Y_Axis.Movement_Speed == 0.0f)) {
		Y_Axis.Movement_Speed -= MOVEMENT_DECELERATION_SPEED;
		if (Y_Axis.Movement_Speed < 0)
			Y_Axis.Movement_Speed = 0.0f;

		if(Y_Axis.Current_State == Player_Direction::FORWARD)
			RootScene->AddWorldOffset(GetActorForwardVector() * Y_Axis.Movement_Speed);
		else
			RootScene->AddWorldOffset(GetActorForwardVector() * -1 * Y_Axis.Movement_Speed);
	}
}

void ATP_VirtualRealityPawn_Motion::MotionControllerThumbLeft_X(float NewAxisValue)
{
	// When have input
	if (!(NewAxisValue == 0.0f))
	{
		if (NewAxisValue > 0.0f) {
			X_Axis.Previous_State = X_Axis.Current_State;
			X_Axis.Current_State = Player_Direction::RIGHT;
		}
		else
		{
			 X_Axis.Previous_State = X_Axis.Current_State;
			 X_Axis.Current_State = Player_Direction::LEFT;
		}
		AccelerationMovementControl(&X_Axis, GetActorRightVector(), NewAxisValue);
	}

	// When have not input
	if ((NewAxisValue == 0.0f) && !(X_Axis.Movement_Speed == 0.0f)) {
		X_Axis.Movement_Speed -= MOVEMENT_DECELERATION_SPEED;
		if (X_Axis.Movement_Speed < 0)
			X_Axis.Movement_Speed = 0.0f;

		if (X_Axis.Current_State == Player_Direction::RIGHT)
			RootScene->AddWorldOffset(GetActorRightVector() * X_Axis.Movement_Speed);
		else
			RootScene->AddWorldOffset(GetActorRightVector() * -1 * X_Axis.Movement_Speed);
	}
}

void ATP_VirtualRealityPawn_Motion::MotionControllerThumbRight_Y(float NewAxisValue)
{
}

void ATP_VirtualRealityPawn_Motion::MotionControllerThumbRight_X(float NewAxisValue)
{
	if (!(NewAxisValue == 0.0f))
	{
		UE_LOG(LogTemp, Warning, TEXT("rotation"));
		FRotator Rootrotator;
		Rootrotator.Add(0.0f, NewAxisValue, 0.0f);

		UE_LOG(LogTemp, Warning, TEXT("ROTATOR %f, %f, %f,"), GetActorRotation().Pitch,  GetActorRotation().Yaw, GetActorRotation().Roll);

		SetActorRotation(GetActorRotation() + (Rootrotator * ROTATION_X_SPEED));
		// Same code
		// RootScene->AddWorldRotation(Rootrotator * ROTATION_X_SPEED);
	}
}

/**
* @brief set player's accelerate movement
*
* @param Movement_Control_Variable* Axis	: axis direction
*        FVector DirectionVector			: criteria direction
*        float AxisValue					: input value
*/
void ATP_VirtualRealityPawn_Motion::AccelerationMovementControl(Movement_Control_Variable* Axis, FVector DirectionVector, float AxisValue)
{
	
	if (Axis->Previous_State != Axis->Current_State) {
		Axis->Movement_Speed = 0.0f;
	}	

	//UE_LOG(LogTemp, Warning, TEXT("previous %d,"), Z_Axis.Previous_State);

	Axis->Movement_Speed += MOVEMENT_ACCELERATION_SPEED;
	if (Axis->Movement_Speed > MOVEMENT_MAX_SPEED)
		Axis->Movement_Speed = MOVEMENT_MAX_SPEED;
	RootScene->AddWorldOffset(DirectionVector * AxisValue * Axis->Movement_Speed);
}

void ATP_VirtualRealityPawn_Motion::Fire()
{
	FActorSpawnParameters SpawnParams;

	
	if (ProjectileClass)
	{
		FVector MuzzleLocation = GetActorLocation() + FTransform(GetActorRotation()).TransformVector(MuzzleOffset);
		FRotator MuzzleRotation = GetActorRotation();

		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;
			AProjectile* Projectile = World->SpawnActor<AProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
			if (Projectile)
			{
				FVector LaunchDirection = MuzzleRotation.Vector();
				Projectile->FireInDirection(LaunchDirection);
				UE_LOG(LogTemp, Warning, TEXT("x:%f, y:%f, z:%f"), LaunchDirection.X, LaunchDirection.Y, LaunchDirection.Z);
			}
		}
		
		UE_LOG(LogTemp, Warning, TEXT("fire"));
	}
}

void ATP_VirtualRealityPawn_Motion::ShowText()
{
	UE_LOG(LogTemp, Warning, TEXT("showText"));
}
