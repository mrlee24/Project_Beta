// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/RPGLevelingComponent.h"
#include "Libraries/RPGInventoryFunctionLibrary.h"

// Sets default values for this component's properties
URPGLevelingComponent::URPGLevelingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void URPGLevelingComponent::BeginPlay()
{
	Super::BeginPlay();

	Initialize();
}

void URPGLevelingComponent::Initialize_Implementation()
{
	SetupLevelingData();

	float MaxExperience = 0.f;

	if (URPGInventoryFunctionLibrary::LevelingMap_Map_Find(LevelingData, CurrentLevel, MaxExperience))
		LevelMaxExperience = MaxExperience; return;

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Current Level is not Valid!"));
}

void URPGLevelingComponent::SetupLevelingData()
{
	const TArray<FName> OutRowNames = LevelingDataTable->GetRowNames();

	for (auto& RowName : OutRowNames)
	{
		FRPGLevelingSystem LevelingRow = *LevelingDataTable->FindRow<FRPGLevelingSystem>(RowName, "");

		LevelingData.Add(LevelingRow.Level, LevelingRow.ExpNeeded);
	}
}

bool URPGLevelingComponent::ExceedLevelMaxExp() const
{
	return CurrentExperience >= LevelMaxExperience;
}

bool URPGLevelingComponent::IsNextLevelValid() const
{
	return LevelingData.Contains(CurrentLevel + 1);
}

