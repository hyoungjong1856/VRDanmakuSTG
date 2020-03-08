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

// Sets default values
ATP_VirtualRealityPawn_Motion::ATP_VirtualRealityPawn_Motion()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// SomWorks :D // Create Components Initialize
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	CameraBase = CreateDefaultSubobject<USceneComponent>(TEXT("VROrigin"));
	VRCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	RootComponent = RootScene;
	CameraBase->SetupAttachment(RootComponent);
	VRCamera->SetupAttachment(CameraBase);

	FadeOutDuration = 0.1f;
	FadeInDuration = 0.2f;
	bIsTeleporting = false;
	TeleportFadeColor = FColor::Black;
	ThumbDeadzone = 0.7f;
	bRightStickDown = false;
	bLeftStickDown = false;
	DefaultPlayerHeight = 180.0f;
	bUseControllerRollToRotate = false;

	X_Axis = { 0.0f, Player_Direction::RIGHT, Player_Direction::RIGHT };
	Y_Axis = { 0.0f, Player_Direction::FORWARD, Player_Direction::FORWARD };
	Z_Axis = { 0.0f, Player_Direction::UP, Player_Direction::UP };
}

// Called when the game starts or when spawned
void ATP_VirtualRealityPawn_Motion::BeginPlay()
{
	Super::BeginPlay();

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
	/*
	float MotionController_Left_Thumbstick_X = InputComponent->GetAxisValue(TEXT("MotionControllerThumbLeft_X")); // = UGameplayStatics::GetPlayerController(GetWorld(), 0)->PlayerInput->GetKeyValue(EKeys::MotionController_Left_Thumbstick_X);
	float MotionController_Left_Thumbstick_Y = InputComponent->GetAxisValue(TEXT("MotionControllerThumbLeft_Y")); // = UGameplayStatics::GetPlayerController(GetWorld(), 0)->PlayerInput->GetKeyValue(EKeys::MotionController_Left_Thumbstick_Y);
	float MotionController_Right_Thumbstick_X = InputComponent->GetAxisValue(TEXT("MotionControllerThumbRight_X")); // = UGameplayStatics::GetPlayerController(GetWorld(), 0)->PlayerInput->GetKeyValue(EKeys::MotionController_Right_Thumbstick_X);
	float MotionController_Right_Thumbstick_Y = InputComponent->GetAxisValue(TEXT("MotionControllerThumbRight_Y")); // = UGameplayStatics::GetPlayerController(GetWorld(), 0)->PlayerInput->GetKeyValue(EKeys::MotionController_Right_Thumbstick_Y);

	// Epic Comment :D // Left Hand Teleport Rotation
	if (LeftController->GetIsTeleporterActive())
	{
		FRotator LeftTeleportRotation = GetRotationFromInput(MotionController_Left_Thumbstick_Y, MotionController_Left_Thumbstick_X, LeftController);
		LeftController->SetTeleportRotation(LeftTeleportRotation);
	}

	// Epic Comment :D // Right Hand Teleport Rotation
	if (RightController->GetIsTeleporterActive())
	{
		FRotator RightTeleportRotation = GetRotationFromInput(MotionController_Right_Thumbstick_Y, MotionController_Right_Thumbstick_X, RightController);
		RightController->SetTeleportRotation(RightTeleportRotation);
	}
	*/
}

// Called to bind functionality to input
void ATP_VirtualRealityPawn_Motion::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up gameplay key bindings
	check(PlayerInputComponent);

	// SomWorks :D // Bind Recenter VR events
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ATP_VirtualRealityPawn_Motion::OnResetVR);

	// SomWorks :D // Bind Input Axises
	PlayerInputComponent->BindAxis(TEXT("DirectionUp"), this, &ATP_VirtualRealityPawn_Motion::DirectionUp);
	PlayerInputComponent->BindAxis(TEXT("DirectionDown"), this, &ATP_VirtualRealityPawn_Motion::DirectionDown);
	PlayerInputComponent->BindAxis(TEXT("MotionControllerThumbLeft_Y"), this, &ATP_VirtualRealityPawn_Motion::MotionControllerThumbLeft_Y);
	PlayerInputComponent->BindAxis(TEXT("MotionControllerThumbLeft_X"), this, &ATP_VirtualRealityPawn_Motion::MotionControllerThumbLeft_X);
	PlayerInputComponent->BindAxis(TEXT("MotionControllerThumbRight_Y"), this, &ATP_VirtualRealityPawn_Motion::MotionControllerThumbRight_Y);
	PlayerInputComponent->BindAxis(TEXT("MotionControllerThumbRight_X"), this, &ATP_VirtualRealityPawn_Motion::MotionControllerThumbRight_X);

	// Movement keyboard input



}

void ATP_VirtualRealityPawn_Motion::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ATP_VirtualRealityPawn_Motion::DirectionUp(float NewAxisValue)
{
	if (!(NewAxisValue == 0.0f))
	{
		if (NewAxisValue > 0.0f) {
			Z_Axis.Previous_State = Z_Axis.Current_State;
			Z_Axis.Current_State = Player_Direction::UP;
		}
		MovementControl(&Z_Axis, GetActorUpVector(), NewAxisValue);
	}

	if ((NewAxisValue == 0.0f) && !(Z_Axis.Movement_Accel == 0.0f) && (Z_Axis.Current_State == Player_Direction::UP)) {
		Z_Axis.Movement_Accel -= MOVEMENT_DECELERATION_SPEED;
		if (Z_Axis.Movement_Accel < 0)
			Z_Axis.Movement_Accel = 0.0f;
		RootScene->AddWorldOffset(GetActorUpVector() * Z_Axis.Movement_Accel);
	}
}

void ATP_VirtualRealityPawn_Motion::DirectionDown(float NewAxisValue)
{
	if (!(NewAxisValue == 0.0f))
	{
		if (NewAxisValue < 0.0f) {
			Z_Axis.Previous_State = Z_Axis.Current_State;
			Z_Axis.Current_State = Player_Direction::DOWN;
		}
		MovementControl(&Z_Axis, GetActorUpVector(), NewAxisValue);
	}
	
	if ((NewAxisValue == 0.0f) && !(Z_Axis.Movement_Accel == 0.0f) && (Z_Axis.Current_State == Player_Direction::DOWN)) {
		Z_Axis.Movement_Accel -= MOVEMENT_DECELERATION_SPEED;
		if (Z_Axis.Movement_Accel < 0)
			Z_Axis.Movement_Accel = 0.0f;

		RootScene->AddWorldOffset(GetActorUpVector() * -1 * Z_Axis.Movement_Accel);
	}
}

void ATP_VirtualRealityPawn_Motion::MotionControllerThumbLeft_Y(float NewAxisValue)
{
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
		MovementControl(&Y_Axis, GetActorForwardVector(), NewAxisValue);
	}
	if ((NewAxisValue == 0.0f) && !(Y_Axis.Movement_Accel == 0.0f)) {
		Y_Axis.Movement_Accel -= MOVEMENT_DECELERATION_SPEED;
		if (Y_Axis.Movement_Accel < 0)
			Y_Axis.Movement_Accel = 0.0f;

		if(Y_Axis.Current_State == Player_Direction::FORWARD)
			RootScene->AddWorldOffset(GetActorForwardVector() * Y_Axis.Movement_Accel);
		else
			RootScene->AddWorldOffset(GetActorForwardVector() * -1 * Y_Axis.Movement_Accel);
	}
}

void ATP_VirtualRealityPawn_Motion::MotionControllerThumbLeft_X(float NewAxisValue)
{
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
		MovementControl(&X_Axis, GetActorRightVector(), NewAxisValue);
	}
	if ((NewAxisValue == 0.0f) && !(X_Axis.Movement_Accel == 0.0f)) {
		X_Axis.Movement_Accel -= MOVEMENT_DECELERATION_SPEED;
		if (X_Axis.Movement_Accel < 0)
			X_Axis.Movement_Accel = 0.0f;

		if (X_Axis.Current_State == Player_Direction::RIGHT)
			RootScene->AddWorldOffset(GetActorRightVector() * X_Axis.Movement_Accel);
		else
			RootScene->AddWorldOffset(GetActorRightVector() * -1 * X_Axis.Movement_Accel);
	}
}

void ATP_VirtualRealityPawn_Motion::MotionControllerThumbRight_Y(float NewAxisValue)
{
}

void ATP_VirtualRealityPawn_Motion::MotionControllerThumbRight_X(float NewAxisValue)
{
	if (!(NewAxisValue == 0.0f))
	{
		FRotator Rootrotator;
		Rootrotator.Add(0.0f, NewAxisValue, 0.0f);

		RootScene->AddWorldRotation(Rootrotator * ROTATION_X_SPEED);
		//UE_LOG(LogTemp, Warning, TEXT("ROTATOR %f,"), Rootrotator.Yaw);
	}
}

void ATP_VirtualRealityPawn_Motion::MovementControl(Movement_Control_Variable* Axis, FVector DirectionVector, float AxisValue)
{
	
	if (Axis->Previous_State != Axis->Current_State) {
		Axis->Movement_Accel = 0.0f;
	}	

	UE_LOG(LogTemp, Warning, TEXT("previous %d,"), Z_Axis.Previous_State);
	UE_LOG(LogTemp, Warning, TEXT("current %d,"), Z_Axis.Current_State);
	UE_LOG(LogTemp, Warning, TEXT("accel %f,"), Axis->Movement_Accel);
	Axis->Movement_Accel += MOVEMENT_ACCELERATION_SPEED;
	if (Axis->Movement_Accel > MOVEMENT_MAX_SPEED)
		Axis->Movement_Accel = MOVEMENT_MAX_SPEED;
	RootScene->AddWorldOffset(DirectionVector * AxisValue * Axis->Movement_Accel);
}

FRotator ATP_VirtualRealityPawn_Motion::GetRotationFromInput(float UpAxis, float RightAxis, ATP_MotionController* MotionController)
{
	// Epic Comment :D // Use PSVR method (lacking thumbstick) or the Desktop implementation with thumbstick support.
	if (bUseControllerRollToRotate)
	{
		// Epic Comment :D // Get Roll difference since we initiated the teleport. (Allows Wrist to change the pawn orientation when teleporting)
		FTransform InitialControllerTransform = FTransform(MotionController->GetInitialControllerRotation(), FVector(0.0f, 0.0f, 0.0f), FVector(1.0f, 1.0f, 1.0f));
		FTransform ConvertTransformResult = UKismetMathLibrary::ConvertTransformToRelative(InitialControllerTransform, MotionController->GetMotionController()->GetComponentTransform());

		// Epic Comment :D // Multiply to make 180 spins of orientation much easier.
		float ConvertTransRotationRoll = ConvertTransformResult.Rotator().Roll * 3;

		// Epic Commnet :D // Add current rotation to the controller adjustment
		float ActorYaw = GetActorRotation().Yaw;

		// Epic Comment :D // Roll of controller gets converted to Yaw for pawn orientation.
		return FRotator(0.0f, ConvertTransRotationRoll + ActorYaw, 0.0f);
	}
	else
	{
		// Epic Comment :D // Rotate input X+Y to always point forward relative to the current pawn rotation.
		FVector InputCenterNormal = UKismetMathLibrary::Normal(FVector(UpAxis, RightAxis, 0.0f));
		FVector InputNormalRotateResult = FRotator(0.0f, GetActorRotation().Yaw, 0.0f).RotateVector(InputCenterNormal);
		FRotator InputRotXResult = UKismetMathLibrary::MakeRotFromX(InputNormalRotateResult);

		// Epic Comment :D // Check whether thumb is near center (to ignore rotation overrides)
		// Epic Comment :D // ThumbDeadzone : Adjust this value to narrow the 'deadzone' center
		bool bCheckThumbNearCenter = (UKismetMathLibrary::Abs(UpAxis) + UKismetMathLibrary::Abs(RightAxis)) >= ThumbDeadzone;

		// Epic Comment :D // Select the rotation created by thumbpad input or use current pawn rotation
		// Epic Comment :D // GetActorRotation() : Use Default rotation if thumb is near center of the pad
		return UKismetMathLibrary::SelectRotator(InputRotXResult, GetActorRotation(), bCheckThumbNearCenter);
	}
}

// Epic Comment :D // Handle Teleportation
void ATP_VirtualRealityPawn_Motion::ExecuteTeleportation(ATP_MotionController* MotionController)
{
	if (!bIsTeleporting)
	{
		if (MotionController->GetIsValidTeleportDestination())
		{
			bIsTeleporting = true;
			
			UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraFade(0.0f, 1.0f, FadeOutDuration, TeleportFadeColor, false, true);
			FTimerDelegate FadeDelegate;// = FTimerDelegate::CreateUObject(this, &ATP_VirtualRealityPawn_Motion::TeleportActor, MotionController);
			FadeDelegate.BindUFunction(this, FName("TeleportActor"), MotionController);
			GetWorldTimerManager().SetTimer(FadeTimerHandle, FadeDelegate, FadeOutDuration, false);
		}
		else
		{
			MotionController->DisableTeleporter();
		}
	}
}

void ATP_VirtualRealityPawn_Motion::TeleportActor(ATP_MotionController* MotionController)
{
	MotionController->DisableTeleporter();

	FVector DestLocation, DevicePosition;
	FRotator DestRotation, DeviceRotation;
	MotionController->GetTeleportDestination(DestLocation, DestRotation);

	UHeadMountedDisplayFunctionLibrary::GetOrientationAndPosition(DeviceRotation, DevicePosition);

	TeleportTo(DestLocation + 10, DestRotation);

	UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraFade(1.0f, 0.0f, FadeInDuration, TeleportFadeColor, false, false);

	bIsTeleporting = false;
	GetWorldTimerManager().ClearTimer(FadeTimerHandle);
}