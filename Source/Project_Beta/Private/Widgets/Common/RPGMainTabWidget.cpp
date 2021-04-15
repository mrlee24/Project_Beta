// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Common/RPGMainTabWidget.h"

void URPGMainTabWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ButtonArray.Add(Crafting_Button);
	ButtonArray.Add(Equipment_Button);
	ButtonArray.Add(Inventory_Button);
	ButtonArray.Add(Status_Button);
	ButtonArray.Add(Map_Button);
	ButtonArray.Add(Quest_Button);
}

UButton* URPGMainTabWidget::GetButtonByWidgetType(const EWidgetType WidgetType) const
{
	UButton* Result = nullptr;
	for (int32 Index = 0; Index < ButtonArray.Num(); Index++)
	{
		switch (WidgetType)
		{
		case EWidgetType::Inventory:
			Result = Inventory_Button;
			break;

		case EWidgetType::Equipment:
			Result = Equipment_Button;
			break;

		case EWidgetType::Crafting:
			Result = Crafting_Button;
			break;

		case EWidgetType::Status:
			Result = Status_Button;
			break;

		case EWidgetType::Map:
			Result = Map_Button;
			break;

		case EWidgetType::Quest:
			Result = Quest_Button;
			break;
		}
	}

	return Result;
}
