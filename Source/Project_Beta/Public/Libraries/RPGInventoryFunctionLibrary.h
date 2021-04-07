// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RPGTypes.h"
#include "RPGInventoryFunctionLibrary.generated.h"

class ARPGPlayerCharacter;

UCLASS()
class PROJECT_BETA_API URPGInventoryFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static void FindEmptyEquipmentSlot(const TMultiMap<FRPGItemSlot, FRPGItemData> EquipmentData, const TArray<FRPGItemSlot> SlotsToSearch, const FRPGItemSlot DefaulSlot, FRPGItemSlot& SlotFound, bool& bFound);

	UFUNCTION(BlueprintCallable)
	static bool HasPartialStack(const TArray<FRPGItemData> DataArray, FRPGItemData ItemData, int32& SlotIndex);

	UFUNCTION(BlueprintCallable)
	static bool HasSpaceInDataArray(TArray<FRPGItemData>& DataArray, int32& SlotIndex);

	UFUNCTION(BlueprintCallable)
	static bool CanItemBeRemoved(const FRPGItemData ItemData);

	UFUNCTION(BlueprintCallable)
	static void FindItemIndex(const TArray<FRPGItemData> DataArray, const FRPGItemData SecondItem, bool& bFound, int32& SlotIndex);

	UFUNCTION(BlueprintCallable)
	static void FindItemByID(const TArray<FRPGItemData> DataArray, const FString ItemID, bool& bFound, FRPGItemData& ItemFound);

	UFUNCTION(BlueprintCallable)
	static void FindItemStat(const TArray<FRPGStatRow> DataArray, const EStatCategory Stat, bool& bFound, int32& StatIndex);

	UFUNCTION(BlueprintCallable)
	static bool AreItemsStackable(const FRPGItemData FirstItem, const FRPGItemData SecondItem);
	
public:
	UFUNCTION(BlueprintCallable, Category = "Items Sorting")
	static TArray<FRPGItemData> SortItemsByType(const TArray<FRPGItemData> DataArray);

	UFUNCTION(BlueprintCallable, Category = "Items Sorting")
	static TArray<FRPGItemData> SortItemsByRarity(const TArray<FRPGItemData> DataArray);

	UFUNCTION(BlueprintCallable, Category = "Items Sorting")
	static TArray<FRPGItemData> SortItemByValue(const TArray<FRPGItemData> DataArray);

	UFUNCTION(BlueprintCallable, Category = "Items Sorting")
	static TArray<FRPGItemData> SortItemByWeight(const TArray<FRPGItemData> DataArray);

	UFUNCTION(BlueprintCallable, Category = "Items Sorting")
	static TArray<FRPGItemData> QuickSortItems(const TArray<FRPGItemData> DataArray);

public:
	UFUNCTION(BlueprintCallable)
	static TArray<FRPGItemData> GetAllItemsOfType(const TArray<FRPGItemData> DataArray, const EItemType ItemType);

	UFUNCTION(BlueprintCallable)
	static ARPGPlayerCharacter* GetPlayerReference();

	UFUNCTION(BlueprintCallable)
	static URPGInventoryComponent* GetInventoryComponent();

public:
	static void ItemData_Array_Set(TArray<FRPGItemData>& TargetArray, int32 Index, const FRPGItemData Item = FRPGItemData(), bool bSizeToFit = false);
	static bool ItemType_Map_Find(const TMap<EItemType, int32>& TargetMap, const EItemType& Key, int32& Value);
	static bool ItemMap_Map_Find(const TMap<int32, FRPGItemData>& TargetMap, const int32& Key, FRPGItemData& Value);

	static bool LevelingMap_Map_Find(const TMap<int32, float>& TargetMap, const int32& Key, float& Value);

	static bool EquipmentData_Map_Find(const TMultiMap<FRPGItemSlot, FRPGItemData>& TargetMap, const FRPGItemSlot& Key, FRPGItemData& Value);
};
