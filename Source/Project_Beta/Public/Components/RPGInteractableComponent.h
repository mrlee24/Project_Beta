// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Engine/TargetPoint.h"
#include "Components/ActorComponent.h"
#include "Components/PrimitiveComponent.h" 	
#include "Components/TimelineComponent.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/Actor.h"
#include "Interfaces/RPGInteractableInterface.h"
#include "RPGTypes.h"
#include "RPGInteractableComponent.generated.h"

class URPGInventoryComponent;
class URPGInteractionWidget;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class PROJECT_BETA_API URPGInteractableComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* InteractableArea;

	UPROPERTY(BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* InteractionWidgetComponent;

	UPROPERTY(BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	URPGInventoryComponent* InventoryComponent;

	UPROPERTY(BlueprintReadWrite, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	FName InteractableTag = TEXT("Interactable");

	UPROPERTY(BlueprintReadWrite, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	TArray<UPrimitiveComponent*> HighlightingObjects;

	UPROPERTY(BlueprintReadWrite, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	FName DestroyableTag = TEXT("Destroyable");

	UPROPERTY(BlueprintReadWrite, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	bool bAlreadyInteracted;

	UPROPERTY(BlueprintReadWrite, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	float MashingPressedAmount = 0.f;

	UPROPERTY(BlueprintReadWrite, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	URPGInteractionWidget* Interaction_Widget;

	UPROPERTY(BlueprintReadWrite, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	FTimerHandle KeyDownTimer;

	UPROPERTY(BlueprintReadWrite, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	FTimerHandle MashingKeyTimer;

	UPROPERTY(BlueprintReadWrite, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	FTimerHandle ToggleTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	bool bCanBeReInitialized;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Moveable Object", meta = (AllowPrivateAccess = "true"))
	float TimelinePosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Moveable Object", meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<ETimelineDirection::Type> TimelineDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main", meta = (AllowPrivateAccess = "true"))
	bool bIsInteractable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	EInteractableType InteractableType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	bool bDestroyAfterPickup;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	FText DefaultInteractionText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	TArray<AActor*> AssociatedInteractableActors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	float MaxKeyTimeDown = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	int MaxMashingAmount = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	float MashingKeyRetriggerableTime = 0.2f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	EInteractionInputType InputType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	EInteractionResponse InteractableResponse;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	int32 InteractableValue = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	int32 InteractableTargetValue = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	int32 InteractableLimitValue = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	bool bCheckForAssociatedActors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	bool bRemoveAssociatedInteractablesOnComplete;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Datas", meta = (AllowPrivateAccess = "true"))
	TArray<FRPGItemData> ItemData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Datas", meta = (AllowPrivateAccess = "true"))
	TArray<UDataTable*> AllItemsFromDT;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Datas", meta = (AllowPrivateAccess = "true"))
	TArray<FRPGSingleDTItem> SingleDTItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Datas", meta = (AllowPrivateAccess = "true"))
	FRPGRandomizedLootTable RandomizedItemsData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Datas", meta = (AllowPrivateAccess = "true"))
	ESortMethod SortingMethod;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Datas", meta = (AllowPrivateAccess = "true"))
	bool bRandomizeItemsData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Datas", meta = (AllowPrivateAccess = "true"))
	bool bReverseSorting;

	UPROPERTY(EditAnywhere, DisplayName = "Inventory Size (Vendor / Storage)", BlueprintReadWrite, Category = "Vendor Storage", meta = (AllowPrivateAccess = "true"))
	int32 InventorySize = 0;

	UPROPERTY(EditAnywhere, DisplayName = "Inventory Size (Vendor / Storage)", BlueprintReadWrite, Category = "Vendor Storage", meta = (AllowPrivateAccess = "true"))
	float VendorGold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movable Object", meta = (AllowPrivateAccess = "true"))
	ATargetPoint* DestinationPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movable Object", meta = (AllowPrivateAccess = "true"))
	float TravelDuration = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door", meta = (AllowPrivateAccess = "true"))
	FString KeyID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door", meta = (AllowPrivateAccess = "true"))
	bool bRemoveItemAfterUnlock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door", meta = (AllowPrivateAccess = "true"))
	EInventoryPanel SpecifiedPanel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door", meta = (AllowPrivateAccess = "true"))
	bool bUseSpecifiedCategory;

public:	
	// Sets default values for this component's properties
	URPGInteractableComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UFUNCTION(Category = "Interactable Area | Events")
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult); // Unsolved comment

	UFUNCTION(Category = "Interactable Area | Events")
	void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex); // Unsolved comment

public:
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void ToggleIsInteractable(bool bCondition);

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void FillInteractionWidgetBorder(float InValue); // Unsolved comment

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void ToggleInteractionWidget(bool bCondition); // UnSolved comment

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void RemoveInteractionByResponse();

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void ChangeInteractableValue(bool bIncrement);

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void ToggleCanBeReInitialized(bool bCondition);

	UFUNCTION(BlueprintCallable, Category = "Item Datas")
	void SetupData();

	UFUNCTION(BlueprintCallable, Category = "Item Datas")
	void SortItems();

	UFUNCTION(BlueprintCallable, Category = "Item Datas")
	void RandomizeItems();

	UFUNCTION(BlueprintCallable, Category = "Item Datas")
	void ChooseItemsToAdd(TArray<FRPGItemData> InItemArray, int32 InAmount);

	UFUNCTION(BlueprintCallable, Category = "Item Datas")
	void AssignRandomValue(FRPGItemData& LItemToAssign);

	UFUNCTION(BlueprintCallable, Category = "Item Datas")
	void AssignRandomItemStats(FRPGItemData& LItemToAssign, const int32 InRandomizationLevel);

	UFUNCTION(BlueprintCallable, Category = "Item Datas")
	void ReverseItemDataArray();

	UFUNCTION(BlueprintPure, Category = "Item Datas")
	float GetMultipliedValueFromDataTable(UDataTable* DataTable, FName RowName) const;

	UFUNCTION(BlueprintPure, Category = "Item Datas")
	int32 GetRandomizedLevel(FRPGItemData Item, int32 RandomizationLevel) const;

	UFUNCTION(BlueprintPure, Category = "Item Datas")
	FRPGItemDurability GetRandomizedItemDurability(FRPGItemData InItem) const;

	UFUNCTION(BlueprintPure, Category = "Item Datas")
	float GetRandomizedItemValue(FRPGItemData InItem, int32 RandomizationLevel) const;

	UFUNCTION(BlueprintPure, Category = "Item Datas")
	FRPGItemStack GetRandomizedItemQuantity(FRPGItemData InItem) const;

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "On Interaction")
	void Interaction(); // Unsolved comment

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "On Interaction")
	void AssociatedActorInteraction();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "On Interaction")
	void CheckForInteractionWithAssociate();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Before Interaction")
	void Initialize(); // Unsolved comment

	UFUNCTION(BlueprintCallable, Category = "Before Interaction")
	void SetupInteractableRef(UBoxComponent* InInteractableArea, UWidgetComponent* InInteractionWidgetComponent, TSet<UPrimitiveComponent*> InHighlitableObjects);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Before Interaction")
	void ToggleHighlight(const bool bHighlight);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Before Interaction")
	void PreInteraction();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Before Interaction")
	void DurationPress();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Before Interaction")
	void MultiplePress();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Before Interaction")
	void SwitchOnInteractableType(); // Unsolved comment

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "After Interaction")
	void RemoveInteraction(); // Unsolved comment

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "After Interaction")
	void EndInteraction(); // Unsolved comment

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "After Interaction")
	void AssociatedActorEndInteraction();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "After Interaction")
	void ReInitialize(); // Unsolved comment

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "After Interaction")
	void ReInitializeAssociatedActors();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "After Interaction")
	void GameLoaded(); // Unsolved comment

public:
	UBoxComponent* GetInteractableArea() const { return InteractableArea; }
	void SetInteractableArea(UBoxComponent* InInteractableArea) { InteractableArea = InInteractableArea; }

	bool GetIsInteractable() const { return bIsInteractable; }
	void SetIsInteractable(bool InbIsInteractable) { bIsInteractable = InbIsInteractable; }
};
