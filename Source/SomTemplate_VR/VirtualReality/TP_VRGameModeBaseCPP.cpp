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
        // 디버그 메시지를 5 초간 표시합니다.
        // "키" (첫 번째 인수) 값을 -1 로 하면 이 메시지를 절대 업데이트하거나 새로고칠 필요가 없음을 나타냅니다.
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello World, this is VRShootingGameMode!"));
    }
}
