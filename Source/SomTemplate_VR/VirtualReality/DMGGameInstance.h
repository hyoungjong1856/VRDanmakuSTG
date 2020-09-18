// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"
#include "Sound/SoundConcurrency.h"
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

	// Sound
	UPROPERTY()
	class USoundWave* MainMenuSound;

	UPROPERTY()
	class USoundWave* InGameSound;

	UPROPERTY()
	class USoundWave* GameClearSound;

	UPROPERTY()
	class USoundWave* GameOverSound;

	float SoundVolumeRate;

	class AAmbientSound* newSound;

	UAudioComponent* MainMenuSoundComponent;

	USoundCue* MainMenuSoundCue;

	// Player Name
	FString PlayerName;


	// Function

	// Score
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

	// Player Name
	// Add letter
	UFUNCTION(BlueprintCallable)
	void AddLetter(FString letter);

	// Erase letter
	UFUNCTION(BlueprintCallable)
	void EraseLetter();

	// Add to Ranking List
	UFUNCTION(BlueprintCallable)
	void AddRankingList();

	UFUNCTION(BlueprintCallable)
	FString GetPlayerName();

	// Sound
	UFUNCTION(BlueprintCallable)
	void PlayMainMenuSound();

	UFUNCTION(BlueprintCallable)
	bool CheckMainMenuSoundPlaying();

	UFUNCTION(BlueprintCallable)
	void ChangeMainMenuSoundState();


	UFUNCTION(BlueprintCallable)
	void PlayInGameSound();

	UFUNCTION(BlueprintCallable)
	bool CheckInGameSoundPlaying();


	UFUNCTION(BlueprintCallable)
	void PlayGameClearSound();

	UFUNCTION(BlueprintCallable)
	bool CheckGameClearSoundPlaying();


	UFUNCTION(BlueprintCallable)
	void PlayGameOverSound();

	UFUNCTION(BlueprintCallable)
	bool CheckGameOverSoundPlaying();


	UFUNCTION(BlueprintCallable)
	float GetSoundVolumeRate();

	UFUNCTION(BlueprintCallable)
	void SetSoundVolumeRate(float value);
};
