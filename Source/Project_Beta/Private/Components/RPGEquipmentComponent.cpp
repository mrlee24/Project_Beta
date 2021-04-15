// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/RPGEquipmentComponent.h"
#include "Components/RPGInventoryComponent.h"
#include "Components/RPGAttributeComponent.h"
#include "Components/RPGLevelingComponent.h"
#include "Widgets/Equipment/RPGEquipmentWidget.h"
#include "Libraries/RPGInventoryFunctionLibrary.h"
#include "Captures/RPGItemCaptureBase.h"

void URPGEquipmentComponent::Init()
{
	InventoryComponent = URPGInventoryFunctionLibrary::GetInventoryComponent();
	AttributeComponent = URPGInventoryFunctionLibrary::GetAttributeComponent();
}

// Sets default values for this component's properties
URPGEquipmentComponent::URPGEquipmentComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void URPGEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();
}

bool URPGEquipmentComponent::TryToAddToPartialStackInEquipment(const FRPGItemData ItemData)
{
	TArray<FRPGItemData> MapValues;
	EquipmentData.GenerateValueArray(MapValues);

	int32 SlotIndex = 0;

	if (URPGInventoryFunctionLibrary::HasPartialStack(MapValues, ItemData, SlotIndex))
	{
		AddStackedToEquipment(SlotIndex, ItemData);
		return true;
	}

	return false;
}

void URPGEquipmentComponent::AddStackedToEquipment(const int32 Index, const FRPGItemData ItemData)
{
	TArray<FRPGItemData> MapValues;
	EquipmentData.GenerateValueArray(MapValues);

	FRPGItemData* ItemPtr = &MapValues[Index];
	ItemPtr->Stacks.bStackable = true;
	ItemPtr->Stacks.Quantity += ItemData.Stacks.Quantity;

	AddItemToEquipmentDataArray(*ItemPtr);
	RefreshEquipment();
}

void URPGEquipmentComponent::RefreshEquipment()
{
	if (Equipment_Widget)
	{
		Equipment_Widget->CreateEquipment();
		OnEquipmentRefreshed.Broadcast();
	}
}

void URPGEquipmentComponent::RemoveFromEquipmentDataArray(const FRPGItemData ItemData)
{
	if (EquipmentData.Contains(ItemData.Slot))
	{
		EquipmentData.Remove(ItemData.Slot);
		EquipmentData.Add(ItemData.Slot, FRPGItemData());
	}
}

void URPGEquipmentComponent::AddItemToEquipmentDataArray(FRPGItemData ItemData)
{
	ItemData.bEquipped = true;

	if (EquipmentData.Contains(ItemData.Slot))
		EquipmentData.Add(ItemData.Slot, ItemData);
}

void URPGEquipmentComponent::ReturnQuantityToEquipment(const FRPGItemData RestStackableData)
{
	if (RestStackableData.Stacks.bStackable && RestStackableData.Stacks.Quantity > 0)
	{
		AddItemToEquipmentDataArray(RestStackableData);
		RefreshEquipment();
	}
}

FRPGItemData URPGEquipmentComponent::GetEquipmentItemByID(const FString ID, bool& bFound)
{
	TArray<FRPGItemData> MapValues;
	EquipmentData.GenerateValueArray(MapValues);

	FRPGItemData ItemRef;
	URPGInventoryFunctionLibrary::FindItemByID(MapValues, ID, bFound, ItemRef);

	return ItemRef;
}

void URPGEquipmentComponent::RemoveQuantityFromEquipment(FRPGItemData* ItemData, const int32 Quantity)
{
	if (ItemData->Stacks.Quantity > Quantity)
	{
		InventoryComponent->RemoveItemWeight(*ItemData);
		ItemData->Stacks.bStackable = true;
		ItemData->Stacks.Quantity -= Quantity;

		AddItemToEquipmentDataArray(*ItemData);
		InventoryComponent->AddItemWeight(*ItemData);
		RefreshEquipment();
	}

	if (ItemData->Stacks.Quantity == Quantity)
	{
		InventoryComponent->RemoveItemWeight(*ItemData);
		//RemoveItemFromEquipment(ItemData);
	}
}

URPGEquipmentSlotWidget* URPGEquipmentComponent::GetEquipmentSlot(const FRPGItemSlot Slot)
{
	if (!Equipment_Widget) return nullptr;

	return Equipment_Widget->GetWidgetSlotByItemSlot(Slot);
}

bool URPGEquipmentComponent::CanItemBeEquipped(const FRPGItemData ItemToEquip) const
{
	if (ItemToEquip.Type != EItemType::None && ItemToEquip.Type != EItemType::Max)
	{
		if ((ItemToEquip.Slot.ItemType != EItemType::None && ItemToEquip.Slot.ItemType != EItemType::Max) && ItemToEquip.Slot.SlotNumber > -1)
		{
			if (InventoryComponent->GetCheckRequiredItemLevel() ? ItemToEquip.Stats.RequiredLevel <= LevelingComponent->GetCurrentLevel() : false)
				return true;
		}
	}

	return false;
}

FRPGItemData URPGEquipmentComponent::GetEquipmentItemBySlot(const FRPGItemSlot Slot, bool& bIsValid) const
{
	FRPGItemData ItemData = *EquipmentData.Find(Slot);

	if (!ItemData.IsValid())
	{
		bIsValid = false;
		return FRPGItemData();
	}

	bIsValid = true;
	return ItemData;
}

void URPGEquipmentComponent::ResetCaptureRotation()
{
	FRotator RelativeRotation = ItemCaptureRef->GetSkeletalMeshComponent()->GetRelativeRotation();

	ItemCaptureRef->GetSkeletalMeshComponent()->SetRelativeRotation(FRotator(RelativeRotation.Roll, RelativeRotation.Yaw, 0));
}

void URPGEquipmentComponent::PassItemCaptureReference(ARPGItemCaptureBase* InItemCaptureRef)
{
	ItemCaptureRef = InItemCaptureRef;
}

