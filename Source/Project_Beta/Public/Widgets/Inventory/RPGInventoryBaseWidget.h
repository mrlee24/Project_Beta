// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/WidgetSwitcher.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/UniformGridPanel.h"
#include "RPGTypes.h"
#include "RPGInventoryBaseWidget.generated.h"

class URPGInventoryComponent;
class URPGInventoryPanelWidget;
class URPGSortWindowWidget;
class URPGRotateItemBoxWidget;

UCLASS()
class PROJECT_BETA_API URPGInventoryBaseWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	URPGInventoryComponent* InventoryComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	UWidgetSwitcher* Panels_Switcher;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	URPGInventoryPanelWidget* Weapon_PanelWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	URPGInventoryPanelWidget* Armor_PanelWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	URPGInventoryPanelWidget* Consumable_PanelWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	URPGInventoryPanelWidget* CraftingIngre_PanelWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	URPGInventoryPanelWidget* QuestItem_PanelWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	URPGRotateItemBoxWidget* RotateItemBox_Widget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	UBorder* Background_Border;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	UImage* Background_Image;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	UBorder* WeaponButton_Border;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	UBorder* ArmorButton_Border;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	UBorder* ConsumableButton_Border;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	UBorder* CraftingIngreButton_Border;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	UBorder* QuestItemButton_Border;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	UButton* Weapon_Button;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	UButton* Armor_Button;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	UButton* Consumable_Button;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	UButton* CraftingIngre_Button;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	UButton* QuestItem_Button;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	URPGSortWindowWidget* SortWindow_Widget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true"))
	int32 ColumnPosition = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true"))
	int32 RowPosition = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true"))
	int32 RowLength = 5;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true"))
	int32 LastFocusedSlot = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true"))
	bool bGamepadControls;

protected:
	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void PlayAnim();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ToggleGamepadInputs();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BindSorting();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SwitchPanel1();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SwitchPanel2();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SwitchPanel3();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SwitchPanel4();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SwitchPanel5();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetCaptureImage(const FRPGItemData ItemData);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void CreateInventories();

public:
	UFUNCTION(BlueprintCallable)
	EItemType GetActivePanel() const;

	UFUNCTION(BlueprintCallable)
	void SetFocusToSlot(const int32 SlotIndex);

	UFUNCTION(BlueprintCallable)
	UUniformGridPanel* GetUniformGridByItemType(const EItemType Index);

	UFUNCTION(BlueprintCallable)
	void SwitchPanels(const bool bToRight);

	UFUNCTION(BlueprintCallable)
	bool IsUsingGamepad() const;

	UFUNCTION(BlueprintCallable)
	void HighlightSlot(const int32 SlotIndex);

	UFUNCTION(BlueprintCallable)
	void HideAllAndShowActiveBorder(const EItemType Panel);

	UFUNCTION(BlueprintCallable)
	UBorder* GetPanelButtonBorder(const EItemType Panel) const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FText UpdatePanelTitle() const;
};
