// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include <map>
#include "DMGGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SOMTEMPLATE_VR_API UDMGGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UDMGGameInstance(const FObjectInitializer& ObjectInitializer);

	virtual void Init() override;

	std::map<int, FString, std::greater<int>> RankingData;

	int AttackScore;
	int TimeScore;
	int SurviveScore;

	void AddRankingData(int score, FString name);
	
	UFUNCTION(BlueprintCallable)
	int GetRankingScore(int index);

	UFUNCTION(BlueprintCallable)
	FString GetRankingName(int index);

	UFUNCTION(BlueprintCallable)
	int GetAttackScore();

	UFUNCTION(BlueprintCallable)
	void SetAttackScore(int score);

	UFUNCTION(BlueprintCallable)
	int GetTimeScore();

	UFUNCTION(BlueprintCallable)
	void SetTimeScore(float playtime);

	UFUNCTION(BlueprintCallable)
	int GetSurviveScore();

	UFUNCTION(BlueprintCallable)
	void SetSurviveScore(int hp, int life);
};
