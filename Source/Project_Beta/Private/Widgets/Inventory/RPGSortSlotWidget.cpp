// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Inventory/RPGSortSlotWidget.h"
#include "Components/RPGInventoryComponent.h"

void URPGSortSlotWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	Title_Text->SetText(Title);
}

void URPGSortSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ToggleGamepadInputs();
}

bool URPGSortSlotWidget::IsUsingGamepad() const
{
	return bGamepadControls;
}

FText URPGSortSlotWidget::UpdateTitle() const
{
	return Title;
}
