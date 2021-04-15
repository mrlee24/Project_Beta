// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"
#include "Components/UniformGridPanel.h"
#include "RPGTypes.h"
#include "RPGToolTipWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnShowComparison, URPGToolTipWidget*, InComparisonToolTip_Widget);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHideComparison);

class URPGEquipmentComponent;
class URPGInventoryComponent;
class URPGToolTipItemInfoWidget;
class URPGToolTipStatsWidget;

UCLASS()
class PROJECT_BETA_API URPGToolTipWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	URPGInventoryComponent* InventoryComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	URPGEquipmentComponent* EquipmentComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	UImage* Background_Image;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	UBorder* Equipped_Border;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	UTextBlock* Description_Text;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	UUniformGridPanel* Comp_UG;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	URPGToolTipItemInfoWidget* ItemInfo_ToolTipW;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	URPGToolTipStatsWidget* Stats_ToolTipW;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true"))
	URPGToolTipWidget* Comparison_ToolTipW;

	UPROPERTY(BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", ExposeOnSpawn = "true"))
	FRPGItemData ItemData;

	UPROPERTY(BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", ExposeOnSpawn = "true"))
	bool bCompareItems;

	UPROPERTY(BlueprintAssignable)
	FOnShowComparison OnShowComparison;

	UPROPERTY(BlueprintAssignable)
	FOnHideComparison OnHideComparison;

protected:
	virtual void NativeConstruct() override;

public:
	void Init(FRPGItemData InItemData, bool InbCompareItems)
	{
		ItemData = InItemData;
		bCompareItems = InbCompareItems;
	}

	URPGToolTipStatsWidget* GetStats_ToolTipW() const { return Stats_ToolTipW; }
	void SetStats_ToolTipW(URPGToolTipStatsWidget* InStats_ToolTipW) { Stats_ToolTipW = InStats_ToolTipW; }

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void PlayAnim();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ShowComparisonToolTip();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void HideComparisonToolTip();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void RemoveAndClearComparisonToolTip();

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FText UpdateDescription() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	ESlateVisibility UpdateUsedVisibility() const;
};
