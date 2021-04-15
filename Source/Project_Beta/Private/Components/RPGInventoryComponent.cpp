// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/RPGInventoryComponent.h"
#include "Components/RPGInteractableComponent.h"
#include "Widgets/VendorAndStorage/RPGVendorWidget.h"
#include "Widgets/Inventory/RPGGoldWeightBarWidget.h"
#include "Widgets/Inventory/RPGInventoryBaseWidget.h"
#include "Kismet/KismetMathLibrary.h"
#include "Libraries/RPGInventoryFunctionLibrary.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Captures/RPGItemCaptureBase.h"

TArray<FRPGItemData>* URPGInventoryComponent::SelectCorrectInventory(const FRPGItemData ItemData)
{
	if (ItemData.Type == EItemType::None || ItemData.Type == EItemType::Currency || ItemData.Type == EItemType::Max) return nullptr;

	return GetInventoryByType(ItemData.Type);
}

TArray<FRPGItemData>* URPGInventoryComponent::SelectCorrectInventory(const EItemType Type)
{
	if (Type == EItemType::None || Type == EItemType::Currency || Type == EItemType::Max) return nullptr;

	return GetInventoryByType(Type);
}

void URPGInventoryComponent::AssignItemsToCorrectInventory(const EItemType Type, TArray<FRPGItemData> ItemsArray)
{
	TArray<FRPGItemData>* InventoryPtr = GetInventoryByType(Type);

	(*InventoryPtr).Empty();

	InventoryPtr->Append(ItemsArray);
}

TArray<FRPGItemData>* URPGInventoryComponent::GetInventoryByType(const EItemType Type)
{
	if (Type == EItemType::None) return nullptr;

	FRPGInventoryPanelData* InventoryPanelData = InventoryData.Find(Type);
	return &InventoryPanelData->ArrayData;
}

void URPGInventoryComponent::SortEveryPanel(const ESortMethod Selection)
{
	for (int32 Index = (int32)EItemType::None; Index < (int32)EItemType::Max; Index++)
	{
		const EItemType Type = static_cast<EItemType>(Index);

		switch (Selection)
		{
		case ESortMethod::QuickSort:
			QuickSort(Type);
			break;

		case ESortMethod::ByType:
			SortByType(Type);
			break;

		case ESortMethod::ByRarity:
			SortByRarity(Type);
			break;

		case ESortMethod::ByValue:
			SortByValue(Type);
			break;

		case ESortMethod::ByWeight:
			SortByWeight(Type);
			break;
		}
	}

	RefreshInventory();
}

void URPGInventoryComponent::SortActivePanel(const ESortMethod Selection)
{

}

void URPGInventoryComponent::AddItemToEmptySlotInInventory(TArray<FRPGItemData>* InventoryArray, const FRPGItemData ItemData, int32& AddedSlotIndex, bool& bInventoryFull)
{
	int32 SlotIndex = -1;
	const bool bHasSpaceInDataArray = URPGInventoryFunctionLibrary::HasSpaceInDataArray(*InventoryArray, SlotIndex);

	if (bHasSpaceInDataArray && SlotIndex >= 0)
	{
		AddedSlotIndex = SlotIndex;
		bInventoryFull = false;
		InventoryArray->Add(ItemData);
		RefreshInventory();
		return;
	}

	bInventoryFull = true;
	AddedSlotIndex = -1;
}

// Sets default values for this component's properties
URPGInventoryComponent::URPGInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void URPGInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	SetupInventoryData();
}

void URPGInventoryComponent::SetupInventoryData_Implementation()
{
	//FRPGInventoryPanelData InventoryPanelData;
	//InventoryPanelData.Size = InventoryMaxSize;

	//InventoryData.Add(EItemType::Weapon, InventoryPanelData);
	//InventoryData.Add(EItemType::Armor, InventoryPanelData);
	//InventoryData.Add(EItemType::Consumable, InventoryPanelData);
	//InventoryData.Add(EItemType::CraftingIngredient, InventoryPanelData);
	//InventoryData.Add(EItemType::QuestItem, InventoryPanelData);
}

void URPGInventoryComponent::SetupInitialInventory_Implementation()
{
	for (auto& ArrayElement : InitialInventory)
	{
		FRPGItemData ItemData = *ArrayElement.TableAndRow.DataTable->FindRow<FRPGItemData>(ArrayElement.TableAndRow.RowName, "", true);

		if (ItemData.IsValid())
		{
			bool bSuccess = false;
			ItemData.Stacks.Quantity = (ArrayElement.Quantity > 0) ? ArrayElement.Quantity : 1;
			AddItemToInventory(ItemData, bSuccess);
		}
	}
}

void URPGInventoryComponent::ToggleGamepadControls_Implementation(const bool bIsUsingGamepad)
{
	if (bIsUsingGamepad != bGamepadControls)
	{
		bGamepadControls = bIsUsingGamepad;
		OnGamepadToggled.Broadcast(bIsUsingGamepad);
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetMouseLocation(0, 0);
	}
}

void URPGInventoryComponent::TryToAddToInventory(const FRPGItemData ItemData, int32& AddedSlotIndex, bool& bInventoryFull)
{
	TArray<FRPGItemData>* SelectedInventoryPtr = SelectCorrectInventory(ItemData);
	TArray<FRPGItemData>& SelectedInventoryRef = *SelectedInventoryPtr;

	if (ItemData.Stacks.bStackable)
	{
		int32 SlotIndex = -1;
		const bool bHasPartialStack = URPGInventoryFunctionLibrary::HasPartialStack(SelectedInventoryRef, ItemData, SlotIndex);

		if (bHasPartialStack && SlotIndex >= 0)
		{
			AddStackToInventory(SlotIndex, SelectedInventoryPtr, ItemData);
			RefreshInventory();

			AddedSlotIndex = SlotIndex;
			bInventoryFull = false;
			return;
		}

		AddItemToEmptySlotInInventory(SelectedInventoryPtr, ItemData, AddedSlotIndex, bInventoryFull);
		return;
	}

	AddItemToEmptySlotInInventory(SelectedInventoryPtr, ItemData, AddedSlotIndex, bInventoryFull);
}

void URPGInventoryComponent::AddStackToInventory(const int32 SlotIndex, TArray<FRPGItemData>* InventoryArray, const FRPGItemData ItemData)
{
	(*InventoryArray)[SlotIndex].Stacks.Quantity += ItemData.Stacks.Quantity;
	(*InventoryArray)[SlotIndex].Stacks.bStackable = true;
}

void URPGInventoryComponent::RefreshInventory()
{

}

void URPGInventoryComponent::AddItemWeight(const FRPGItemData ItemData)
{
	CurrentInventoryWeight += (ItemData.Stacks.Quantity > 0) ? ItemData.Stacks.Quantity * ItemData.Stats.Weight : ItemData.Stats.Weight;
}

void URPGInventoryComponent::RemoveItemWeight(const FRPGItemData ItemData)
{
	const float WeightToRemove = CurrentInventoryWeight - (ItemData.Stacks.Quantity > 0) ? ItemData.Stacks.Quantity * ItemData.Stats.Weight : ItemData.Stats.Weight;

	CurrentInventoryWeight = (WeightToRemove < 0) ? 0.f : WeightToRemove;
}

TArray<FRPGItemData> URPGInventoryComponent::GetCombinedInventories() const
{
	TArray<FRPGItemData> LInventory;

	for (const TPair<EItemType, FRPGInventoryPanelData>& Pair : InventoryData)
		LInventory.Append(Pair.Value.ArrayData);

	return LInventory;
}

FRPGItemData URPGInventoryComponent::GetInventoryItemByID(const FString ID, const bool bSpecifiedType, const EItemType Type, bool& bFound)
{
	TArray<FRPGItemData> SelectInventory = (bSpecifiedType) ? *GetInventoryByType(Type) : GetCombinedInventories();

	FRPGItemData FoundItem;
	URPGInventoryFunctionLibrary::FindItemByID(SelectInventory, ID, bFound, FoundItem);

	if (!bFound) return FRPGItemData();

	return FoundItem;
}

FRPGItemData URPGInventoryComponent::GetInventoryItemByData(const FRPGItemData ItemData, bool& bFound)
{
	const TArray<FRPGItemData> SelectInventory = *SelectCorrectInventory(ItemData);

	int32 SlotIndex = -1;
	URPGInventoryFunctionLibrary::FindItemIndex(SelectInventory, ItemData, bFound, SlotIndex);

	if (!bFound && SlotIndex == -1) return FRPGItemData();

	return SelectInventory[SlotIndex];
}

bool URPGInventoryComponent::CheckInventorySpace(const EItemType Type)
{
	if (Type == EItemType::None) return false;

	int32 SlotIndex = -1;
	return URPGInventoryFunctionLibrary::HasSpaceInDataArray(*GetInventoryByType(Type), SlotIndex);
}

void URPGInventoryComponent::HighlightInventorySlot(const int32 SlotIndex)
{
	InventoryBase_Widget->HighlightSlot(SlotIndex);
}

void URPGInventoryComponent::ReplaceItemInInventory(const FRPGItemData ItemData)
{
	(*SelectCorrectInventory(ItemData))[ItemData.Index] = ItemData;

	RefreshInventory();
}

bool URPGInventoryComponent::IsInventoryOverweighted()
{
	return (CurrentInventoryWeight > MaxInventoryWeight) ? true : false;
}

void URPGInventoryComponent::CanBeAddedToSlotInInventory(const FRPGItemData ItemData, bool& bAdded)
{
	if (!ItemData.IsValid()) return;

	if (ItemData.Type == EItemType::Currency)
	{
		AddGoldToPlayerInventory((float)ItemData.Stacks.Quantity);
		bAdded = false;
		return;
	}

	bAdded = true;
}

void URPGInventoryComponent::AddItemToInventory(const FRPGItemData ItemData, bool& bSuccess)
{

}

bool URPGInventoryComponent::IsPlayerGoldEnough(const FRPGItemData ItemData) const
{
	const int32 QuanityMultiplier = (ItemData.Stacks.Quantity > 0) ? ItemData.Stacks.Quantity : 1;
	const float TotalValue = ItemData.Stats.Value * QuanityMultiplier;

	if (PlayerGold < TotalValue)
	{
		Vendor_Widget->GetGoldWeightBar_Widget()->PlayAnim();
		return false;
	}

	return true;
}

void URPGInventoryComponent::AddItemGold(const FRPGItemData ItemData)
{
	const int32 QuantityMultiplier = (ItemData.Stacks.Quantity > 0) ? ItemData.Stacks.Quantity : 1;
	const float GoldAmountToAdd = QuantityMultiplier * ItemData.Stats.Value;

	AddGoldToPlayerInventory(GoldAmountToAdd);

	if (CurrentInteractableComponent)
		CurrentInteractableComponent->SetVendorGold(CurrentInteractableComponent->GetVendorGold() - GoldAmountToAdd);
}

void URPGInventoryComponent::RemoveItemGold(const FRPGItemData ItemData)
{
	const int32 QuantityMultiplier = (ItemData.Stacks.Quantity > 0) ? ItemData.Stacks.Quantity : 1;
	const float GoldAmountToRemove = QuantityMultiplier * ItemData.Stats.Value;

	RemoveGoldFromPlayerInventory(GoldAmountToRemove);

	if (CurrentInteractableComponent)
		CurrentInteractableComponent->SetVendorGold(CurrentInteractableComponent->GetVendorGold() + GoldAmountToRemove);
}

void URPGInventoryComponent::AddGoldToPlayerInventory(const float Amount /*= 0.f*/)
{
	PlayerGold += Amount;
}

void URPGInventoryComponent::RemoveGoldFromPlayerInventory(const float Amount /*= 0.f*/)
{
	PlayerGold = UKismetMathLibrary::Clamp(PlayerGold - Amount, 0.f, PlayerGold);
}

void URPGInventoryComponent::SortByType(const EItemType Type)
{
	if (Type == EItemType::None) return;

	AssignItemsToCorrectInventory(Type, URPGInventoryFunctionLibrary::SortItemsByType(*GetInventoryByType(Type)));
}

void URPGInventoryComponent::SortItemsInInventory(const bool bEveryPanel, const ESortMethod Method)
{
	UWidgetBlueprintLibrary::CancelDragDrop();

	(bEveryPanel) ? SortEveryPanel(Method) : SortActivePanel(Method) ;
}

void URPGInventoryComponent::SortByRarity(const EItemType Type)
{
	if (Type == EItemType::None) return;

	AssignItemsToCorrectInventory(Type, URPGInventoryFunctionLibrary::SortItemsByRarity(*GetInventoryByType(Type)));
}

void URPGInventoryComponent::SortByValue(const EItemType Type)
{
	if (Type == EItemType::None) return;

	AssignItemsToCorrectInventory(Type, URPGInventoryFunctionLibrary::SortItemByValue(*GetInventoryByType(Type)));
}

void URPGInventoryComponent::SortByWeight(const EItemType Type)
{
	if (Type == EItemType::None) return;

	AssignItemsToCorrectInventory(Type, URPGInventoryFunctionLibrary::SortItemByWeight(*GetInventoryByType(Type)));
}

void URPGInventoryComponent::QuickSort(const EItemType Type)
{
	if (Type == EItemType::None) return;

	//AssignItemsToCorrectInventory(Type, URPGInventoryFunctionLibrary::QuickSortItems(*GetInventoryByType(Type)));
}

void URPGInventoryComponent::AssignCurrentWidgetInput(const EInputMethod InputMethod, const EWidgetType WidgetType)
{
	CurrentInputMethod = InputMethod;
	CurrentWidgetInput = WidgetType;
}

void URPGInventoryComponent::GetCurrentWidgetInput(EInputMethod& InputMethod, EWidgetType& WidgetType)
{
	InputMethod = CurrentInputMethod;
	WidgetType = CurrentWidgetInput;
}

void URPGInventoryComponent::ResetCaptureRotation()
{
	FRotator RelativeRotation = ItemCaptureRef->GetSkeletalMeshComponent()->GetRelativeRotation();

	ItemCaptureRef->GetSkeletalMeshComponent()->SetRelativeRotation(FRotator(RelativeRotation.Roll, RelativeRotation.Yaw, 0));
}

void URPGInventoryComponent::PassItemCaptureReference(ARPGItemCaptureBase* InItemCaptureRef)
{
	ItemCaptureRef = InItemCaptureRef;
}

FSlateColor URPGInventoryComponent::SetRarityColor(const EItemRarity Rarity) const
{
	return FSlateColor();
}

