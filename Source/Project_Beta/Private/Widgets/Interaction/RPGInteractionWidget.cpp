// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Interaction/RPGInteractionWidget.h"
#include "Kismet/KismetMathLibrary.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void URPGInteractionWidget::SetInteractionIcon(UTexture2D* InteractionTexture)
{
	UWidgetBlueprintLibrary::SetBrushResourceToTexture(InteractionKeyIcon, InteractionTexture);
}

void URPGInteractionWidget::SetFillDecimalValue(float Value)
{
	const float ClampValue = UKismetMathLibrary::Clamp(Value, 0.05f, 1.f);
	FillBorder_Image->GetDynamicMaterial()->SetScalarParameterValue(FName("Decimal"), ClampValue);
}
