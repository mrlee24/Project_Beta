// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "RPGGoldWeightBarWidget.generated.h"

class URPGInventoryComponent;

UCLASS()
class PROJECT_BETA_API URPGGoldWeightBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Components")
	URPGInventoryComponent* InventoryComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	UImage* Gold_Image;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	UImage* Weight_Image;

protected:
	virtual void NativeConstruct();

public:
	UFUNCTION(BlueprintCallable)
	FText UpdatePlayerGold() const;

	UFUNCTION(BlueprintCallable)
	FText UpdateCurrentInventoryWeight() const;

	UFUNCTION(BlueprintCallable)
	FText UpdateMaxInventoryWeight() const;

	UFUNCTION(BlueprintCallable)
	FSlateColor UpdateInventoryWeightColor() const;

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void PlayAnim();

	URPGInventoryComponent* GetInventoryComponent() const { return InventoryComponent; }
	void SetInventoryComponent(URPGInventoryComponent* InInventoryComponent) { InventoryComponent = InInventoryComponent; }

	UImage* GetGold_Image() const { return Gold_Image; }
	void SetGold_Image(UImage* InGold_Image) { Gold_Image = InGold_Image; }

	UImage* GetWeight_Image() const { return Weight_Image; }
	void SetWeight_Image(UImage* InWeight_Image) { Weight_Image = InWeight_Image; }
};
