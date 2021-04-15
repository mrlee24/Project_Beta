// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/VerticalBox.h"
#include "Components/TextBlock.h"
#include "RPGTypes.h"
#include "RPGToolTipStatsWidget.generated.h"

class URPGToolTipStatRowWidget;
class URPGToolTipWidget;

UCLASS()
class PROJECT_BETA_API URPGToolTipStatsWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	URPGToolTipStatRowWidget* Armor_StatRowW;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	URPGToolTipStatRowWidget* Damage_StatRowW;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	URPGToolTipStatRowWidget* AttackSpeed_StatRowW;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	URPGToolTipStatRowWidget* MaxHealth_StatRowW;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	URPGToolTipStatRowWidget* MaxStamina_StatRowW;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	URPGToolTipStatRowWidget* MaxMana_StatRowW;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	UHorizontalBox* StackedValue_HBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	UHorizontalBox* StackedWeight_HBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	UHorizontalBox* Durability_HBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	UHorizontalBox* Level_HBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	UVerticalBox* Stats_VBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	UTextBlock* Durability_Text;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	UTextBlock* DurabilityPerc_Text;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	UTextBlock* DurabilityValue_Text;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	UTextBlock* ReqLevel_Text;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	UTextBlock* ReqLevelValue_Text;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	UTextBlock* StackedValue_Text;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	UTextBlock* StackedWeight_Text;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true"))
	FRPGItemData ItemData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true"))
	URPGToolTipWidget* ToolTip_Widget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Customizables", meta = (AllowPrivateAccess = "true"))
	FSlateColor Durability_Color;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Customizables", meta = (AllowPrivateAccess = "true"))
	FSlateColor LevelRequired_Color;

public:
	FRPGItemData GetItemData() const { return ItemData; }
	void SetItemData(FRPGItemData InItemData) { ItemData = InItemData; }

	URPGToolTipWidget* GetToolTip_Widget() const { return ToolTip_Widget; }
	void SetToolTip_Widget(URPGToolTipWidget* InToolTip_Widget) { ToolTip_Widget = InToolTip_Widget; }

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void Init();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void HideComparedValues();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void UpdateComparedValues(const URPGToolTipWidget* ComparisonToolTip);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void CreateStatsBox();

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FText UpdateWeight() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FText UpdateValue() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FText UpdateStackedWeight() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FText UpdateStackedValue() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	URPGToolTipStatRowWidget* GetStatWidget(const EStatCategory Stat) const;

	UFUNCTION(BlueprintCallable)
	void SetDurability();

	UFUNCTION(BlueprintCallable)
	void SetRequiredLevel();
};
