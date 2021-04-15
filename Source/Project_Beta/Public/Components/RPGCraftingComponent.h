// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "RPGTypes.h"
#include "RPGCraftingComponent.generated.h"

class URPGInventoryComponent;
class URPGCraftingItemWidget;
class URPGCraftingWindowWidget;
class URPGCraftingRequiredSlotWidget;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class PROJECT_BETA_API URPGCraftingComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Category", meta = (AllowPrivateAccess = "true"))
	URPGInventoryComponent* InventoryComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UDataTable* DataTable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<FRPGCrafting> ArmorList;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<FRPGCrafting> WeaponList;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<FRPGCrafting> RequiredIngredientList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<URPGCraftingItemWidget> CraftingItem_Class;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	URPGCraftingItemWidget* CraftingItem_Widget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<URPGCraftingWindowWidget> CraftingWindow_Class;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	URPGCraftingWindowWidget* CraftingWindow_Widget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<URPGCraftingRequiredSlotWidget> CraftingRequiredSlot_Class;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	URPGCraftingRequiredSlotWidget* CraftingRequiredSlot_Widget;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FRPGItemData PreviewItemData;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bIsCraftingOpen = false;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bIsPlayerNearAForge = false;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bCanBeAddedToInventory = false;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float DefaultCaptureRotation = 0.f;

public:	
	// Sets default values for this component's properties
	URPGCraftingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable, Category = "Filter")
	TArray<FRPGCrafting> FilterByRarity(TArray<FRPGCrafting> CraftingData) const;

public:
	URPGInventoryComponent* GetInventoryComponent() const { return InventoryComponent; }
	UDataTable* GetDataTable() const { return DataTable; }
	TArray<FRPGCrafting> GetArmorList() const { return ArmorList; }
	TArray<FRPGCrafting> GetWeaponList() const { return WeaponList; }
	TArray<FRPGCrafting> GetRequiredIngredientList() const { return RequiredIngredientList; }
	URPGCraftingItemWidget* GetCraftingItem_Widget() const { return CraftingItem_Widget; }
	URPGCraftingWindowWidget* GetCraftingWindow_Widget() const { return CraftingWindow_Widget; }
	URPGCraftingRequiredSlotWidget* GetCraftingRequiredSlot_Widget() const { return CraftingRequiredSlot_Widget; }
	FRPGItemData GetPreviewItemData() const { return PreviewItemData; }
	void SetPreviewItemData(FRPGItemData InPreviewItemData) { PreviewItemData = InPreviewItemData; }
	bool GetIsCraftingOpen() const { return bIsCraftingOpen; }
	void SetIsCraftingOpen(bool InbIsCraftingOpen) { bIsCraftingOpen = InbIsCraftingOpen; }
	bool GetIsPlayerNearAForge() const { return bIsPlayerNearAForge; }
	void SetIsPlayerNearAForge(bool InbIsPlayerNearAForge) { bIsPlayerNearAForge = InbIsPlayerNearAForge; }
	bool GetCanBeAddedToInventory() const { return bCanBeAddedToInventory; }
	void SetCanBeAddedToInventory(bool InbCanBeAddedToInventory) { bCanBeAddedToInventory = InbCanBeAddedToInventory; }
	float GetDefaultCaptureRotation() const { return DefaultCaptureRotation; }
	void SetDefaultCaptureRotation(float InDefaultCaptureRotation) { DefaultCaptureRotation = InDefaultCaptureRotation; }
};
