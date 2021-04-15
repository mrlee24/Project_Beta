// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Common/RPGTabBaseWidget.h"
#include "RPGLoadGameTabWidget.generated.h"


UCLASS()
class PROJECT_BETA_API URPGLoadGameTabWidget : public URPGTabBaseWidget
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	UButton* LoadGame_Button;

protected:
	virtual void NativeConstruct() override;
};
