// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Inventory/RPGInventoryBaseWidget.h"
#include "Widgets/Inventory/RPGInventoryPanelWidget.h"
#include "Widgets/Inventory/RPGInventorySlotWidget.h"
#include "Components/RPGInventoryComponent.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Libraries/RPGInventoryFunctionLibrary.h"

void URPGInventoryBaseWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayAnim();

	InventoryComponent = URPGInventoryFunctionLibrary::GetInventoryComponent();
	CreateInventories();
	HideAllAndShowActiveBorder(EItemType::Weapon);
	ToggleGamepadInputs();
	BindSorting();
}

void URPGInventoryBaseWidget::CreateInventories_Implementation()
{
	TArray<UUserWidget*> WidgetPanels;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), WidgetPanels, URPGInventoryPanelWidget::StaticClass(), false);

	for (int32 Index = 0; Index < WidgetPanels.Num(); Index++)
	{
		ColumnPosition = 0;
		RowPosition = 0;

		URPGInventoryPanelWidget* Panel = Cast<URPGInventoryPanelWidget>(WidgetPanels[Index]);
		Panel->Init(InventoryComponent, this);
		const EItemType Type = Panel->GetType();

		if (Type != EItemType::None || Type != EItemType::Currency || Type != EItemType::Max)
		{
			FRPGInventoryPanelData InventoryPanel = (*InventoryComponent->GetInventoryData().Find(Type));
			Panel->BuildInventory(InventoryPanel.Size, InventoryComponent->SelectCorrectInventory(Type), ColumnPosition, RowPosition, RowLength);
		}
	}
}

EItemType URPGInventoryBaseWidget::GetActivePanel() const
{
	URPGInventoryPanelWidget* ActiveWidget = Cast<URPGInventoryPanelWidget>(Panels_Switcher->GetActiveWidget());

	return ActiveWidget->GetType();
}

void URPGInventoryBaseWidget::SetFocusToSlot(const int32 SlotIndex)
{
	if (InventoryComponent->GetFocusedWidget() == EWidgetType::Inventory)
	{
		if (GetUniformGridByItemType(GetActivePanel())->GetChildAt(SlotIndex))
		{
			LastFocusedSlot = SlotIndex;
			GetUniformGridByItemType(GetActivePanel())->GetChildAt(SlotIndex)->SetUserFocus(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		}
	}
}

UUniformGridPanel* URPGInventoryBaseWidget::GetUniformGridByItemType(const EItemType Index)
{
	UUniformGridPanel* Result;

	switch (Index)
	{
	case EItemType::Weapon:
		Result = Weapon_PanelWidget->GetUniformGrid();
		break;

	case EItemType::Armor:
		Result = Armor_PanelWidget->GetUniformGrid();
		break;

	case EItemType::Consumable:
		Result = Consumable_PanelWidget->GetUniformGrid();
		break;

	case EItemType::CraftingIngredient:
		Result = CraftingIngre_PanelWidget->GetUniformGrid();
		break;

	case EItemType::QuestItem:
		Result = QuestItem_PanelWidget->GetUniformGrid();
		break;

	default: 
		Result = nullptr;
		break;
	}

	return Result;
}

void URPGInventoryBaseWidget::SwitchPanels(const bool bToRight)
{
	if (bToRight)
	{
		switch (GetActivePanel())
		{
		case EItemType::Weapon:
			SwitchPanel2();
			break;

		case EItemType::Armor:
			SwitchPanel3();
			break;

		case EItemType::Consumable:
			SwitchPanel4();
			break;

		case EItemType::CraftingIngredient:
			SwitchPanel5();
			break;

		case EItemType::QuestItem:
			SwitchPanel1();
		}
	}
	else
	{
		switch (GetActivePanel())
		{
		case EItemType::Weapon:
			SwitchPanel5();
			break;

		case EItemType::Armor:
			SwitchPanel1();
			break;

		case EItemType::Consumable:
			SwitchPanel2();
			break;

		case EItemType::CraftingIngredient:
			SwitchPanel3();
			break;

		case EItemType::QuestItem:
			SwitchPanel4();
		}
	}
}

bool URPGInventoryBaseWidget::IsUsingGamepad() const
{
	return bGamepadControls;
}

void URPGInventoryBaseWidget::HighlightSlot(const int32 SlotIndex)
{
	 UWidget* ChildIndex = GetUniformGridByItemType(GetActivePanel())->GetChildAt(SlotIndex);

	 if (ChildIndex)
	 {
		 URPGInventorySlotWidget* InventorySlotIndex = Cast<URPGInventorySlotWidget>(ChildIndex);
		 InventorySlotIndex->HighlightSlot();
	 }
}

void URPGInventoryBaseWidget::HideAllAndShowActiveBorder(const EItemType Panel)
{
	for (int32 Index = (int32)EItemType::None; Index < (int32)EItemType::Max; Index++)
	{
		const EItemType Type = static_cast<EItemType>(Index);
		
		if (Type != EItemType::None && Type != EItemType::Currency && Type != EItemType::Max)
			GetPanelButtonBorder(Type)->SetBrushColor(FLinearColor::Transparent);
	}

	GetPanelButtonBorder(Panel)->SetBrushColor(FLinearColor::White);
}

UBorder* URPGInventoryBaseWidget::GetPanelButtonBorder(const EItemType Panel) const
{
	UBorder* Result;

	switch (Panel)
	{
	case EItemType::Weapon:
		Result = WeaponButton_Border;
		break;

	case EItemType::Armor:
		Result = ArmorButton_Border;
		break;

	case EItemType::Consumable:
		Result = ConsumableButton_Border;
		break;

	case EItemType::CraftingIngredient:
		Result = CraftingIngreButton_Border;
		break;

	case EItemType::QuestItem:
		Result = QuestItemButton_Border;
		break;

	default:
		Result = nullptr;
		break;
	}

	return Result;
}

FText URPGInventoryBaseWidget::UpdatePanelTitle() const
{
	FText Result;

	switch (GetActivePanel())
	{
	case EItemType::Weapon:
		Result = Weapon_PanelWidget->GetTitle();
		break;

	case EItemType::Armor:
		Result = Armor_PanelWidget->GetTitle();
		break;

	case EItemType::Consumable:
		Result = Consumable_PanelWidget->GetTitle();
		break;

	case EItemType::CraftingIngredient:
		Result = CraftingIngre_PanelWidget->GetTitle();
		break;

	case EItemType::QuestItem:
		Result = QuestItem_PanelWidget->GetTitle();
		break;

	default:
		Result = FText();
		break;
	}

	return Result;
}
