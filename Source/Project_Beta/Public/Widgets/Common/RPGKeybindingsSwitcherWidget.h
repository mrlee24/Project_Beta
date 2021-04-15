// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/WidgetSwitcher.h"
#include "RPGTypes.h"
#include "RPGKeybindingsSwitcherWidget.generated.h"

class URPGInventoryComponent;

UCLASS()
class PROJECT_BETA_API URPGKeybindingsSwitcherWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	URPGInventoryComponent* InventoryComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true", BindWidget))
	UHorizontalBox* AbilitiesGamepad_HBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true", BindWidget))
	UHorizontalBox* AbilitiesKeyboard_HBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true", BindWidget))
	UHorizontalBox* CraftingGamepad_HBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true", BindWidget))
	UHorizontalBox* CraftingKeyboard_HBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true", BindWidget))
	UHorizontalBox* InventoryGamepad_HBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true", BindWidget))
	UHorizontalBox* InventoryKeyboard_HBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true", BindWidget))
	UHorizontalBox* LoadGameGamepad_HBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true", BindWidget))
	UHorizontalBox* LoadGameKeyboard_HBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true", BindWidget))
	UHorizontalBox* StorageGamepad_HBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true", BindWidget))
	UHorizontalBox* StorageKeyboard_HBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true", BindWidget))
	UHorizontalBox* VendorGamepad_HBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true", BindWidget))
	UHorizontalBox* VendorKeyboard_HBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true", BindWidget))
	UWidgetSwitcher* KeyBindings_Switcher;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true", BindWidget))
	EWidgetType WidgetType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true", BindWidget))
	bool bGamepadControls = false;

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ToggleGamepadInputs();
};
