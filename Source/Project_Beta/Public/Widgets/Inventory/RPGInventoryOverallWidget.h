// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "RPGInventoryOverallWidget.generated.h"

class URPGInventoryComponent;
class URPGInventoryBaseWidget;
//class URPGDropBarWidget;
class URPGKeybindingsSwitcherWidget;
class URPGUpperUIBarWidget;

UCLASS()
class PROJECT_BETA_API URPGInventoryOverallWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true"))
	URPGInventoryComponent* InventoryComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	UImage* Background_Image;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	//URPGDropBarWidget* DropBar_Widget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	URPGInventoryBaseWidget* InventoryBase_Widget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	URPGKeybindingsSwitcherWidget* KeybindingsSwitcher_Widget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	URPGUpperUIBarWidget* UpperUIBar_Widget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true"))
	TSet<FKey> InventoryKeybindings;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true"))
	TSet<FKey> ExitKeybindings;
};
