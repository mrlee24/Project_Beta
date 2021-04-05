// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/RPGInventoryComponent.h"
#include "Widgets/VendorAndStorage/RPGVendorWidget.h"
#include "Widgets/Inventory/RPGGoldWeightBarWidget.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
URPGInventoryComponent::URPGInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
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

void URPGInventoryComponent::AddGoldToPlayerInventory(const float Amount /*= 0.f*/)
{
	PlayerGold += Amount;
}

void URPGInventoryComponent::RemoveGoldFromPlayerInventory(const float Amount /*= 0.f*/)
{
	PlayerGold = UKismetMathLibrary::Clamp(PlayerGold - Amount, 0.f, PlayerGold);
}

// Called when the game starts
void URPGInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


