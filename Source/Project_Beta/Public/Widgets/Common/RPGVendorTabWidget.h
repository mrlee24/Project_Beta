// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Common/RPGTabBaseWidget.h"
#include "Components/Button.h"
#include "RPGTypes.h"
#include "RPGVendorTabWidget.generated.h"

UCLASS()
class PROJECT_BETA_API URPGVendorTabWidget : public URPGTabBaseWidget
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	UButton* Vendor_Button;
	
public:
	virtual UButton* GetButtonByWidgetType(const EWidgetType WidgetType) const;
};
