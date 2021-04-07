// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RPGTypes.h"
#include "RPGInventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGamepadToggled, bool, bGamepadControls);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameUnfreezed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryRefreshed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnItemsBarRefreshed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnVendorStorageRefreshed);

class URPGInteractionComponent;
class URPGInteractableComponent;
class URPGActionConsumablesComponent;
class URPGLevelingComponent;
class URPGVendorWidget;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_BETA_API URPGInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	URPGInteractionComponent* InteractionComponent;

	UPROPERTY(BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	URPGActionConsumablesComponent* ActionConsumablesComponent;
	
	UPROPERTY(BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	URPGInteractableComponent* CurrentInteractableComponent;

	UPROPERTY(BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	URPGLevelingComponent* LevelingComponent;

	UPROPERTY(BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	float CurrentInventoryWeight = 0.f;

	UPROPERTY(BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	bool bInventoryOpen = false;

	// EditAnywhere just for debugging
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	TMap<EItemType, FRPGInventoryPanelData> InventoryData;

	//UPROPERTY(BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	//TSubclassOf<URPGInventoryOverallWidget> InventoryOverall_Class;

	//UPROPERTY(BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	//URPGInventoryOverallWidget* InventoryOverall_Widget;

	//UPROPERTY(BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	//URPGInventoryBaseWidget* InventoryBase_Widget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bGamepadControls = false;

	UPROPERTY(BlueprintReadWrite, Category = "Vendor & Storage", meta = (AllowPrivateAccess = "true"))
	bool bVendorStorageOpen = false;

	UPROPERTY(BlueprintReadWrite, Category = "Vendor & Storage", meta = (AllowPrivateAccess = "true"))
	URPGVendorWidget* Vendor_Widget;

	//UPROPERTY(BlueprintReadWrite, Category = "Vendor & Storage", meta = (AllowPrivateAccess = "true"))
	//URPGStorageWidget* Storage_Widget;

	//UPROPERTY(BlueprintReadWrite, Category = "Vendor & Storage", meta = (AllowPrivateAccess = "true"))
	//URPGVendorStorageInventoryWidget* VendorStorageInventory_Widget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player", meta = (AllowPrivateAccess = "true"))
	float PlayerGold = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customizable", meta = (AllowPrivateAccess = "true"))
	float MaxInventoryWeight = 120.f;

public:
	UPROPERTY(BlueprintAssignable)
	FOnGamepadToggled OnGamepadToggled;

private:
	TArray<FRPGItemData>* SelectCorrectInventory(const FRPGItemData ItemData);
	void AssignItemsToCorrectInventory(const EItemType Type, TArray<FRPGItemData> ItemsArray);
	TArray<FRPGItemData>* GetInventoryByType(const EItemType Type);
	void SortEveryPanel(const ESortMethod Selection);
	void SortActivePanel(const ESortMethod Selection);
	void AddItemToEmptySlotInInventory(TArray<FRPGItemData>* InventoryArray, const FRPGItemData ItemData, int32& AddedSlotIndex, bool& bInventoryFull);

public:
	// Sets default values for this component's properties
	URPGInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void TryToAddToInventory(const FRPGItemData ItemData, int32& AddedSlotIndex, bool& bInventoryFull);

	void AddStackToInventory(const int32 SlotIndex, TArray<FRPGItemData>* InventoryArray, const FRPGItemData ItemData);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void RefreshInventory();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddItemWeight(const FRPGItemData ItemData);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void RemoveItemWeight(const FRPGItemData ItemData);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Inventory")
	TArray<FRPGItemData> GetCombinedInventories() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Inventory")
	FRPGItemData GetInventoryItemByID(const FString ID, const bool bSpecifiedType, const EItemType Type, bool& bFound);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Inventory")
	FRPGItemData GetInventoryItemByData(const FRPGItemData ItemData, bool& bFound);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool CheckInventorySpace(const EItemType Type);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void ReplaceItemInInventory(const FRPGItemData ItemData);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool IsInventoryOverweighted(); 
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void CanBeAddedToSlotInInventory(const FRPGItemData ItemData, bool& bAdded);

public:
	UFUNCTION(BlueprintCallable, Category = "Player")
	bool IsPlayerGoldEnough(const FRPGItemData ItemData) const;

	UFUNCTION(BlueprintCallable, Category = "Player")
	void AddItemGold(const FRPGItemData ItemData);

	UFUNCTION(BlueprintCallable, Category = "Player")
	void RemoveItemGold(const FRPGItemData ItemData);

	UFUNCTION(BlueprintCallable, Category = "Player")
	void AddGoldToPlayerInventory(const float Amount = 0.f);

	UFUNCTION(BlueprintCallable, Category = "Player")
	void RemoveGoldFromPlayerInventory(const float Amount = 0.f);

public:
	UFUNCTION(BlueprintCallable, Category = "Sorting Items")
	void SortByType(const EItemType Type);

	UFUNCTION(BlueprintCallable, Category = "Sorting Items")
	void SortItemsInInventory(const bool bEveryPanel, const ESortMethod Method);

	UFUNCTION(BlueprintCallable, Category = "Sorting Items")
	void SortByRarity(const EItemType Type);

	UFUNCTION(BlueprintCallable, Category = "Sorting Items")
	void SortByValue(const EItemType Type);

	UFUNCTION(BlueprintCallable, Category = "Sorting Items")
	void SortByWeight(const EItemType Type);

	UFUNCTION(BlueprintCallable, Category = "Sorting Items")
	void QuickSort(const EItemType Type);

public:
	TMap<EItemType, FRPGInventoryPanelData> GetInventoryData() const { return InventoryData; }
	void SetInventoryData(TMap<EItemType, FRPGInventoryPanelData> InInventoryData) { InventoryData = InInventoryData; }

	float GetCurrentInventoryWeight() const { return CurrentInventoryWeight; }
	void SetCurrentInventoryWeight(float InCurrentInventoryWeight) { CurrentInventoryWeight = InCurrentInventoryWeight; }

	float GetMaxInventoryWeight() const { return MaxInventoryWeight; }
	void SetMaxInventoryWeight(float InMaxInventoryWeight) { MaxInventoryWeight = InMaxInventoryWeight; }

	bool GetInventoryOpen() const { return bInventoryOpen; }
	void SetInventoryOpen(bool InbInventoryOpen) { bInventoryOpen = InbInventoryOpen; }

	float GetPlayerGold() const { return PlayerGold; }
	void SetPlayerGold(float InPlayerGold) { PlayerGold = InPlayerGold; }

	bool GetGamepadControls() const { return bGamepadControls; }
	void SetGamepadControls(bool InbGamepadControls) { bGamepadControls = InbGamepadControls; }
};
