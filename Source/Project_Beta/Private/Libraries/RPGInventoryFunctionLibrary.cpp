// Fill out your copyright notice in the Description page of Project Settings.


#include "Libraries/RPGInventoryFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Characters/RPGPlayerCharacter.h"

TArray<FRPGItemData> URPGInventoryFunctionLibrary::SortItemsByType(const TArray<FRPGItemData> DataArray)
{
	TArray<FRPGItemData> Armor;
	TArray<FRPGItemData> Weapons;
	TArray<FRPGItemData> Shields;
	TArray<FRPGItemData> Ammo;
	TArray<FRPGItemData> Accessories;
	TArray<FRPGItemData> Potions;
	TArray<FRPGItemData> CrIngredients;
	TArray<FRPGItemData> QuestItems;

	TArray<FRPGItemData> SortedArray;

	for (auto& ArrayElement : DataArray)
	{
		if (ArrayElement.Type != EItemType::None)
		{
			switch (ArrayElement.Type)
			{
			case EItemType::Armor:
				Armor.Add(ArrayElement);
				break;

			case EItemType::Weapon:
				Weapons.Add(ArrayElement);
				break;

			case EItemType::Shield:
				Shields.Add(ArrayElement);
				break;

			case EItemType::Ammo:
				Ammo.Add(ArrayElement);
				break;

			case EItemType::Accessory:
				Accessories.Add(ArrayElement);
				break;

			case EItemType::Potion:
				Potions.Add(ArrayElement);
				break;

			case EItemType::CraftingIngredient:
				CrIngredients.Add(ArrayElement);
				break;

			case EItemType::QuestItem:
				QuestItems.Add(ArrayElement);
				break;
			}
		}
	}

	SortedArray.Append(Armor);
	SortedArray.Append(Weapons);
	SortedArray.Append(Shields);
	SortedArray.Append(Ammo);
	SortedArray.Append(Accessories);
	SortedArray.Append(Potions);
	SortedArray.Append(CrIngredients);
	SortedArray.Append(QuestItems);

	return SortedArray;
}

TArray<FRPGItemData> URPGInventoryFunctionLibrary::SortItemsByRarity(const TArray<FRPGItemData> DataArray)
{
	TArray<FRPGItemData> Common;
	TArray<FRPGItemData> Rare;
	TArray<FRPGItemData> Epic;
	TArray<FRPGItemData> Legendary;
	TArray<FRPGItemData> Useable;
	TArray<FRPGItemData> Consumable;

	TArray<FRPGItemData> SortedArray;

	for (auto& ArrayElement : DataArray)
	{
		if (ArrayElement.Rarity != EItemRarity::None)
		{
			switch (ArrayElement.Rarity)
			{
			case EItemRarity::Common:
				Common.Add(ArrayElement);
				break;

			case EItemRarity::Rare:
				Rare.Add(ArrayElement);
				break;

			case EItemRarity::Epic:
				Rare.Add(ArrayElement);
				break;

			case EItemRarity::Legendary:
				Legendary.Add(ArrayElement);
				break;

			case EItemRarity::Useable:
				Useable.Add(ArrayElement);
				break;

			case EItemRarity::Consumable:
				Consumable.Add(ArrayElement);
				break;
			}
		}
	}

	SortedArray.Append(Common);
	SortedArray.Append(Rare);
	SortedArray.Append(Epic);
	SortedArray.Append(Legendary);
	SortedArray.Append(Useable);
	SortedArray.Append(Consumable);

	return SortedArray;
}

TArray<FRPGItemData> URPGInventoryFunctionLibrary::SortItemByValue(const TArray<FRPGItemData> DataArray)
{
	TArray<FRPGItemData> SortedArray;
	bool bFound = false;

	for (auto& ArrayElement : DataArray)
	{
		if (ArrayElement.IsValid())
		{
			for (int32 Index = 0; Index < SortedArray.Num(); Index++)
			{
				if (ArrayElement.Stats.Value > SortedArray[Index].Stats.Value)
				{
					bFound = true;
					SortedArray.Insert(ArrayElement, Index);
				}
			}

			if (bFound)
				bFound = false;
			else
				SortedArray.Add(ArrayElement);
		}
	}

	return SortedArray;
}

TArray<FRPGItemData> URPGInventoryFunctionLibrary::SortItemByWeight(const TArray<FRPGItemData> DataArray)
{
	TArray<FRPGItemData> SortedArray;
	bool bFound = false;

	for (auto& ArrayElement : DataArray)
	{
		if (ArrayElement.IsValid())
		{
			for (int32 Index = 0; Index < SortedArray.Num(); Index++)
			{
				if (ArrayElement.Stats.Weight > SortedArray[Index].Stats.Weight)
				{
					bFound = true;
					SortedArray.Insert(ArrayElement, Index);
				}
			}

			if (bFound)
				bFound = false;
			else
				SortedArray.Add(ArrayElement);
		}
	}

	return SortedArray;
}

TArray<FRPGItemData> URPGInventoryFunctionLibrary::QuickSortItems(const TArray<FRPGItemData> DataArray)
{
	TArray<FRPGItemData> SortedArray;

	for (auto& ArrayElement : DataArray)
	{
		if (ArrayElement.IsValid())
			SortedArray.Add(ArrayElement);
	}

	return SortedArray;
}

TArray<FRPGItemData> URPGInventoryFunctionLibrary::GetAllItemsOfType(const TArray<FRPGItemData> DataArray, const EItemType ItemType)
{
	TArray<FRPGItemData> SeparatedItems;
	for (auto& ArrayElement : DataArray)
	{
		if (ArrayElement.Type == ItemType)
			SeparatedItems.Add(ArrayElement);
	}

	return SeparatedItems;
}

ARPGPlayerCharacter* URPGInventoryFunctionLibrary::GetPlayerReference()
{
	ARPGPlayerCharacter* PlayerCharacter = Cast<ARPGPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GEngine->GameViewport->GetWorld(), 0));

	if (PlayerCharacter)
		return PlayerCharacter;

	return nullptr;
}

URPGInventoryComponent* URPGInventoryFunctionLibrary::GetInventoryComponent()
{
	ARPGPlayerCharacter* PlayerCharacter = URPGInventoryFunctionLibrary::GetPlayerReference();

	//URPGInventoryComponent* InventoryComponent = PlayerCharacter->GetInventoryComponent();

	//if (InventoryComponent)
	//	return InventoryComponent;

	return nullptr;
}

void URPGInventoryFunctionLibrary::ItemData_Array_Set(TArray<FRPGItemData>& TargetArray, int32 Index, const FRPGItemData Item /*= FRPGItemData()*/, bool bSizeToFit /*= false*/)
{
	if (!TargetArray.IsValidIndex(Index) && bSizeToFit && (Index >= 0))
		(&TargetArray)->SetNum(Index + 1);

	if (TargetArray.IsValidIndex(Index))
		TargetArray[Index] = Item;
}

bool URPGInventoryFunctionLibrary::ItemType_Map_Find(const TMap<EItemType, int32>& TargetMap, const EItemType& Key, int32& Value)
{
	if (const int32* CurrentValue = TargetMap.Find(Key))
	{
		Value = *CurrentValue;
		return true;
	}
	return false;
}

bool URPGInventoryFunctionLibrary::ItemMap_Map_Find(const TMap<int32, FRPGItemData>& TargetMap, const int32& Key, FRPGItemData& Value)
{
	if (const FRPGItemData* CurrentValue = TargetMap.Find(Key))
	{
		Value = *CurrentValue;
		return true;
	}
	return false;
}