// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "RPGRotateItemBoxWidget.generated.h"

class URPGInventoryComponent;

UCLASS()
class PROJECT_BETA_API URPGRotateItemBoxWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	URPGInventoryComponent* InventoryComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true", BindWidget))
	UImage* Background_Image;

protected:
	virtual void NativeConstruct() override;
};
