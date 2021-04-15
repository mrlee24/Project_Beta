// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Common/RPGWindowSwitcherWidget.h"
#include "Widgets/Common/RPGTabBaseWidget.h"
#include "Widgets/Common/RPGMainTabWidget.h"
#include "Widgets/Common/RPGVendorTabWidget.h"
#include "Widgets/Common/RPGStorageTabWidget.h"
#include "Widgets/Common/RPGLoadGameTabWidget.h"

void URPGWindowSwitcherWidget::EventOnSwitchWidgetTab_Implementation(const EWidgetType TabToActivate)
{
	OnSwitchWidgetTab.Broadcast(TabToActivate);
}

URPGTabBaseWidget* URPGWindowSwitcherWidget::GetWidgetSwitcherPanel(const EWidgetType Index) const
{
	URPGTabBaseWidget* Result = nullptr;

	switch (Index)
	{
	case EWidgetType::Inventory:
		Result = Cast<URPGTabBaseWidget>(MainTab_Widget);
		break;

	case EWidgetType::Crafting:
		Result = Cast<URPGTabBaseWidget>(MainTab_Widget);
		break;

	case EWidgetType::Equipment:
		Result = Cast<URPGTabBaseWidget>(MainTab_Widget);
		break;
		
	case EWidgetType::Status:
		Result = Cast<URPGTabBaseWidget>(MainTab_Widget);
		break;

	case EWidgetType::Map:
		Result = Cast<URPGTabBaseWidget>(MainTab_Widget);
		break;

	case EWidgetType::Quest:
		Result = Cast<URPGTabBaseWidget>(MainTab_Widget);
		break;

	case EWidgetType::Vendor:
		Result = Cast<URPGTabBaseWidget>(VendorTab_Widget);
		break;

	case EWidgetType::Storage:
		Result = Cast<URPGTabBaseWidget>(StorageTab_Widget);
		break;

	case EWidgetType::LoadGame:
		Result = Cast<URPGTabBaseWidget>(LoadGameTab_Widget);
	}

	return Result;
}

UButton* URPGWindowSwitcherWidget::GetButtonByWidgetType(const EWidgetType CurrentWidget)
{
	UButton* Result = nullptr;

	switch (CurrentWidget)
	{
	case EWidgetType::Inventory:
		Result = MainTab_Widget->GetButtonByWidgetType(CurrentWidget);
		break;

	case EWidgetType::Equipment:
		Result = MainTab_Widget->GetButtonByWidgetType(CurrentWidget);
		break;

	case EWidgetType::Crafting:
		Result = MainTab_Widget->GetButtonByWidgetType(CurrentWidget);
		break;

	case EWidgetType::Map:
		Result = MainTab_Widget->GetButtonByWidgetType(CurrentWidget);
		break;

	case EWidgetType::Status:
		Result = MainTab_Widget->GetButtonByWidgetType(CurrentWidget);
		break;

	case EWidgetType::Quest:
		Result = MainTab_Widget->GetButtonByWidgetType(CurrentWidget);
		break;

	case EWidgetType::Storage:
		Result = StorageTab_Widget->GetButtonByWidgetType(CurrentWidget);
		break;

	case EWidgetType::Vendor:
		Result = VendorTab_Widget->GetButtonByWidgetType(CurrentWidget);
		break;
	}

	return Result;
}
