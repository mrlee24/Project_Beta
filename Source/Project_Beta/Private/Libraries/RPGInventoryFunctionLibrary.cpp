// Fill out your copyright notice in the Description page of Project Settings.


#include "Libraries/RPGInventoryFunctionLibrary.h"
#include "Interfaces/RPGPlayerCharacterInterface.h"
#include "Actors/Interactables/RPGItemBase.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Characters/RPGPlayerCharacter.h"

TArray<FRPGItemData> URPGInventoryFunctionLibrary::SortItemsByType(const TArray<FRPGItemData> DataArray)
{
	TArray<FRPGItemData> Armor;
	TArray<FRPGItemData> Weapons;
	TArray<FRPGItemData> Ammo;
	TArray<FRPGItemData> Accessories;
	TArray<FRPGItemData> Potions;
	TArray<FRPGItemData> CrIngredients;
	TArray<FRPGItemData> QuestItems;

	TArray<FRPGItemData> SortedArray;

	for (auto& ArrayElement : DataArray)
	{
		/*if (ArrayElement.Type != EItemType::None)
		{
			switch (ArrayElement.Type)
			{
			case EItemType::Armor:
				Armor.Add(ArrayElement);
				break;

			case EItemType::Weapon:
				Weapons.Add(ArrayElement);
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
		}*/
	}

	SortedArray.Append(Armor);
	SortedArray.Append(Weapons);
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

	//for (auto& ArrayElement : DataArray)
	//{
	//	if (ArrayElement.IsValid())
	//		SortedArray.Add(ArrayElement);
	//}

	return SortedArray;
}

void URPGInventoryFunctionLibrary::FindEmptyEquipmentSlot(const TMultiMap<FRPGItemSlot, FRPGItemData> EquipmentData, const TArray<FRPGItemSlot> SlotsToSearch, const FRPGItemSlot DefaulSlot, FRPGItemSlot& SlotFound, bool& bFound)
{
	FRPGItemData Item;
	FRPGItemSlot Slot;
	for (auto& ItemSlot : SlotsToSearch)
	{

		if (URPGInventoryFunctionLibrary::EquipmentData_Map_Find(EquipmentData, ItemSlot, Item))
		{
			if (Item.Class == NULL)
			{
				bFound = true;
				Slot = ItemSlot;
				break;
			}
		}
	}

	SlotFound = (bFound) ? Slot : DefaulSlot;
}

bool URPGInventoryFunctionLibrary::HasPartialStack(const TArray<FRPGItemData> DataArray, FRPGItemData ItemData, int32& SlotIndex)
{
	bool bFound = false;

	for (int32 Index = 0; Index < DataArray.Num(); Index++)
	{
		if (DataArray[Index].Description.Name.EqualTo(ItemData.Description.Name, ETextComparisonLevel::Type::Default) && DataArray[Index].Stacks.bStackable && ItemData.Stacks.bStackable)
		{
			SlotIndex = Index;
			return bFound = true;
		}
	}

	if (!bFound)
		SlotIndex = -1;

	return bFound = false;
}

bool URPGInventoryFunctionLibrary::HasSpaceInDataArray(TArray<FRPGItemData>& DataArray, int32& SlotIndex)
{
	bool bFound = false;

	for (int32 Index = 0; Index < DataArray.Num(); Index++)
	{
		if (!DataArray[Index].IsValid())
		{
			SlotIndex = Index;
			bFound = true;
			break;
		}
	}

	return (bFound) ? true : false;
}

bool URPGInventoryFunctionLibrary::CanItemBeRemoved(const FRPGItemData ItemData)
{
	return ItemData.Use.RemoveType != EItemRemoveType::CannotBeRemoved;
}

void URPGInventoryFunctionLibrary::FindItemIndex(const TArray<FRPGItemData> DataArray, const FRPGItemData SecondItem, bool& bFound, int32& SlotIndex)
{
	for (int32 Index = 0; Index < DataArray.Num(); Index++)
	{
		if (DataArray[Index] == SecondItem)
		{
			bFound = true;
			SlotIndex = Index;
			return;
		}
	}

	bFound = false;
}

void URPGInventoryFunctionLibrary::FindItemByID(const TArray<FRPGItemData> DataArray, const FString ItemID, bool& bFound, FRPGItemData& ItemFound)
{
	for (int32 Index = 0; Index < DataArray.Num(); Index++)
	{
		if (DataArray[Index].Description.ID == ItemID)
		{
			bFound = true;
			ItemFound = DataArray[Index];
			return;
		}
	}

	bFound = false;
}

void URPGInventoryFunctionLibrary::FindItemStat(const TArray<FRPGStatRow> DataArray, const EStatCategory Stat, bool& bFound , int32& StatIndex)
{
	for (int32 Index = 0; Index < DataArray.Num(); Index++)
	{
		if (Stat == DataArray[Index].Stat)
		{
			bFound = true;
			StatIndex = Index;
			return;
		}
	}

	bFound = false;
}

bool URPGInventoryFunctionLibrary::AreItemsStackable(const FRPGItemData FirstItem, const FRPGItemData SecondItem)
{
	if (FirstItem.IsStackable() && SecondItem.IsStackable())
		return true;

	return false;
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
	IRPGPlayerCharacterInterface* PlayerCharacterInterface = Cast<IRPGPlayerCharacterInterface>(URPGInventoryFunctionLibrary::GetPlayerReference());

	URPGInventoryComponent* InventoryComponent = PlayerCharacterInterface->GetInventoryComponent();

	if (InventoryComponent)
		return InventoryComponent;

	return nullptr;
}

URPGEquipmentComponent* URPGInventoryFunctionLibrary::GetEquipmentComponent()
{
	IRPGPlayerCharacterInterface* PlayerCharacterInterface = Cast<IRPGPlayerCharacterInterface>(URPGInventoryFunctionLibrary::GetPlayerReference());

	URPGEquipmentComponent* EquipmentComponent = PlayerCharacterInterface->GetEquipmentComponent();

	if (EquipmentComponent)
		return EquipmentComponent;

	return nullptr;
}

URPGLevelingComponent* URPGInventoryFunctionLibrary::GetLevelingComponent()
{
	IRPGPlayerCharacterInterface* PlayerCharacterInterface = Cast<IRPGPlayerCharacterInterface>(URPGInventoryFunctionLibrary::GetPlayerReference());

	URPGLevelingComponent* LevelingComponent = PlayerCharacterInterface->GetLevelingComponent();

	if (LevelingComponent)
		return LevelingComponent;

	return nullptr;
}

URPGAttributeComponent* URPGInventoryFunctionLibrary::GetAttributeComponent()
{
	IRPGPlayerCharacterInterface* PlayerCharacterInterface = Cast<IRPGPlayerCharacterInterface>(URPGInventoryFunctionLibrary::GetPlayerReference());

	URPGAttributeComponent* LevelingComponent = PlayerCharacterInterface->GetAttributeComponent();

	if (LevelingComponent)
		return LevelingComponent;

	return nullptr;
}

URPGCraftingComponent* URPGInventoryFunctionLibrary::GetCraftingComponent()
{
	IRPGPlayerCharacterInterface* PlayerCharacterInterface = Cast<IRPGPlayerCharacterInterface>(URPGInventoryFunctionLibrary::GetPlayerReference());

	URPGCraftingComponent* CraftingComponent = PlayerCharacterInterface->GetCraftingComponent();

	if (CraftingComponent)
		return CraftingComponent;

	return nullptr;
}

bool URPGInventoryFunctionLibrary::IsItemValid(const FRPGItemData ItemData)
{
	return ItemData.IsValid();
}

//
//void URPGInventoryFunctionLibrary::ItemData_Array_Set(TArray<FRPGItemData>& TargetArray, int32 Index, const FRPGItemData Item /*= FRPGItemData()*/, bool bSizeToFit /*= false*/)
//{
//	if (!TargetArray.IsValidIndex(Index) && bSizeToFit && (Index >= 0))
//		(&TargetArray)->SetNum(Index + 1);
//
//	if (TargetArray.IsValidIndex(Index))
//		TargetArray[Index] = Item;
//}

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

bool URPGInventoryFunctionLibrary::LevelingMap_Map_Find(const TMap<int32, float>& TargetMap, const int32& Key, float& Value)
{
	if (const float* CurrentValue = TargetMap.Find(Key))
	{
		Value = *CurrentValue;
		return true;
	}

	return false;
}

bool URPGInventoryFunctionLibrary::EquipmentData_Map_Find(const TMultiMap<FRPGItemSlot, FRPGItemData>& TargetMap, const FRPGItemSlot& Key, FRPGItemData& Value)
{
	if (const FRPGItemData* CurrentValue = TargetMap.Find(Key))
	{
		Value = *CurrentValue;
		return true;
	}
	return false;
}
