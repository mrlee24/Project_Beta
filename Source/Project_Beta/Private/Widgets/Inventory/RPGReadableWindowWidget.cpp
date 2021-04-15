// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Inventory/RPGReadableWindowWidget.h"
#include "Widgets/Inventory/RPGInventoryOverallWidget.h"
#include "Components/RPGInventoryComponent.h"

void URPGReadableWindowWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InventoryComponent->SetFocusedWidget(EWidgetType::ReadableText);
	InventoryComponent->GetInventoryOverall_Widget()->SetIsEnabled(false);

	ExitKeybindings = InventoryComponent->GetExitKeybindings();

	ToggleGamepadInputs();
}
