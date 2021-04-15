// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "RPGTypes.h"
#include "RPGTabBaseWidget.generated.h"

class URPGWindowSwitcherWidget;

UCLASS()
class PROJECT_BETA_API URPGTabBaseWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true"))
	URPGWindowSwitcherWidget* Window_Switcher;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	UImage* LButton_Image;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	UImage* RButton_Image;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true"))
	TArray<UButton*> ButtonArray;

public:
	void SetWindow_Switcher(URPGWindowSwitcherWidget* InWindow_Switcher) { Window_Switcher = InWindow_Switcher; }

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	UButton* GetButtonByWidgetType(const EWidgetType WidgetType) const;
};
