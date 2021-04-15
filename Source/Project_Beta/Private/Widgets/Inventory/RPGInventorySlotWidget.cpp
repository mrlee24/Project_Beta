// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Inventory/RPGInventorySlotWidget.h"
#include "Widgets/Inventory/RPGToolTipWidget.h"
#include "Widgets/Inventory/RPGInventoryBaseWidget.h"
#include "Components/RPGInventoryComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetTextLibrary.h"
#include "Engine/World.h"

void URPGInventorySlotWidget::NativeDestruct()
{
	Super::NativeDestruct();

	if (ToolTip_Widget)
		ToolTip_Widget->RemoveFromParent();
}

void URPGInventorySlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ToggleGamepadInputs();
}

void URPGInventorySlotWidget::OnRightClick_Implementation()
{
	if (ItemData.IsValid())
	{
		InventoryComponent->AssignCurrentWidgetInput(EInputMethod::RightClick, EWidgetType::Inventory);
		//InventoryComponent->HandleSlotInput();
	}

	InventoryBase_Widget->SetFocusToSlot(ItemData.Index);
}

void URPGInventorySlotWidget::ShowItemComparison_Implementation()
{
	if (ItemData.IsValid())
	{
		if (ItemData.Type != EItemType::Consumable)
		{
			if (ToolTip_Widget)
				ToolTip_Widget->ShowComparisonToolTip();
		}
	}
}

void URPGInventorySlotWidget::HideItemComparison_Implementation()
{
	if (ToolTip_Widget)
		ToolTip_Widget->HideComparisonToolTip();
}

FText URPGInventorySlotWidget::UpdateQuantity() const
{
	return (ItemData.Stacks.bStackable && ItemData.Stacks.Quantity > 1) ? UKismetTextLibrary::Conv_IntToText(ItemData.Stacks.Quantity) : FText();
}

bool URPGInventorySlotWidget::IsUsingGamepad() const
{
	return bGamepadControls;
}

void URPGInventorySlotWidget::UpdateButtonStyle(FRPGItemData InItemData)
{
	if (InItemData.IsValid())
	{
		if (InItemData.Use.bIsAlreadyUsed)
		{
			FLinearColor MakeTint = { 0.223958, 0.220658, 0.210761, 1.f };
			FSlateColor MakeSlateColor = { MakeTint };
			InItemData.Thumbnail.TintColor = MakeSlateColor;

			FButtonStyle ButtonStyle;
			ButtonStyle.Normal = InItemData.Thumbnail;
			ButtonStyle.Hovered = InItemData.Thumbnail;
			ButtonStyle.Pressed = InItemData.Thumbnail;
			Slot_Button->SetStyle(ButtonStyle);
			return;
		}

		FButtonStyle ButtonStyle;
		ButtonStyle.Normal = InItemData.Thumbnail;
		ButtonStyle.Hovered = InItemData.Thumbnail;
		ButtonStyle.Pressed = InItemData.Thumbnail;
		Slot_Button->SetStyle(ButtonStyle);
	}
}

void URPGInventorySlotWidget::HighlightSlot()
{
	if (!HasUserFocus(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
		PlayAnim();
}


