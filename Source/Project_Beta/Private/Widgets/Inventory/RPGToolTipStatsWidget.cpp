// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Inventory/RPGToolTipStatsWidget.h"
#include "Widgets/Inventory/RPGToolTipStatRowWidget.h"
#include "Widgets/Inventory/RPGToolTipWidget.h"
#include "Components/RPGLevelingComponent.h"
#include "Kismet/KismetTextLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Libraries/RPGInventoryFunctionLibrary.h"

void URPGToolTipStatsWidget::HideComparedValues_Implementation()
{
	for (int32 Index = (int32)EStatCategory::None; Index < (int32)EStatCategory::Max; Index++)
	{
		const EStatCategory Type = static_cast<EStatCategory>(Index);
		URPGToolTipStatRowWidget* SelectedWidget = GetStatWidget(Type);

		if (SelectedWidget)
			SelectedWidget->GetComparisonValue_Text()->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void URPGToolTipStatsWidget::UpdateComparedValues_Implementation(const URPGToolTipWidget* ComparisonToolTip)
{
	for (int32 Index = (int32)EStatCategory::None; Index < (int32)EStatCategory::Max; Index++)
	{
		const EStatCategory Type = static_cast<EStatCategory>(Index);
		URPGToolTipStatRowWidget* SelectedWidget = GetStatWidget(Type);

		if (SelectedWidget)
		{
			SelectedWidget->SetComparisonValue(ComparisonToolTip->GetStats_ToolTipW()->GetStatWidget(Type)->GetStatRow().Value);
			SelectedWidget->GetComparisonValue_Text()->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

void URPGToolTipStatsWidget::CreateStatsBox_Implementation()
{
	for (auto& ItemStat : ItemData.Stats.Stats)
	{
		URPGToolTipStatRowWidget* SelectedWidget = GetStatWidget(ItemStat.Stat);
		SelectedWidget->SetItemValue(ItemStat.Value);
		SelectedWidget->SetVisibility(ESlateVisibility::Visible);
	}

	SetRequiredLevel();
	SetDurability();
}

FText URPGToolTipStatsWidget::UpdateWeight() const
{
	return UKismetTextLibrary::Conv_FloatToText(ItemData.Stats.Weight, ERoundingMode::HalfToEven, false, true, 1, 324, 0, 3);
}

FText URPGToolTipStatsWidget::UpdateValue() const
{
	return UKismetTextLibrary::Conv_FloatToText(ItemData.Stats.Value, ERoundingMode::HalfToEven, false, true, 1, 324, 0, 1);
}

FText URPGToolTipStatsWidget::UpdateStackedWeight() const
{
	if (!ItemData.Stacks.bStackable)
	{
		StackedWeight_HBox->SetVisibility(ESlateVisibility::Collapsed);
		return FText();
	}

	StackedWeight_HBox->SetVisibility(ESlateVisibility::Visible);
	return UKismetTextLibrary::Conv_FloatToText(ItemData.Stats.Weight * ItemData.Stacks.Quantity, ERoundingMode::HalfToEven, false, true, 1, 324, 0, 3);
}

FText URPGToolTipStatsWidget::UpdateStackedValue() const
{
	if (!ItemData.Stacks.bStackable)
	{
		StackedWeight_HBox->SetVisibility(ESlateVisibility::Collapsed);
		return FText();
	}

	StackedWeight_HBox->SetVisibility(ESlateVisibility::Visible);
	return UKismetTextLibrary::Conv_FloatToText(ItemData.Stats.Value * ItemData.Stacks.Quantity, ERoundingMode::HalfToEven, false, true, 1, 324, 0, 3);
}

URPGToolTipStatRowWidget* URPGToolTipStatsWidget::GetStatWidget(const EStatCategory Stat) const
{
	URPGToolTipStatRowWidget* Result;

	switch (Stat)
	{
	case EStatCategory::MaxHealth:
		Result = MaxHealth_StatRowW;
		break;

	case EStatCategory::MaxStamina:
		Result = MaxStamina_StatRowW;
		break;

	case EStatCategory::MaxMana:
		Result = MaxMana_StatRowW;
		break;

	case EStatCategory::Armor:
		Result = Armor_StatRowW;
		break;

	case EStatCategory::Damage:
		Result = Damage_StatRowW;
		break;

	case EStatCategory::AttackSpeed:
		Result = AttackSpeed_StatRowW;
		break;

	default:
		Result = nullptr;
		break;
	}

	return Result;
}

void URPGToolTipStatsWidget::SetDurability()
{
	if (ItemData.Stats.Durability.bUseDurability)
	{
		int32 CurrentDurability = UKismetMathLibrary::Clamp(ItemData.Stats.Durability.CurrentDurability, 0, 100);
		DurabilityValue_Text->SetText(UKismetTextLibrary::Conv_IntToText(CurrentDurability));

		if (CurrentDurability < 1)
		{
			Durability_Text->SetColorAndOpacity(Durability_Color);
			DurabilityPerc_Text->SetColorAndOpacity(Durability_Color);
			DurabilityValue_Text->SetColorAndOpacity(Durability_Color);
		}
		return;
	}

	Durability_HBox->SetVisibility(ESlateVisibility::Collapsed);
}

void URPGToolTipStatsWidget::SetRequiredLevel()
{
	if (ItemData.Stats.RequiredLevel > 0)
	{
		ReqLevelValue_Text->SetText(UKismetTextLibrary::Conv_IntToText(ItemData.Stats.RequiredLevel));

		if (ItemData.Stats.RequiredLevel > URPGInventoryFunctionLibrary::GetLevelingComponent()->GetCurrentLevel())
		{
			ReqLevel_Text->SetColorAndOpacity(LevelRequired_Color);
			ReqLevelValue_Text->SetColorAndOpacity(LevelRequired_Color);
		}

		return;
	}

	Level_HBox->SetVisibility(ESlateVisibility::Collapsed); return;
}
