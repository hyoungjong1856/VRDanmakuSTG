// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.


#include "DMGGameInstance.h"
#include "Engine/World.h"
#include "AudioDevice.h"
#include "Sound/AmbientSound.h"
#include "Sound/SoundWave.h"
#include "Sound/SoundBase.h"
#include "Sound/SoundCue.h"
#include "ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

UDMGGameInstance::UDMGGameInstance(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) { 
	// Sound

	static ConstructorHelpers::FObjectFinder<USoundWave> MainMenuSoundWave(TEXT("SoundWave'/Game/Sound/MainMenu.MainMenu'"));
	MainMenuSound = MainMenuSoundWave.Object;

	static ConstructorHelpers::FObjectFinder<USoundWave> InGameSoundWave(TEXT("SoundWave'/Game/Sound/InGame.InGame'"));
	InGameSound = InGameSoundWave.Object;

	static ConstructorHelpers::FObjectFinder<USoundWave> GameClearSoundWave(TEXT("SoundWave'/Game/Sound/GameClear.GameClear'"));
	GameClearSound = GameClearSoundWave.Object;

	static ConstructorHelpers::FObjectFinder<USoundWave> GameOverSoundWave(TEXT("SoundWave'/Game/Sound/GameOver.GameOver'"));
	GameOverSound = GameOverSoundWave.Object;

	MainMenuSound->SetPrecacheState(ESoundWavePrecacheState::NotStarted);
	InGameSound->SetPrecacheState(ESoundWavePrecacheState::NotStarted);
	GameClearSound->SetPrecacheState(ESoundWavePrecacheState::NotStarted);
	GameOverSound->SetPrecacheState(ESoundWavePrecacheState::NotStarted);

	MainMenuSoundComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("MainMenuSoundComponent"));
	
	static ConstructorHelpers::FObjectFinder<USoundCue> MainMenuSoundCueObject(TEXT("SoundCue'/Game/Sound/MainMenu_Cue.MainMenu_Cue'"));

	if (MainMenuSoundCueObject.Succeeded())
	{
		MainMenuSoundCue = MainMenuSoundCueObject.Object;
		MainMenuSoundComponent->SetSound(MainMenuSoundCueObject.Object);
	}

	MainMenuSoundComponent->SetIntParameter(FName("MainMenuSound"), 0);

	SoundVolumeRate = 0.5f;
	
	PlayerName = "";
}

void UDMGGameInstance::Init()
{
	// Ranking Dummy Data
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

void UDMGGameInstance::AddLetter(FString letter)
{
	if(PlayerName.Len() < 3)
		PlayerName = PlayerName.Append(letter);
}

void UDMGGameInstance::EraseLetter()
{
	if (PlayerName.Len() != 0)
	{
		if (PlayerName.Len() == 1)
			PlayerName = "";
		else
			PlayerName = PlayerName.Mid(0, PlayerName.Len() - 1);
	}
}

void UDMGGameInstance::AddRankingList()
{
	RankingData.insert(std::make_pair((AttackScore + TimeScore + SurviveScore), PlayerName));
}

FString UDMGGameInstance::GetPlayerName()
{
	return PlayerName;
}

void UDMGGameInstance::PlayMainMenuSound()
{	
	UGameplayStatics::PlaySound2D(this, MainMenuSound, 0.1f * SoundVolumeRate);
	UGameplayStatics::PlaySound2D(this, MainMenuSound, 0.0f);
	UGameplayStatics::PlaySound2D(this, MainMenuSound, 0.0f);
	UGameplayStatics::PlaySound2D(this, MainMenuSound, 0.0f);
	UGameplayStatics::PlaySound2D(this, MainMenuSound, 0.0f);
	UGameplayStatics::PlaySound2D(this, MainMenuSound, 0.0f);
	UGameplayStatics::PlaySound2D(this, MainMenuSound, 0.0f);
	UGameplayStatics::PlaySound2D(this, MainMenuSound, 0.0f);
	UGameplayStatics::PlaySound2D(this, MainMenuSound, 0.0f);
	UGameplayStatics::PlaySound2D(this, MainMenuSound, 0.0f);
	UGameplayStatics::PlaySound2D(this, MainMenuSound, 0.0f);
	UGameplayStatics::PlaySound2D(this, MainMenuSound, 0.0f);
	UGameplayStatics::PlaySound2D(this, MainMenuSound, 0.0f);
	UGameplayStatics::PlaySound2D(this, MainMenuSound, 0.0f);
	UGameplayStatics::PlaySound2D(this, MainMenuSound, 0.0f);
	UGameplayStatics::PlaySound2D(this, MainMenuSound, 0.0f);
	UGameplayStatics::PlaySound2D(this, MainMenuSound, 0.0f);
	UGameplayStatics::PlaySound2D(this, MainMenuSound, 0.0f);
	UGameplayStatics::PlaySound2D(this, MainMenuSound, 0.0f);
	UGameplayStatics::PlaySound2D(this, MainMenuSound, 0.0f); 
	UGameplayStatics::PlaySound2D(this, MainMenuSound, 0.0f);
	UGameplayStatics::PlaySound2D(this, MainMenuSound, 0.0f);
	UGameplayStatics::PlaySound2D(this, MainMenuSound, 0.0f);
	UGameplayStatics::PlaySound2D(this, MainMenuSound, 0.0f);
	UGameplayStatics::PlaySound2D(this, MainMenuSound, 0.0f);
	UGameplayStatics::PlaySound2D(this, MainMenuSound, 0.0f);
	UGameplayStatics::PlaySound2D(this, MainMenuSound, 0.0f);
	UGameplayStatics::PlaySound2D(this, MainMenuSound, 0.0f);
	UGameplayStatics::PlaySound2D(this, MainMenuSound, 0.0f);
	UGameplayStatics::PlaySound2D(this, MainMenuSound, 0.0f);

	MainMenuSound->SetPrecacheState(ESoundWavePrecacheState::Done);
}

bool UDMGGameInstance::CheckMainMenuSoundPlaying()
{
	return MainMenuSound->GetPrecacheState() == ESoundWavePrecacheState::Done ? true : false;
}

void UDMGGameInstance::ChangeMainMenuSoundState()
{
	MainMenuSound->SetPrecacheState(ESoundWavePrecacheState::NotStarted);
}

void UDMGGameInstance::PlayInGameSound()
{
	UGameplayStatics::PlaySound2D(this, InGameSound, 0.1f * SoundVolumeRate);
	InGameSound->SetPrecacheState(ESoundWavePrecacheState::Done);
}

bool UDMGGameInstance::CheckInGameSoundPlaying()
{
	return InGameSound->GetPrecacheState() == ESoundWavePrecacheState::Done ? true : false;
}

void UDMGGameInstance::PlayGameClearSound()
{
	UGameplayStatics::PlaySound2D(this, GameClearSound, 0.2f * SoundVolumeRate);
	GameClearSound->SetPrecacheState(ESoundWavePrecacheState::Done);

}

bool UDMGGameInstance::CheckGameClearSoundPlaying()
{
	return GameClearSound->GetPrecacheState() == ESoundWavePrecacheState::Done ? true : false;
}

void UDMGGameInstance::PlayGameOverSound()
{
	UGameplayStatics::PlaySound2D(this, GameOverSound, 0.1f * SoundVolumeRate);
	GameOverSound->SetPrecacheState(ESoundWavePrecacheState::Done);
}

bool UDMGGameInstance::CheckGameOverSoundPlaying()
{
	return GameOverSound->GetPrecacheState() == ESoundWavePrecacheState::Done ? true : false;
}

float UDMGGameInstance::GetSoundVolumeRate()
{
	return SoundVolumeRate;
}

void UDMGGameInstance::SetSoundVolumeRate(float value)
{
	SoundVolumeRate = value;
}


