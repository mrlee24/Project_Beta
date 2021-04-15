// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Inventory/RPGInventoryPanelWidget.h"
#include "Widgets/Inventory/RPGInventorySlotWidget.h"
#include "Widgets/Inventory/RPGInventoryBaseWidget.h"
#include "Components/RPGInventoryComponent.h"

void URPGInventoryPanelWidget::Init(URPGInventoryComponent* InInventoryComponent, URPGInventoryBaseWidget* InInventoryBase_Widget)
{
	InventoryComponent = InInventoryComponent;
	InventoryBase_Widget = InInventoryBase_Widget;
}

void URPGInventoryPanelWidget::BuildInventory(const int32 InventorySize, TArray<FRPGItemData>* InventoryData, int32 InColumnPosition, int32 InRowPosition, int32 InRowLength)
{
	(*InventoryData).SetNum(InventorySize);

	for (int32 Index = 0; Index < InventorySize; Index++)
	{
		(*InventoryData)[Index].Index = Index;
		(*InventoryData)[Index].bEquipped = false;

		UUserWidget* WidgetRef = CreateWidget<UUserWidget>(GetWorld(), InventorySlot_Class);

		if (WidgetRef)
		{
			InventorySlot_Widget = Cast<URPGInventorySlotWidget>(WidgetRef);
			InventorySlot_Widget->Init(InventoryComponent, (*InventoryData)[Index], InventoryBase_Widget);

			UUniformGridSlot* UniformGridSlot = UniformGrid->AddChildToUniformGrid(InventorySlot_Widget, 0, 0);
			UniformGridSlot->SetHorizontalAlignment(HAlign_Fill);
			UniformGridSlot->SetVerticalAlignment(VAlign_Fill);
			UniformGridSlot->SetColumn(InColumnPosition);
			UniformGridSlot->SetRow(InRowPosition);

			InventorySlot_Widget->UpdateButtonStyle((*InventoryData)[Index]);

			InColumnPosition++;

			if (InColumnPosition >= InRowLength)
			{
				InColumnPosition = 0;
				InRowPosition++;
			}
		}
	}
}
