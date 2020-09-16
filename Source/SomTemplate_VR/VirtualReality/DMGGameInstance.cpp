// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.


#include "DMGGameInstance.h"

UDMGGameInstance::UDMGGameInstance(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {   }

void UDMGGameInstance::Init()
{
	
	// Dummy Data
	RankingData.insert(std::make_pair(23456, "WOW"));
	RankingData.insert(std::make_pair(12345, "LUX"));
	RankingData.insert(std::make_pair(9999, "CAT"));
}

void UDMGGameInstance::AddRankingData(int score, FString name)
{
	RankingData.insert(std::make_pair(score, name));
}

int UDMGGameInstance::GetRankingScore(int index)
{
	int score[3] = { 0 };
	int i = 0;
	for (auto iter = RankingData.begin(); iter != RankingData.end(); iter++)
	{
		if (i < 3)
		{
			score[i] = iter->first;
			i++;
		}
	}

	return score[index];
}

FString UDMGGameInstance::GetRankingName(int index)
{
	FString name[3] = { "" };
	int i = 0;
	for (auto iter = RankingData.begin(); iter != RankingData.end(); iter++)
	{
		if (i < 3)
		{
			name[i] = iter->second;
			i++;
		}
	}

	return name[index];
}

int UDMGGameInstance::GetAttackScore()
{
	return AttackScore;
}

void UDMGGameInstance::SetAttackScore(int score)
{
	AttackScore = score;
}

int UDMGGameInstance::GetTimeScore()
{
	return TimeScore;
}

void UDMGGameInstance::SetTimeScore(float playtime)
{
	if (playtime < 180)
		TimeScore = 10000;
	else if (playtime < 300)
		TimeScore = 5000;
	else
		TimeScore = 0;
}

int UDMGGameInstance::GetSurviveScore()
{
	return SurviveScore;
}

void UDMGGameInstance::SetSurviveScore(int hp, int life)
{
	SurviveScore = (hp * 500) + (life * 3000);
}


