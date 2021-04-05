// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RPGVendorWidget.generated.h"

class URPGGoldWeightBarWidget;

UCLASS()
class PROJECT_BETA_API URPGVendorWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	URPGGoldWeightBarWidget* GoldWeightBar_Widget;

public:
	URPGGoldWeightBarWidget* GetGoldWeightBar_Widget() const { return GoldWeightBar_Widget; }
	void SetGoldWeightBar_Widget(URPGGoldWeightBarWidget* InGoldWeightBar_Widget) { GoldWeightBar_Widget = InGoldWeightBar_Widget; }
};
