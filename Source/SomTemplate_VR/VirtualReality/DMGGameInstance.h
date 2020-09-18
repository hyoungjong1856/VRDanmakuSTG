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


	// Function
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

	// Sound
	UFUNCTION(BlueprintCallable)
	void PlayMainMenuSound();

	UFUNCTION(BlueprintCallable)
	void StopMainMenuSound();

	UFUNCTION(BlueprintCallable)
	bool CheckMainMenuSoundPlaying();

	UFUNCTION(BlueprintCallable)
	void ChangeMainMenuSoundState();

	UFUNCTION(BlueprintCallable)
	int CheckMainMenuSoundState();


	UFUNCTION(BlueprintCallable)
	void PlayInGameSound();

	UFUNCTION(BlueprintCallable)
	void StopInGameSound();

	UFUNCTION(BlueprintCallable)
	bool CheckInGameSoundPlaying();


	UFUNCTION(BlueprintCallable)
	void PlayGameClearSound();

	UFUNCTION(BlueprintCallable)
	void StopGameClearSound();

	UFUNCTION(BlueprintCallable)
	bool CheckGameClearSoundPlaying();


	UFUNCTION(BlueprintCallable)
	void PlayGameOverSound();

	UFUNCTION(BlueprintCallable)
	void StopGameOverSound();

	UFUNCTION(BlueprintCallable)
	bool CheckGameOverSoundPlaying();


	UFUNCTION(BlueprintCallable)
	float GetSoundVolumeRate();

	UFUNCTION(BlueprintCallable)
	void SetSoundVolumeRate(float value);
};
