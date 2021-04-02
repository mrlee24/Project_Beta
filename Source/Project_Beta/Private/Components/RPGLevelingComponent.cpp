// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/RPGLevelingComponent.h"
#include "Widgets/Leveling/RPGLevelExpNotifyWidget.h"
#include "Kismet/KismetMathLibrary.h"
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

void URPGLevelingComponent::AddLevelExp_Implementation(const float Experience /*= 0.f*/)
{
	CurrentExperience += Experience;
	OnGainedExperience.Broadcast();

	UUserWidget* WidgetRef = CreateWidget<UUserWidget>(GetWorld(), LevelExpNotify_Class);

	if (WidgetRef)
	{
		URPGLevelExpNotifyWidget* LevelExpNotify_Widget = Cast<URPGLevelExpNotifyWidget>(WidgetRef);
		LevelExpNotify_Widget->Init(0, Experience);
		LevelExpNotify_Widget->AddToViewport();

		if (ExceedLevelMaxExp())
			LevelUp();
	}
}

void URPGLevelingComponent::LevelUp_Implementation()
{
	if (ExceedLevelMaxExp())
	{
		if (!IsNextLevelValid())
		{
			CurrentExperience = UKismetMathLibrary::Clamp(CurrentExperience, 0.f, LevelMaxExperience);
			OnGainedExperience.Broadcast();
			return;
		}

		CurrentExperience -= LevelMaxExperience;
		CurrentLevel += 1;

		URPGInventoryFunctionLibrary::LevelingMap_Map_Find(LevelingData, CurrentLevel, LevelMaxExperience);
		OnLevelChanged.Broadcast();

		UUserWidget* WidgetRef = CreateWidget<UUserWidget>(GetWorld(), LevelExpNotify_Class);

		if (WidgetRef)
		{
			URPGLevelExpNotifyWidget* LevelExpNotify_Widget = Cast<URPGLevelExpNotifyWidget>(WidgetRef);
			LevelExpNotify_Widget->Init(GetCurrentLevel());
			LevelExpNotify_Widget->AddToViewport();

			if (ExceedLevelMaxExp())
				LevelUp();
		}
	}
}

void URPGLevelingComponent::SetLevel_Implementation(const int32 Level)
{
	float MaxExperience = 0.f;
	if (URPGInventoryFunctionLibrary::LevelingMap_Map_Find(LevelingData, Level, MaxExperience))
	{
		CurrentLevel = Level;
		LevelMaxExperience = MaxExperience;
		OnLevelChanged.Broadcast();
	}
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

