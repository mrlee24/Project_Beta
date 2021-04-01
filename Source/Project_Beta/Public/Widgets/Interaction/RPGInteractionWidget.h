// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Animation/WidgetAnimation.h"
#include "RPGTypes.h"
#include "Styling/SlateBrush.h"
#include "RPGInteractionWidget.generated.h"

class UTexture2D;
class URPGInventoryComponent;

UCLASS()
class PROJECT_BETA_API URPGInteractionWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	URPGInventoryComponent* InventoryComponent;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", BindWidgetAnim))
	//UWidgetAnimation* FillAnim;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EInteractionInputType InputType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FText InteractionText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bGamepadControls;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	UImage* FillBorder_Image;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	UImage* Key_Image;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FSlateBrush InteractionKeyIcon;

protected:
	virtual void NativeConstruct() override;

public:
	void Init(const FText InInteractionText, const EInteractionInputType InInputType)
	{
		InteractionText = InInteractionText;
		InputType = InInputType;
	}

	URPGInventoryComponent* GetInventoryComponent() const { return InventoryComponent; }
	void SetInventoryComponent(URPGInventoryComponent* InInventoryComponent) { InventoryComponent = InInventoryComponent; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FText GetInteractionText() const { return InteractionText; }
	void SetInteractionText(FText InInteractionText) { InteractionText = InInteractionText; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	EInteractionInputType GetInputType() const { return InputType; }
	void SetInputType(EInteractionInputType InInputType) { InputType = InInputType; }

	bool GetGamepadControls() const { return bGamepadControls; }
	void SetGamepadControls(bool InbGamepadControls) { bGamepadControls = InbGamepadControls; }

	UImage* GetFillBorder_Image() const { return FillBorder_Image; }
	void SetFillBorder_Image(UImage* InFillBorder_Image) { FillBorder_Image = InFillBorder_Image; }

	UImage* GetKey_Image() const { return Key_Image; }
	void SetKey_Image(UImage* InKey_Image) { Key_Image = InKey_Image; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FSlateBrush GetInteractionKeyIcon() const { return InteractionKeyIcon; }

	UFUNCTION(BlueprintCallable)
	void SetInteractionIcon(UTexture2D* InteractionTexture);

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ToggleGamepadInputs();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BorderFill(float Value);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetAppropriateFillingBackground();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UpdateInteractionIcon();

	UFUNCTION(BlueprintCallable)
	void SetFillDecimalValue(float Value);
};
