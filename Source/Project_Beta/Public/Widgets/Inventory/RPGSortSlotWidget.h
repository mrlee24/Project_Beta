// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "RPGTypes.h"
#include "Components/TextBlock.h"
#include "RPGSortSlotWidget.generated.h"

class URPGInventoryComponent;
class URPGSortWindowWidget;

UCLASS()
class PROJECT_BETA_API URPGSortSlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	URPGInventoryComponent* InventoryComponent;

	UPROPERTY(BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	UBorder* Slot_Border;

	UPROPERTY(BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	UButton* Slot_Button;

	UPROPERTY(BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	UTextBlock* Title_Text;

	UPROPERTY(BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true"))
	URPGSortWindowWidget* SortWindow_Widget;

	UPROPERTY(BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true"))
	bool bGamepadControls;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true"))
	ESortMethod SortingMethod;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true"))
	FText Title = FText::FromString("Title");

protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ToggleGamepadInputs();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void PressedSortKey();

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsUsingGamepad() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FText UpdateTitle() const;

public:
	URPGInventoryComponent* GetInventoryComponent() const { return InventoryComponent; }
	void SetInventoryComponent(URPGInventoryComponent* InInventoryComponent) { InventoryComponent = InInventoryComponent; }

	URPGSortWindowWidget* GetSortWindow_Widget() const { return SortWindow_Widget; }
	void SetSortWindow_Widget(URPGSortWindowWidget* InSortWindow_Widget) { SortWindow_Widget = InSortWindow_Widget; }
};
