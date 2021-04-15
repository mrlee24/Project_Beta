// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RPGTypes.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/Overlay.h"
#include "RPGEquipmentSlotWidget.generated.h"

class URPGInventoryComponent;
class URPGEquipmentComponent;
class URPGEquipmentWidget;
class URPGToolTipWidget;

UCLASS()
class PROJECT_BETA_API URPGEquipmentSlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	URPGInventoryComponent* InventoryComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	URPGEquipmentComponent* EquipmentComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defautls", meta = (AllowPrivateAccess = "true"))
	FRPGItemData ItemData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defautls", meta = (AllowPrivateAccess = "true"))
	URPGEquipmentWidget* Equipment_Widget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defautls", meta = (AllowPrivateAccess = "true"))
	URPGToolTipWidget* ToolTip_Widget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defautls", meta = (AllowPrivateAccess = "true"))
	bool bGamepadControls = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defautls", meta = (AllowPrivateAccess = "true"))
	FLinearColor BorderHovered;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defautls", meta = (AllowPrivateAccess = "true"))
	FLinearColor BorderUnHovered;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defautls", meta = (AllowPrivateAccess = "true"))
	FText LabelCharText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defautls", meta = (AllowPrivateAccess = "true"))
	FRPGItemSlot ItemSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defautls", meta = (AllowPrivateAccess = "true"))
	FSlateBrush EmptySlotStyle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defautls", meta = (AllowPrivateAccess = "true", BindWidget))
	UImage* Border_Image;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defautls", meta = (AllowPrivateAccess = "true", BindWidget))
	UButton* Equip_Button;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defautls", meta = (AllowPrivateAccess = "true", BindWidget))
	UImage* Equip_Image;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defautls", meta = (AllowPrivateAccess = "true", BindWidget))
	UImage* Item_Image;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defautls", meta = (AllowPrivateAccess = "true", BindWidget))
	UTextBlock* Label_Text;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defautls", meta = (AllowPrivateAccess = "true", BindWidget))
	UOverlay* Overlay_Label;

public:
	FRPGItemSlot GetItemSlot() const { return ItemSlot; }
	UImage* GetItem_Image() const { return Item_Image; }

	void SetItemSlot(FRPGItemSlot InItemSlot) { ItemSlot = InItemSlot; }
	void SetEquipment_Widget(URPGEquipmentWidget* InEquipment_Widget) { Equipment_Widget = InEquipment_Widget; }
	void SetItemData(FRPGItemData InItemData) { ItemData = InItemData; }

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ToggleGamepadInputs();
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void EmptySlot();

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FText UpdateQuantity() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	ESlateVisibility UpdateLabelVisibility() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsUsingGamepad() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FText UpdateLabelCharacter() const;
};
