// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "RPGTypes.h"
#include "RPGLevelingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_BETA_API URPGLevelingComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 CurrentLevel = 1.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float CurrentExperience = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float LevelMaxExperience = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UDataTable* LevelingDataTable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TMap<int32, float> LevelingData;
	
public:	
	// Sets default values for this component's properties
	URPGLevelingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Initialize();

	//UFUNCTION(BlueprintNativeEvent, BlueprintCallable)


public:
	UFUNCTION(BlueprintCallable)
	void SetupLevelingData();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool ExceedLevelMaxExp() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsNextLevelValid() const;

public:
	int32 GetCurrentLevel() const { return CurrentLevel; }
	void SetCurrentLevel(int32 InCurrentLevel) { CurrentLevel = InCurrentLevel; }

	float GetCurrentExperience() const { return CurrentExperience; }
	void SetCurrentExperience(float InCurrentExperience) { CurrentExperience = InCurrentExperience; }

	float GetLevelMaxExperience() const { return LevelMaxExperience; }
	void SetLevelMaxExperience(float InLevelMaxExperience) { LevelMaxExperience = InLevelMaxExperience; }

	UDataTable* GetLevelingDataTable() const { return LevelingDataTable; }

	TMap<int32, float> GetLevelingData() const { return LevelingData; }
	void SetLevelingData(TMap<int32, float> InLevelingData) { LevelingData = InLevelingData; }
};
