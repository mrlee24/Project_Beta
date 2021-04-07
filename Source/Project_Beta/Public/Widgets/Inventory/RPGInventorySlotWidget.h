// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RPGTypes.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "RPGInventorySlotWidget.generated.h"

class URPGInventoryBaseWidget;

UCLASS()
class PROJECT_BETA_API URPGInventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defauts", meta = (AllowPrivateAccess = "true"))
	FRPGItemData ItemData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defauts", meta = (AllowPrivateAccess = "true"))
	bool bGamepadControls;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defauts", meta = (AllowPrivateAccess = "true"))
	URPGInventoryBaseWidget* InventoryBase_Widget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defauts", meta = (AllowPrivateAccess = "true"))
	FLinearColor BorderUnHovered;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defauts", meta = (AllowPrivateAccess = "true"))
	FLinearColor BorderHovered;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defauts", meta = (AllowPrivateAccess = "true", BindWidget))
	UBorder* Slot_Border;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defauts", meta = (AllowPrivateAccess = "true", BindWidget))
	UButton* Slot_Button;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defauts", meta = (AllowPrivateAccess = "true", BindWidget))
	UTextBlock* SlotQuantity_Text;
};
