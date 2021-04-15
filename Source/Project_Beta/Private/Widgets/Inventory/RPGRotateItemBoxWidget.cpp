// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Inventory/RPGRotateItemBoxWidget.h"
#include "Libraries/RPGInventoryFunctionLibrary.h"

void URPGRotateItemBoxWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InventoryComponent = URPGInventoryFunctionLibrary::GetInventoryComponent();
}
