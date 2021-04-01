// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/RPGInteractableComponent.h"
#include "Components/RPGInventoryComponent.h"
#include "Components/RPGInteractionComponent.h"
#include "Components/SlateWrapperTypes.h"
//#include "Widgets/Inventory/RPGInventoryOverallWidget.h"
//#include "Widgets/Inventory/RPGReadableWindowWidget.h"
//#include "Widgets/Inventory/RPGSplitStackWidget.h"
//#include "Widgets/Inventory/RPGConfirmationMenuWidget.h"
//#include "Widgets/Equipment/RPGEquipmentWidget.h"
//#include "Widgets/ItemsBar/RPGItemsBarWidget.h"
//#include "Widgets/VendorAndStorage/RPGVendorWidget.h"
//#include "Widgets/VendorAndStorage/RPGVendorStorageInventoryWidget.h"
//#include "Widgets/VendorAndStorage/RPGStorageWidget.h"
//#include "Widgets/SaveSystem/RPGLoadGameWindowWidget.h"
#include "Widgets/Interaction/RPGInteractionWidget.h"
#include "Interfaces/RPGPlayerCharacterInterface.h"
#include "Libraries/RPGInventoryFunctionLibrary.h"
#include "Kismet/KismetMathLibrary.h" 	
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TimerManager.h" 	
#include "Engine/World.h"

// Sets default values for this component's properties
URPGInteractableComponent::URPGInteractableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void URPGInteractableComponent::BeginPlay()
{
	Super::BeginPlay();

	InventoryComponent = URPGInventoryFunctionLibrary::GetInventoryComponent();
	Initialize();
	SetupData();
	AActor* OwnerActor = GetOwner();
	OwnerActor->Tags.AddUnique(InteractableTag);

	if (bDestroyAfterPickup)
		GetOwner()->Tags.AddUnique(DestroyableTag);

	if (InteractionWidgetComponent)
	{
		Interaction_Widget = CreateWidget<URPGInteractionWidget>(GetWorld(), InteractionWidgetComponent->GetWidgetClass());

		if (Interaction_Widget)
		{
			Interaction_Widget->Init(DefaultInteractionText, InputType);
			InteractionWidgetComponent->SetWidget(Interaction_Widget);
		}
	}

	InteractableArea->OnComponentBeginOverlap.AddDynamic(this, &URPGInteractableComponent::OnComponentBeginOverlap);
	InteractableArea->OnComponentEndOverlap.AddDynamic(this, &URPGInteractableComponent::OnComponentEndOverlap);
}

void URPGInteractableComponent::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != GetOwner() && OtherActor->ActorHasTag("Player"))
	{
		IRPGPlayerCharacterInterface* PlayerInterfaceRef = Cast<IRPGPlayerCharacterInterface>(OtherActor);

		/*
			*** Avoiding Begin & End are toggled at the same time ***
		*/
		GetWorld()->GetTimerManager().SetTimer
		(
			ToggleTimerHandle,
			[&]()
			{ PlayerInterfaceRef->GetInteractionComponent()->ToggleInteractionTimer(true); },
			0.1f,
			false
		);
	}
}

void URPGInteractableComponent::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor != GetOwner() && OtherActor->ActorHasTag("Player"))
	{
		IRPGPlayerCharacterInterface* PlayerInterfaceRef = Cast<IRPGPlayerCharacterInterface>(OtherActor);
		PlayerInterfaceRef->GetInteractionComponent()->ToggleInteractionTimer(false);
	}
}

void URPGInteractableComponent::ToggleIsInteractable(bool bCondition)
{
	if (bCondition != GetIsInteractable())
		SetIsInteractable(bCondition);
}

void URPGInteractableComponent::FillInteractionWidgetBorder(float InValue)
{
	if (Interaction_Widget)
	{
		float Value = UKismetMathLibrary::MapRangeClamped(InValue, 0.f, MaxKeyTimeDown, 0.f, 1.f);
		Interaction_Widget->BorderFill(Value);
	}
}

void URPGInteractableComponent::ToggleInteractionWidget(bool bCondition)
{
	const ESlateVisibility ReturnValue = (bCondition) ? ESlateVisibility::Visible : ESlateVisibility::Hidden;

	if (GetIsInteractable() && Interaction_Widget)
	{
		Interaction_Widget->SetVisibility(ReturnValue);
		Interaction_Widget->SetFillDecimalValue(0.05f);
	}
}

void URPGInteractableComponent::RemoveInteractionByResponse()
{
	if (InteractableResponse == EInteractionResponse::OnlyOnce || InteractableResponse == EInteractionResponse::Temporary)
		RemoveInteraction();
}

void URPGInteractableComponent::ChangeInteractableValue(bool bIncrement)
{
	if (bIncrement)
	{
		InteractableValue++;

		if (InteractableValue > InteractableLimitValue)
			InteractableValue = 0;
		return;
	}

	InteractableValue--;

	if (InteractableValue < 0)
		InteractableValue = InteractableLimitValue;
}

void URPGInteractableComponent::ToggleCanBeReInitialized(bool bCondition)
{
	if (bCondition)
	{
		if (bCondition != bCanBeReInitialized)
			bCanBeReInitialized = bCondition;
	}
}

void URPGInteractableComponent::SetupData()
{
	if (bRandomizeItemsData)
		RandomizeItems();

	for (auto& ArrayElement : AllItemsFromDT)
	{
		if (ArrayElement)
		{
			TArray<FName> OutRowNames = ArrayElement->GetRowNames();

			for (auto& RowArrayElement : OutRowNames)
			{
				FRPGItemData OutRow = *ArrayElement->FindRow<FRPGItemData>(RowArrayElement, "");

				ItemData.Add(OutRow);
			}
		}
	}

	for (auto& ArrayElement : SingleDTItem)
	{
		FRPGItemData OutRow = *ArrayElement.TableAndRow.DataTable->FindRow<FRPGItemData>(ArrayElement.TableAndRow.RowName, "");

		if (ArrayElement.Quantity == 0)
			ItemData.Add(OutRow);
		else
		{
			OutRow.Stacks.Quantity = ArrayElement.Quantity;
			ItemData.Add(OutRow);
		}
	}

	AllItemsFromDT.Empty();
	SingleDTItem.Empty();
	RandomizedItemsData = FRPGRandomizedLootTable();
	SortItems();

	if (bReverseSorting)
		ReverseItemDataArray();
}

void URPGInteractableComponent::SortItems()
{
	switch (SortingMethod)
	{
	case ESortMethod::QuickSort:
		ItemData = URPGInventoryFunctionLibrary::QuickSortItems(ItemData);
		break;

	case ESortMethod::ByType:
		ItemData = URPGInventoryFunctionLibrary::SortItemsByType(ItemData);
		break;

	case ESortMethod::ByRarity:
		ItemData = URPGInventoryFunctionLibrary::SortItemsByRarity(ItemData);
		break;

	case ESortMethod::ByValue:
		ItemData = URPGInventoryFunctionLibrary::SortItemByValue(ItemData);
		break;

	case ESortMethod::ByWeight:
		ItemData = URPGInventoryFunctionLibrary::SortItemByWeight(ItemData);
		break;
	}
}

void URPGInteractableComponent::RandomizeItems()
{
	FRPGItemData LItemData;
	EItemType LItemType;
	TArray<FRPGItemData> LNotDrawItems;
	TMap<EItemType, int32> LCurrentTypesAmount;
	int32 LCurrentMaxLootItems = 0;

	for (auto& DTArrayElement : RandomizedItemsData.DataTables)
	{
		if (DTArrayElement)
		{
			TArray<FName> OutRowNames = DTArrayElement->GetRowNames();

			for (auto& RowNameArrayElement : OutRowNames)
			{
				LItemData = *DTArrayElement->FindRow<FRPGItemData>(RowNameArrayElement, "");
				LItemType = LItemData.Type;

				if (LItemData.LootRandomizer.DropPercentage >= UKismetMathLibrary::RandomIntegerInRange(0, 100))
				{
					int32 Temp = 0;
					URPGInventoryFunctionLibrary::ItemType_Map_Find(LCurrentTypesAmount, LItemType, Temp) ? LCurrentTypesAmount.Add(LItemType, Temp + 1) : LCurrentTypesAmount.Add(LItemType, 1);

					if (URPGInventoryFunctionLibrary::ItemType_Map_Find(RandomizedItemsData.MaxSameTypesAmount, LItemType, Temp))
					{
						if (*RandomizedItemsData.MaxSameTypesAmount.Find(LItemType) <= Temp)
						{
							if (RandomizedItemsData.MaxLootItems > 0)
							{
								LCurrentMaxLootItems++;

								if (!(LCurrentMaxLootItems > RandomizedItemsData.MaxLootItems))
								{
									AssignRandomValue(LItemData);
									ItemData.Add(LItemData);
								}
							}
						}
					}
					else
					{
						if (RandomizedItemsData.MaxLootItems > 0)
						{
							LCurrentMaxLootItems++;

							if (!(LCurrentMaxLootItems > RandomizedItemsData.MaxLootItems))
							{
								AssignRandomValue(LItemData);
								ItemData.Add(LItemData);
							}
						}
					}
				}
				else
					LNotDrawItems.Add(LItemData);
			}
		}
	}

	if ((RandomizedItemsData.MaxLootItems <= 0) || (RandomizedItemsData.MaxLootItems > LCurrentMaxLootItems))
	{
		TArray<EItemType> LItemTypes;
		RandomizedItemsData.MinSameTypesAmount.GetKeys(LItemTypes);

		for (auto& ItemType : LItemTypes)
		{
			LItemType = ItemType;
			int32 LCurrentAmount = 0;
			bool bIsFound = URPGInventoryFunctionLibrary::ItemType_Map_Find(LCurrentTypesAmount, LItemType, LCurrentAmount);

			int32 MinSameTypeAmount = *RandomizedItemsData.MinSameTypesAmount.Find(LItemType);

			int32 AmountToAdd = bIsFound ? (MinSameTypeAmount - LCurrentAmount) : MinSameTypeAmount;

			if (bIsFound)
			{
				if (MinSameTypeAmount > LCurrentAmount)
					ChooseItemsToAdd(URPGInventoryFunctionLibrary::GetAllItemsOfType(LNotDrawItems, LItemType), AmountToAdd);
			}
			else
				ChooseItemsToAdd(URPGInventoryFunctionLibrary::GetAllItemsOfType(LNotDrawItems, LItemType), AmountToAdd);
		}
	}
}

void URPGInteractableComponent::ChooseItemsToAdd(TArray<FRPGItemData> InItemArray, int32 InAmount)
{
	TMap<int32, FRPGItemData> LItemsMap;
	int32 LPercentMax = 0;
	int32 LRand = 0;
	TArray<FRPGItemData> LItemsArray;
	TArray<FRPGItemData> LSeparatedItems;

	for (auto& ArrayElement : InItemArray)
	{
		LPercentMax += ArrayElement.LootRandomizer.DropPercentage;
		LItemsMap.Add(LPercentMax, ArrayElement);
	}

	for (int32 FirstIndex = 1; FirstIndex <= InAmount; FirstIndex++)
	{
		LRand = UKismetMathLibrary::RandomIntegerInRange(0, LPercentMax);
		TArray<int32> IntArray;
		LItemsMap.GetKeys(IntArray);
		for (auto& ArrayElement : IntArray)
		{
			FRPGItemData LItem;
			URPGInventoryFunctionLibrary::ItemMap_Map_Find(LItemsMap, ArrayElement, LItem);
			int32 DropPercentage = LItem.LootRandomizer.DropPercentage;
			if (UKismetMathLibrary::InRange_IntInt(LRand, ArrayElement - DropPercentage, ArrayElement))
			{
				AssignRandomValue(LItem);
				ItemData.Add(LItem);

				LItemsMap.Remove(ArrayElement);
				break;
			}
		}
	}

	LPercentMax = 0;
	LItemsMap.GenerateValueArray(LItemsArray);
	LItemsMap.Empty();

	for (auto& ArrayElement : LItemsArray)
	{
		LPercentMax += ArrayElement.LootRandomizer.DropPercentage;
		LItemsMap.Add(LPercentMax, ArrayElement);
	}
}

void URPGInteractableComponent::AssignRandomValue(FRPGItemData& LItemToAssign)
{
	int32 RandomizationLevel = UKismetMathLibrary::RandomIntegerInRange(1, 10);

	AssignRandomItemStats(LItemToAssign, RandomizationLevel);

	LItemToAssign.Stats.Value = GetRandomizedItemValue(LItemToAssign, RandomizationLevel);
	LItemToAssign.Stats.Level = GetRandomizedLevel(LItemToAssign, RandomizationLevel);
	LItemToAssign.Stats.Durability = GetRandomizedItemDurability(LItemToAssign);

	LItemToAssign.Stacks = GetRandomizedItemQuantity(LItemToAssign);
}

void URPGInteractableComponent::AssignRandomItemStats(FRPGItemData& LItemToAssign, const int32 InRandomizationLevel)
{
	FRPGStatRow LEmptyStat;
	TArray<FRPGStatRow> LRandomizedStats;
	FRPGItemData LItemData;

	if (LItemToAssign.LootRandomizer.RandomStats.IsValidIndex(0))
	{
		for (FRPGItemRandomStats& ArrayElement : LItemToAssign.LootRandomizer.RandomStats)
		{
			int32 MinValue = ArrayElement.ValueAndMultiplier.MinValue;
			int32 MaxValue = ArrayElement.ValueAndMultiplier.MaxValue;
			int32 MultipliedValue = GetMultipliedValueFromDataTable(ArrayElement.ValueAndMultiplier.MultiplierDataTable, FName(*FString::FromInt(InRandomizationLevel)));

			int32 ResultValue = (ArrayElement.bRountToInt) ? UKismetMathLibrary::Clamp(MinValue * MultipliedValue, MinValue, MaxValue) : UKismetMathLibrary::Round(UKismetMathLibrary::Clamp(MinValue * MultipliedValue, MinValue, MaxValue));

			LEmptyStat.Value = ResultValue;
			LEmptyStat.Stat = ArrayElement.Stat;

			LRandomizedStats.Add(LEmptyStat);
		}

		LItemToAssign.Stats.Stats = LRandomizedStats;
	}
}

void URPGInteractableComponent::ReverseItemDataArray()
{
	TArray<FRPGItemData> LItemData = ItemData;
	ItemData.Empty();

	for (int32 Index = LItemData.Num() - 1; Index >= 0; Index--)
		ItemData.Add(LItemData[Index]);
}

float URPGInteractableComponent::GetMultipliedValueFromDataTable(UDataTable* DataTable, FName RowName) const
{
	if (DataTable)
	{
		FRPGMultiplier* OutRow = DataTable->FindRow<FRPGMultiplier>(RowName, "");

		if (OutRow)
			return OutRow->MultiplyValue;
	}

	return 0.f;
}

int32 URPGInteractableComponent::GetRandomizedLevel(FRPGItemData Item, int32 RandomizationLevel) const
{
	if (Item.LootRandomizer.RandomLevel.MinValue > 0)
	{
		return UKismetMathLibrary::Clamp
		(
			UKismetMathLibrary::Round
			(
				Item.LootRandomizer.RandomLevel.MinValue *
				GetMultipliedValueFromDataTable
				(
					Item.LootRandomizer.RandomLevel.MultiplierDataTable,
					FName(*FString::FromInt(RandomizationLevel))
				)
			),
			Item.LootRandomizer.RandomLevel.MinValue,
			Item.LootRandomizer.RandomLevel.MaxValue
		);
	}

	return 0;
}

FRPGItemDurability URPGInteractableComponent::GetRandomizedItemDurability(FRPGItemData InItem) const
{
	bool bUseDurability = InItem.Stats.Durability.bUseDurability;

	int32 CurrentDurability = UKismetMathLibrary::RandomIntegerInRange(InItem.LootRandomizer.MinDurability, InItem.LootRandomizer.MaxDurability);

	FRPGItemDurability ItemDurability;
	ItemDurability.bUseDurability = bUseDurability;
	ItemDurability.CurrentDurability = CurrentDurability;
	return ItemDurability;
}

float URPGInteractableComponent::GetRandomizedItemValue(FRPGItemData InItem, int32 RandomizationLevel) const
{
	if (InItem.LootRandomizer.RandomValue.MinValue > 0)
	{
		return UKismetMathLibrary::Clamp
		(
			UKismetMathLibrary::Round
			(
				InItem.LootRandomizer.RandomValue.MinValue *
				GetMultipliedValueFromDataTable
				(
					InItem.LootRandomizer.RandomLevel.MultiplierDataTable,
					FName(*FString::FromInt(RandomizationLevel))
				)
			),
			InItem.LootRandomizer.RandomValue.MinValue,
			InItem.LootRandomizer.RandomValue.MaxValue
		);
	}

	return InItem.Stats.Value;
}

FRPGItemStack URPGInteractableComponent::GetRandomizedItemQuantity(FRPGItemData InItem) const
{
	FRPGItemStack ItemStack;
	ItemStack.bStackable = InItem.Stacks.bStackable;
	int32 RandInt = UKismetMathLibrary::RandomIntegerInRange(InItem.LootRandomizer.MinQuantity, InItem.LootRandomizer.MaxQuantity);
	ItemStack.Quantity = (RandInt > 0) ? RandInt : 1;

	return ItemStack;
}

void URPGInteractableComponent::Interaction_Implementation()
{
	bAlreadyInteracted = true;
	AActor* OwnerActor = GetOwner();
	IRPGInteractableInterface* OwnerInterface = Cast<IRPGInteractableInterface>(OwnerActor);
	OwnerInterface->Execute_OnInteraction(OwnerActor);
	RemoveInteractionByResponse();
}

void URPGInteractableComponent::AssociatedActorInteraction_Implementation()
{
	for (auto& AssociatedInteractableActor : AssociatedInteractableActors)
	{
		URPGInteractableComponent* InteractableComponent = AssociatedInteractableActor->FindComponentByClass<URPGInteractableComponent>();
		if (AssociatedInteractableActor && InteractableComponent)
			InteractableComponent->CheckForInteractionWithAssociate();
	}
}

void URPGInteractableComponent::CheckForInteractionWithAssociate_Implementation()
{
	if (bRemoveAssociatedInteractablesOnComplete)
	{
		for (auto& AssociatedInteractableActor : AssociatedInteractableActors)
		{
			URPGInteractableComponent* InteractableComponent = AssociatedInteractableActor->FindComponentByClass<URPGInteractableComponent>();
			InteractableComponent->RemoveInteraction();
			InteractableComponent->InteractableResponse = EInteractionResponse::OnlyOnce;
		}

		return;
	}

	switch (InteractableResponse)
	{
	case EInteractionResponse::OnlyOnce:
		for (auto& AssociatedInteractableActor : AssociatedInteractableActors)
		{
			URPGInteractableComponent* InteractableComponent = AssociatedInteractableActor->FindComponentByClass<URPGInteractableComponent>();
			InteractableComponent->RemoveInteraction();
			InteractableComponent->InteractableResponse = EInteractionResponse::OnlyOnce;
		}
		break;

	case EInteractionResponse::Temporary:
		for (auto& AssociatedInteractableActor : AssociatedInteractableActors)
		{
			URPGInteractableComponent* InteractableComponent = AssociatedInteractableActor->FindComponentByClass<URPGInteractableComponent>();
			InteractableComponent->RemoveInteraction();
			InteractableComponent->ToggleCanBeReInitialized(false);
		}
		break;
	}
}

void URPGInteractableComponent::Initialize_Implementation()
{
	AActor* OwnerActor = GetOwner();
	IRPGInteractableInterface* OwnerInterface = Cast<IRPGInteractableInterface>(OwnerActor);
	OwnerInterface->Execute_OnInitialize(OwnerActor);
}

void URPGInteractableComponent::SetupInteractableRef(UBoxComponent* InInteractableArea, UWidgetComponent* InInteractionWidgetComponent, TSet<UPrimitiveComponent*> InHighlitableObjects)
{
	InteractableArea = InInteractableArea;
	InteractionWidgetComponent = InInteractionWidgetComponent;
	HighlightingObjects = InHighlitableObjects.Array();

	for (auto& HighlitingObject : HighlightingObjects)
		HighlitingObject->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel3, ECollisionResponse::ECR_Block);
}

void URPGInteractableComponent::ToggleHighlight_Implementation(const bool bHighlight)
{
	InteractionWidgetComponent->SetVisibility(bHighlight);
	
	for (auto& ObjectToHighlight : HighlightingObjects)
		ObjectToHighlight->SetRenderCustomDepth(bHighlight);
}

void URPGInteractableComponent::PreInteraction_Implementation()
{
	switch (InputType)
	{
	case EInteractionInputType::Single:
		SwitchOnInteractableType();
		break;

	case EInteractionInputType::Holding:
		DurationPress();
		break;

	case EInteractionInputType::MultipleMashing:
		MultiplePress();
		break;
	}
}

void URPGInteractableComponent::SwitchOnInteractableType_Implementation()
{
	switch (InteractableType)
	{
	case EInteractableType::Default:
		Interaction();
		break;
	case EInteractableType::LootBox:
		//InventoryComponent->LootBoxInteraction();
		break;
	case EInteractableType::Vendor:
		//InventoryComponent->VendorInteraction();
		break;
	case EInteractableType::Storage:
		//InventoryComponent->StorageInteraction();
		break;
	case EInteractableType::Forge:
		//InventoryComponent->ForgeInteraction();
		break;
	}
}

void URPGInteractableComponent::RemoveInteraction_Implementation()
{
	AActor* OwnerActor = GetOwner();
	IRPGInteractableInterface* OwnerInterface = Cast<IRPGInteractableInterface>(OwnerActor);
	OwnerInterface->Execute_OnRemoveInteraction(OwnerActor);

	if (bDestroyAfterPickup)
		OwnerActor->Destroy(); return;

	InteractableArea = nullptr;
	SetIsInteractable(false);
}

void URPGInteractableComponent::EndInteraction_Implementation()
{
	AActor* OwnerActor = GetOwner();
	IRPGInteractableInterface* OwnerInterface = Cast<IRPGInteractableInterface>(OwnerActor);
	OwnerInterface->Execute_OnEndInteraction(OwnerActor);
}

void URPGInteractableComponent::AssociatedActorEndInteraction_Implementation()
{
	for (auto& AssociatedInteractableActor : AssociatedInteractableActors)
	{
		URPGInteractableComponent* InteractableComponent = AssociatedInteractableActor->FindComponentByClass<URPGInteractableComponent>();

		if (AssociatedInteractableActor && InteractableComponent)
			InteractableComponent->EndInteraction();
	}
}

void URPGInteractableComponent::ReInitialize_Implementation()
{
	if (InteractableResponse == EInteractionResponse::Temporary && bCanBeReInitialized)
	{
		AActor* OwnerActor = GetOwner();
		IRPGInteractableInterface* OwnerInterface = Cast<IRPGInteractableInterface>(OwnerActor);
		OwnerInterface->Execute_OnInitialize(OwnerActor);
		ToggleIsInteractable(true);
		Interaction_Widget->SetVisibility(ESlateVisibility::Visible);
	}
}

void URPGInteractableComponent::ReInitializeAssociatedActors_Implementation()
{
	for (auto& AssociatedInteractableActor : AssociatedInteractableActors)
	{
		URPGInteractableComponent* InteractableComponent = AssociatedInteractableActor->FindComponentByClass<URPGInteractableComponent>();

		if (AssociatedInteractableActor && InteractableComponent)
		{
			InteractableComponent->ToggleCanBeReInitialized(true);
			InteractableComponent->ReInitialize();
		}
	}
}

void URPGInteractableComponent::GameLoaded_Implementation()
{
	Interaction_Widget->SetVisibility(ESlateVisibility::Visible);
	AActor* OwnerActor = GetOwner();
	IRPGInteractableInterface* OwnerInterface = Cast<IRPGInteractableInterface>(OwnerActor);
	OwnerInterface->Execute_OnGameLoad(OwnerActor);
}

