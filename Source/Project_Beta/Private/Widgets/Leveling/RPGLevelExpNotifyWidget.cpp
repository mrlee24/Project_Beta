// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Leveling/RPGLevelExpNotifyWidget.h"

void URPGLevelExpNotifyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	(Level > 0) ? PlayLevelAnimtion() : PlayExperienceAnimation();
}

FText URPGLevelExpNotifyWidget::GetLevelText() const
{
	TArray<FStringFormatArg> Args; 
	Args.Add(FStringFormatArg(Level));
	FString Result = FString::Format(TEXT("LEVEL {0} "), Args);
	return FText::FromString(Result);
}

FText URPGLevelExpNotifyWidget::GetExperienceText() const
{
	TArray<FStringFormatArg> Args;
	Args.Add(FStringFormatArg(Experience));
	FString Result = FString::Format(TEXT("+{0} EXP"), Args);
	return FText::FromString(Result);
}
