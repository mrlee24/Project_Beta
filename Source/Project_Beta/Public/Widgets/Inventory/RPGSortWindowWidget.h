// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RPGTypes.h"
#include "RPGSortWindowWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEndSorting);

class URPGInventoryComponent;
class URPGSortSlotWidget;

UCLASS()
class PROJECT_BETA_API URPGSortWindowWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	URPGInventoryComponent* InventoryComponent;

	UPROPERTY(BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	URPGSortSlotWidget* Type_SortSlotW;

	UPROPERTY(BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	URPGSortSlotWidget* Rarity_SortSlotW;

	UPROPERTY(BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	URPGSortSlotWidget* Value_SortSlotW;

	UPROPERTY(BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	URPGSortSlotWidget* Weight_SortSlotW;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bGamepadControls;

	UPROPERTY(BlueprintAssignable, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FOnEndSorting OnEndSorting;

protected:
	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ToggleGamepadInputs();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ToggleSortingWindow();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnSort(const ESortMethod SortingMethod);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void EndSorting();

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<URPGSortSlotWidget*> GetAllButtons() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsUsingGamepad() const;

public:
	URPGInventoryComponent* GetInventoryComponent() const { return InventoryComponent; }
	void SetInventoryComponent(URPGInventoryComponent* InInventoryComponent) { InventoryComponent = InInventoryComponent; }
};
