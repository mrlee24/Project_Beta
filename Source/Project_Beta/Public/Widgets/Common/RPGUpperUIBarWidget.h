// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "RPGTypes.h"
#include "RPGUpperUIBarWidget.generated.h"

class URPGLevelExpWidget;
class URPGWindowSwitcherWidget;

UCLASS()
class PROJECT_BETA_API URPGUpperUIBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	UButton* Close_Button;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	UTextBlock* X_Text;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	URPGLevelExpWidget* LevelExp_Widget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	URPGWindowSwitcherWidget* WindowSwitcher_Widget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true"))
	EWidgetType WidgetType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true"))
	FSlateColor ButtonXHovered;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true"))
	FSlateColor ButtonXUnHovered;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true"))
	bool ShowLvlExperience = true;
};
