// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Inventory/RPGToolTipStatRowWidget.h"
#include "Kismet/KismetTextLibrary.h"

void URPGToolTipStatRowWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	StatName_Text->SetText(StatName);
}

FText URPGToolTipStatRowWidget::UpdateComparisonValue() const
{
	const float LocalValue = StatRow.Value - ComparisonValue;
	FText ResultText;

	if (LocalValue > 0.f)
	{
		FString TempString = " + " + UKismetTextLibrary::Conv_FloatToText(LocalValue, ERoundingMode::HalfToEven, false, true, 1, 324, 0, 2).ToString();
		return ResultText = FText::FromString(TempString);
	}

	return ResultText = UKismetTextLibrary::Conv_FloatToText(LocalValue, ERoundingMode::HalfToEven, false, true, 1, 324, 0, 2);
}

FSlateColor URPGToolTipStatRowWidget::UpdateComparisonColor() const
{
	FSlateColor ResultColor;

	if (StatRow.Value > ComparisonValue)
	{
		const FLinearColor SpecifiedColor = { 0.f, 0.630208f, 0.069169f, 1.f };

		ResultColor = { SpecifiedColor };
	}

	if (StatRow.Value == ComparisonValue)
	{
		const FLinearColor SpecifiedColor = { 0.626207f, 0.630208f, 0.609449f, 1.f };

		ResultColor = { SpecifiedColor };
	}

	if (StatRow.Value < ComparisonValue)
	{
		const FLinearColor SpecifiedColor = { 0.630208f, 0.f, 0.031315f, 1.f };

		ResultColor = { SpecifiedColor };
	}

	return ResultColor;
}
