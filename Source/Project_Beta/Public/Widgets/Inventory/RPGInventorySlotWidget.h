// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RPGTypes.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "RPGInventorySlotWidget.generated.h"

class URPGInventoryComponent;
class URPGInventoryPanelWidget;
class URPGInventoryBaseWidget;
class URPGToolTipWidget;

UCLASS()
class PROJECT_BETA_API URPGInventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true"))
	URPGInventoryComponent* InventoryComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true"))
	FRPGItemData ItemData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true"))
	bool bGamepadControls;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true"))
	URPGToolTipWidget* ToolTip_Widget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true"))
	URPGInventoryBaseWidget* InventoryBase_Widget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true"))
	FLinearColor BorderUnHovered;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true"))
	FLinearColor BorderHovered;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	UBorder* Slot_Border;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	UButton* Slot_Button;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	UTextBlock* SlotQuantity_Text;

protected:
	virtual void NativeDestruct() override;
	virtual void NativeConstruct() override;

public:
	void Init(URPGInventoryComponent* InInventoryComponent, FRPGItemData InItemData, URPGInventoryBaseWidget* InInventoryBase_Widget)
	{
		InventoryComponent = InInventoryComponent;
		ItemData = InItemData;
		InventoryBase_Widget = InInventoryBase_Widget;
	}

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ToggleGamepadInputs();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void PlayAnim();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void StopAnim();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnRightClick();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ShowItemComparison();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void HideItemComparison();

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FText UpdateQuantity() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsUsingGamepad() const;

	UFUNCTION(BlueprintCallable)
	void UpdateButtonStyle(FRPGItemData InItemData);

	UFUNCTION(BlueprintCallable)
	void HighlightSlot();
};
