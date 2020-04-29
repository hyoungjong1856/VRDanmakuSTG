// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.
// SomWorks :D // MIT LICENSE // Epic VR Template Convert C++ Open Source Project.

#include "TP_VRGameModeBaseCPP.h"
#include "Engine.h"
#include "TP_VirtualRealityPawn_Motion.h"
#include "TP_VirtualRealityPawn_GamePad.h"
#include "Projectile.h"



ATP_VRGameModeBaseCPP::ATP_VRGameModeBaseCPP()
{
	// SomWorks :D // DefaultPawnClass
	DefaultPawnClass = ATP_VirtualRealityPawn_Motion::StaticClass();

    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    UE_LOG(LogTemp, Warning, TEXT("gamemode start"));
    //VR_Player = ATP_VirtualRealityPawn_Motion::StaticClass();
    //ATP_VirtualRealityPawn_Motion* VR_Player = CreateDefaultSubobject<ATP_VirtualRealityPawn_Motion>(TEXT("AB"));
    

}

void ATP_VRGameModeBaseCPP::StartPlay()
{
    Super::StartPlay();
    //UE_LOG(LogTemp, Warning, TEXT("start"));
    if (GEngine)
    {
        // ����� �޽����� 5 �ʰ� ǥ���մϴ�.
        // "Ű" (ù ��° �μ�) ���� -1 �� �ϸ� �� �޽����� ���� ������Ʈ�ϰų� ���ΰ�ĥ �ʿ䰡 ������ ��Ÿ���ϴ�.
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello World, this is VRShootingGameMode!"));
    }
    /*
    ACharacter* character = GetWorld()->GetFirstPlayerController()->GetCharacter();
    ATP_VirtualRealityPawn_Motion* VR_Player = Cast< ATP_VirtualRealityPawn_Motion>(character);
    VR_Player->Fire();
    */
}

void ATP_VRGameModeBaseCPP::Tick(float DeltaTime)
{
   // UE_LOG(LogTemp, Warning, TEXT("tick"));
}
