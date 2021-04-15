// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "RPGTypes.h"
#include "RPGInventoryPanelWidget.generated.h"

class URPGInventoryComponent;
class URPGInventorySlotWidget;
class URPGInventoryBaseWidget;

UCLASS()
class PROJECT_BETA_API URPGInventoryPanelWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	URPGInventoryComponent* InventoryComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defautls", meta = (AllowPrivateAccess = "true"))
	FText Title;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defautls", meta = (AllowPrivateAccess = "true"))
	EItemType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defautls", meta = (AllowPrivateAccess = "true"))
	FButtonStyle ButtonStyleOn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defautls", meta = (AllowPrivateAccess = "true"))
	FButtonStyle ButtonStyleOff;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defautls", meta = (AllowPrivateAccess = "true"))
	FSlateBrush ButtonIcon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defautls", meta = (AllowPrivateAccess = "true", BindWidget))
	UUniformGridPanel* UniformGrid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defautls", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<URPGInventorySlotWidget> InventorySlot_Class;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defautls", meta = (AllowPrivateAccess = "true"))
	URPGInventorySlotWidget* InventorySlot_Widget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true"))
	URPGInventoryBaseWidget* InventoryBase_Widget;

public:
	FText GetTitle() const { return Title; }
	EItemType GetType() const { return Type; }
	FSlateBrush GetButtonIcon() const { return ButtonIcon; }
	UUniformGridPanel* GetUniformGrid() const { return UniformGrid; }

public:
	void Init(URPGInventoryComponent* InInventoryComponent, URPGInventoryBaseWidget* InInventoryBase_Widget);
	void BuildInventory(const int32 InventorySize, TArray<FRPGItemData>* InventoryData, int32 InColumnPosition, int32 InRowPosition, int32 InRowLength);

};
