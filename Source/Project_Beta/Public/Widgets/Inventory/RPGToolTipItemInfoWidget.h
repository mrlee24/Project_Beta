// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RPGTypes.h"
#include "Components/Image.h"
#include "RPGToolTipItemInfoWidget.generated.h"

class URPGInventoryComponent;

UCLASS()
class PROJECT_BETA_API URPGToolTipItemInfoWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	URPGInventoryComponent* InventoryComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true"))
	FRPGItemData ItemData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	UImage* Background_Image;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	UImage* Thumbnail_Image;

public:
	URPGInventoryComponent* GetInventoryComponent() const { return InventoryComponent; }
	void SetInventoryComponent(URPGInventoryComponent* InInventoryComponent) { InventoryComponent = InInventoryComponent; }

	FRPGItemData GetItemData() const { return ItemData; }
	void SetItemData(FRPGItemData InItemData) { ItemData = InItemData; }
};
