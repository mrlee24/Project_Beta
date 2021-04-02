// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/WidgetSwitcher.h"
#include "RPGLevelExpNotifyWidget.generated.h"

UCLASS()
class PROJECT_BETA_API URPGLevelExpNotifyWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 Level = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float Experience = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	UCanvasPanel* Experience_Panel;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	UCanvasPanel* Level_Panel;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	UWidgetSwitcher* Switcher_WS;

protected:
	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void PlayLevelAnimtion();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void PlayExperienceAnimation();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FText GetLevelText() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FText GetExperienceText() const;

public:
	void Init(int32 InLevel = 0, float InExperience = 0.f)
	{
		Level = InLevel;
		Experience = InExperience;
	}

	int32 GetLevel() const { return Level; }
	void SetLevel(int32 InLevel) { Level = InLevel; }

	float GetExperience() const { return Experience; }
	void SetExperience(float InExperience) { Experience = InExperience; }

	UCanvasPanel* GetExperience_Panel() const { return Experience_Panel; }

	UCanvasPanel* GetLevel_Panel() const { return Level_Panel; }

	UWidgetSwitcher* GetSwitcher_WS() const { return Switcher_WS; }
};
