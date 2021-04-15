// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Inventory/RPGDropBarWidget.h"
#include "Libraries/RPGInventoryFunctionLibrary.h"

void URPGDropBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InventoryComponent = URPGInventoryFunctionLibrary::GetInventoryComponent();
}
