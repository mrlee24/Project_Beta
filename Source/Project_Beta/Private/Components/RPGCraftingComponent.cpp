// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/RPGCraftingComponent.h"
#include "Components/RPGInventoryComponent.h"
#include "Widgets/Crafting/RPGCraftingItemWidget.h"
#include "Widgets/Crafting/RPGCraftingWindowWidget.h"
#include "Widgets/Crafting/RPGCraftingRequiredSlotWidget.h"

// Sets default values for this component's properties
URPGCraftingComponent::URPGCraftingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void URPGCraftingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

TArray<FRPGCrafting> URPGCraftingComponent::FilterByRarity(TArray<FRPGCrafting> CraftingData) const
{
	TArray<FRPGCrafting> FilteredArray;
	TArray<FRPGCrafting> CommonArray;
	TArray<FRPGCrafting> RareArray;
	TArray<FRPGCrafting> EpicArray;
	TArray<FRPGCrafting> LegendaryArray;
	TArray<FRPGCrafting> ConsumableArray;

	for (auto& CraftingElement : CraftingData)
	{
		const FDataTableRowHandle TableAndRow = CraftingElement.CraftableItem.TableAndRow;
		const UDataTable* SingleDT = TableAndRow.DataTable;
		const FName RowName = TableAndRow.RowName;

		const FRPGItemData OutRow = *SingleDT->FindRow<FRPGItemData>(RowName, "");

		if (OutRow.Rarity != EItemRarity::None)
		{
			switch (OutRow.Rarity)
			{
			case EItemRarity::Common:
				CommonArray.Add(CraftingElement);
				break;

			case EItemRarity::Rare:
				RareArray.Add(CraftingElement);
				break;

			case EItemRarity::Epic:
				EpicArray.Add(CraftingElement);
				break;

			case EItemRarity::Legendary:
				LegendaryArray.Add(CraftingElement);
				break;

			case EItemRarity::Consumable:
				ConsumableArray.Add(CraftingElement);
				break;
			}
		}
	}

	FilteredArray.Append(CommonArray);
	FilteredArray.Append(RareArray);
	FilteredArray.Append(EpicArray);
	FilteredArray.Append(LegendaryArray);
	FilteredArray.Append(ConsumableArray);

	return FilteredArray;
}
