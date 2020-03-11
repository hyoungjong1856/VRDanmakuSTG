// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.
// SomWorks :D // MIT LICENSE // Epic VR Template Convert C++ Open Source Project.

#include "Engine.h"
#include "TP_VRGameModeBaseCPP.h"
#include "TP_VirtualRealityPawn_Motion.h"
#include "TP_VirtualRealityPawn_GamePad.h"

ATP_VRGameModeBaseCPP::ATP_VRGameModeBaseCPP()
{
	// SomWorks :D // DefaultPawnClass
	DefaultPawnClass = ATP_VirtualRealityPawn_Motion::StaticClass();
}

void ATP_VRGameModeBaseCPP::StartPlay()
{
    Super::StartPlay();

    if (GEngine)
    {
        // ����� �޽����� 5 �ʰ� ǥ���մϴ�.
        // "Ű" (ù ��° �μ�) ���� -1 �� �ϸ� �� �޽����� ���� ������Ʈ�ϰų� ���ΰ�ĥ �ʿ䰡 ������ ��Ÿ���ϴ�.
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello World, this is VRShootingGameMode!"));
    }
}
