// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Inventory/RPGSortWindowWidget.h"
#include "Widgets/Inventory/RPGSortSlotWidget.h"
#include "Libraries/RPGInventoryFunctionLibrary.h"

void URPGSortWindowWidget::NativeConstruct()
{
	InventoryComponent = URPGInventoryFunctionLibrary::GetInventoryComponent();
	ToggleGamepadInputs();

	for (auto& Button : GetAllButtons())
	{
		Button->SetSortWindow_Widget(this);
		Button->SetInventoryComponent(InventoryComponent);
	}
}

void URPGSortWindowWidget::EndSorting_Implementation()
{
	OnEndSorting.Broadcast();
}

TArray<URPGSortSlotWidget*> URPGSortWindowWidget::GetAllButtons() const
{
	TArray<URPGSortSlotWidget*> ButtonArray;
	ButtonArray.Add(Type_SortSlotW);
	ButtonArray.Add(Rarity_SortSlotW);
	ButtonArray.Add(Value_SortSlotW);
	ButtonArray.Add(Weight_SortSlotW);

	return ButtonArray;
}

bool URPGSortWindowWidget::IsUsingGamepad() const
{
	return bGamepadControls;
}
