// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Inventory/RPGGoldWeightBarWidget.h"
#include "Kismet/KismetTextLibrary.h"
#include "Components/RPGInventoryComponent.h"
#include "Libraries/RPGInventoryFunctionLibrary.h"

void URPGGoldWeightBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InventoryComponent = URPGInventoryFunctionLibrary::GetInventoryComponent();
}

FText URPGGoldWeightBarWidget::UpdatePlayerGold() const
{
	if (!InventoryComponent) return FText();

	return UKismetTextLibrary::Conv_FloatToText(InventoryComponent->GetPlayerGold(), ERoundingMode::HalfToEven, false, true, 1, 324, 0, 0);
}

FText URPGGoldWeightBarWidget::UpdateCurrentInventoryWeight() const
{
	if (!InventoryComponent) return FText();

	return UKismetTextLibrary::Conv_FloatToText(InventoryComponent->GetCurrentInventoryWeight(), ERoundingMode::HalfToEven, false, true, 1, 324, 0, 1);
}

FText URPGGoldWeightBarWidget::UpdateMaxInventoryWeight() const
{
	if (!InventoryComponent) return FText();

	return UKismetTextLibrary::Conv_FloatToText(InventoryComponent->GetMaxInventoryWeight(), ERoundingMode::HalfToEven, false, true, 1, 324, 0, 1);
}

FSlateColor URPGGoldWeightBarWidget::UpdateInventoryWeightColor() const
{
	if (!InventoryComponent) return FSlateColor();

	return (InventoryComponent->GetCurrentInventoryWeight() > InventoryComponent->GetMaxInventoryWeight()) ? FSlateColor(FLinearColor::Red) : FSlateColor(FLinearColor::White);
}
