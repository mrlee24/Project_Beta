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
	//static bool EquipmentData_Map_Find(const TMultiMap<EItemSlot, FRPGItemData>& TargetMap, const EItemSlot& Key, FRPGItemData& Value);
};
