// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Equipment/RPGEquipmentSlotWidget.h"
#include "Kismet/KismetTextLibrary.h"

FText URPGEquipmentSlotWidget::UpdateQuantity() const
{
	return (ItemData.Stacks.bStackable && ItemData.Stacks.Quantity > 1) ? UKismetTextLibrary::Conv_IntToText(ItemData.Stacks.Quantity) : FText();
}

ESlateVisibility URPGEquipmentSlotWidget::UpdateLabelVisibility() const
{
	return UKismetTextLibrary::TextIsEmpty(LabelCharText) ? ESlateVisibility::Collapsed : ESlateVisibility::HitTestInvisible;
}

bool URPGEquipmentSlotWidget::IsUsingGamepad() const
{
	return bGamepadControls;
}

FText URPGEquipmentSlotWidget::UpdateLabelCharacter() const
{
	return LabelCharText;
}
