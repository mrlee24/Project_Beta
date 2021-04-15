// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Inventory/RPGToolTipWidget.h"
#include "Widgets/Inventory/RPGToolTipItemInfoWidget.h"
#include "Widgets/Inventory/RPGToolTipStatsWidget.h"
#include "Kismet/KismetTextLibrary.h"
#include "Libraries/RPGInventoryFunctionLibrary.h"

void URPGToolTipWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InventoryComponent = URPGInventoryFunctionLibrary::GetInventoryComponent();
	EquipmentComponent = URPGInventoryFunctionLibrary::GetEquipmentComponent();


	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, ItemData.IsValid() ? "true" : "false");

	if (ItemData.IsValid())
	{
		(bCompareItems) ? Equipped_Border->SetVisibility(ESlateVisibility::Visible) : Equipped_Border->SetVisibility(ESlateVisibility::Hidden);

		PlayAnim();

		ItemInfo_ToolTipW->SetInventoryComponent(InventoryComponent);
		ItemInfo_ToolTipW->SetItemData(ItemData);

		Stats_ToolTipW->SetItemData(ItemData);
		Stats_ToolTipW->SetToolTip_Widget(this);
		Stats_ToolTipW->Init();

		ForceLayoutPrepass();
	}
}

void URPGToolTipWidget::ShowComparisonToolTip_Implementation()
{
	if (!Comparison_ToolTipW)
	{
		
	}
}

void URPGToolTipWidget::HideComparisonToolTip_Implementation()
{
	if (Comparison_ToolTipW)
	{
		Comparison_ToolTipW->RemoveFromParent();
		Comparison_ToolTipW = nullptr;
		OnHideComparison.Broadcast();
	}
}

void URPGToolTipWidget::RemoveAndClearComparisonToolTip_Implementation()
{
	if (Comparison_ToolTipW)
	{
		Comparison_ToolTipW->RemoveFromParent();
		Comparison_ToolTipW = nullptr;
		OnHideComparison.Broadcast();
	}
}

FText URPGToolTipWidget::UpdateDescription() const
{
	if (UKismetTextLibrary::TextIsEmpty(ItemData.Description.Description))
		Description_Text->SetVisibility(ESlateVisibility::Collapsed);

	return ItemData.Description.Description;
}

ESlateVisibility URPGToolTipWidget::UpdateUsedVisibility() const
{
	if (ItemData.Use.UseableType == EItemUseType::ReadableText && ItemData.Use.bIsAlreadyUsed)
		return ESlateVisibility::Visible;

	return ESlateVisibility::Collapsed;
}
