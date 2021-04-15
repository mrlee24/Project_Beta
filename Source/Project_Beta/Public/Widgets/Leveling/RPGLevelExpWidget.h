// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RPGLevelExpWidget.generated.h"

class URPGLevelingComponent;

UCLASS()
class PROJECT_BETA_API URPGLevelExpWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	URPGLevelingComponent* LevelingComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	int32 PlayerLevel = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	float PlayerCurrentExp = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	float PlayerLimitExp = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	float PercentProgressValue = 0.f;

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetupEventDispatchers();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void RefreshProgressValue();
};
