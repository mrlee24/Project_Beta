// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RPGTypes.h"
#include "RPGInventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGamepadToggled, bool, bGamepadControls);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameUnfreezed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryRefreshed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnItemsBarRefreshed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnVendorStorageRefreshed);

class URPGInteractionComponent;
class URPGInteractableComponent;
class URPGActionConsumablesComponent;
class URPGVendorWidget;
class URPGInventoryOverallWidget;
class URPGInventoryBaseWidget;
class URPGReadableWindowWidget;
class ARPGItemCaptureBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class PROJECT_BETA_API URPGInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	URPGInteractionComponent* InteractionComponent;

	UPROPERTY(BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	URPGActionConsumablesComponent* ActionConsumablesComponent;
	
	UPROPERTY(BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	URPGInteractableComponent* CurrentInteractableComponent;

	UPROPERTY(BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	float CurrentInventoryWeight = 0.f;

	UPROPERTY(BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	bool bInventoryOpen = false;

	// EditAnywhere just for debugging
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	TMap<EItemType, FRPGInventoryPanelData> InventoryData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<URPGInventoryOverallWidget> InventoryOverall_Class;

	UPROPERTY(BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	URPGInventoryOverallWidget* InventoryOverall_Widget;

	UPROPERTY(BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	URPGInventoryBaseWidget* InventoryBase_Widget;

	UPROPERTY(BlueprintReadWrite, Category = "Vendor & Storage", meta = (AllowPrivateAccess = "true"))
	bool bVendorStorageOpen = false;

	UPROPERTY(BlueprintReadWrite, Category = "Vendor & Storage", meta = (AllowPrivateAccess = "true"))
	URPGVendorWidget* Vendor_Widget;

	//UPROPERTY(BlueprintReadWrite, Category = "Vendor & Storage", meta = (AllowPrivateAccess = "true"))
	//URPGStorageWidget* Storage_Widget;

	//UPROPERTY(BlueprintReadWrite, Category = "Vendor & Storage", meta = (AllowPrivateAccess = "true"))
	//URPGVendorStorageInventoryWidget* VendorStorageInventory_Widget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player", meta = (AllowPrivateAccess = "true"))
	float PlayerGold = 0.f;

	UPROPERTY(BlueprintReadWrite, Category = "Gamepad", meta = (AllowPrivateAccess = "true"))
	bool bGamepadControls = false;

	UPROPERTY(BlueprintReadWrite, Category = "Gamepad", meta = (AllowPrivateAccess = "true"))
	EWidgetType FocusedWidget;

	UPROPERTY(BlueprintReadWrite, Category = "KeyBindings", meta = (AllowPrivateAccess = "true"))
	TSet<FKey> InventoryKeybindings;

	UPROPERTY(BlueprintReadWrite, Category = "KeyBindings", meta = (AllowPrivateAccess = "true"))
	TSet<FKey> ExitKeybindings;

	UPROPERTY(BlueprintReadWrite, Category = "KeyBindings", meta = (AllowPrivateAccess = "true"))
	TSet<FKey> LoadGameKeyBindings;

	UPROPERTY(BlueprintReadWrite, Category = "Readable Window", meta = (AllowPrivateAccess = "true"))
	URPGReadableWindowWidget* ReadabkeWindow_Widget;

	UPROPERTY(BlueprintReadWrite, Category = "Readable Window", meta = (AllowPrivateAccess = "true"))
	bool bIsReadableWindowOpen = false;

	UPROPERTY(BlueprintReadWrite, Category = "Inputs", meta = (AllowPrivateAccess = "true"))
	EInputMethod CurrentInputMethod;

	UPROPERTY(BlueprintReadWrite, Category = "Inputs", meta = (AllowPrivateAccess = "true"))
	EWidgetType CurrentWidgetInput;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customizable", meta = (AllowPrivateAccess = "true"))
	float MaxInventoryWeight = 120.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customizable", meta = (AllowPrivateAccess = "true"))
	int32 InventoryMaxSize = 30;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customizable", meta = (AllowPrivateAccess = "true"))
	FLinearColor BackgrounColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customizable", meta = (AllowPrivateAccess = "true"))
	FSlateColor CommonColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customizable", meta = (AllowPrivateAccess = "true"))
	FSlateColor RareColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customizable", meta = (AllowPrivateAccess = "true"))
	FSlateColor ConsumableColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customizable", meta = (AllowPrivateAccess = "true"))
	FSlateColor SuperiorColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customizable", meta = (AllowPrivateAccess = "true"))
	FSlateColor EpicColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customizable", meta = (AllowPrivateAccess = "true"))
	FSlateColor LegendaryColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customizable", meta = (AllowPrivateAccess = "true"))
	FSlateColor UseableColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customizable", meta = (AllowPrivateAccess = "true"))
	FText FullInventoryNotify = FText::FromString("Your Inventory is Full");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customizable", meta = (AllowPrivateAccess = "true"))
	FText FullStorageInventoryNotify = FText::FromString("Storage Inventory is Full");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customizable", meta = (AllowPrivateAccess = "true"))
	FText FullVendorInventoryNotify = FText::FromString("Vendor Inventory is Full");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customizable", meta = (AllowPrivateAccess = "true"))
	bool bAutoQuickSort = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customizable", meta = (AllowPrivateAccess = "true"))
	TArray<FRPGSingleDTItem> InitialInventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customizable", meta = (AllowPrivateAccess = "true"))
	TArray<FRPGSingleDTItem> InitialEquipment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customizable", meta = (AllowPrivateAccess = "true"))
	bool bCheckRequiredItemLevel = true;

	UPROPERTY(BlueprintReadWrite, Category = "Item Capture", meta = (AllowPrivateAccess = "true"))
	ARPGItemCaptureBase* ItemCaptureRef;

	UPROPERTY(BlueprintReadWrite, Category = "Item Capture", meta = (AllowPrivateAccess = "true"))
	float DefaultCaptureRotation = 0.f;

public:
	UPROPERTY(BlueprintAssignable)
	FOnGamepadToggled OnGamepadToggled;

public:
	TArray<FRPGItemData>* SelectCorrectInventory(const FRPGItemData ItemData);

	TArray<FRPGItemData>* SelectCorrectInventory(const EItemType Type);

	void AssignItemsToCorrectInventory(const EItemType Type, TArray<FRPGItemData> ItemsArray);

	TArray<FRPGItemData>* GetInventoryByType(const EItemType Type);

	void SortEveryPanel(const ESortMethod Selection);

	void SortActivePanel(const ESortMethod Selection);

	void AddItemToEmptySlotInInventory(TArray<FRPGItemData>* InventoryArray, const FRPGItemData ItemData, int32& AddedSlotIndex, bool& bInventoryFull);

public:
	// Sets default values for this component's properties
	URPGInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetupInventoryData();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetupInitialInventory();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ToggleGamepadControls(const bool bIsUsingGamepad);

public:
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void TryToAddToInventory(const FRPGItemData ItemData, int32& AddedSlotIndex, bool& bInventoryFull);

	void AddStackToInventory(const int32 SlotIndex, TArray<FRPGItemData>* InventoryArray, const FRPGItemData ItemData);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void RefreshInventory();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddItemWeight(const FRPGItemData ItemData);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void RemoveItemWeight(const FRPGItemData ItemData);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Inventory")
	TArray<FRPGItemData> GetCombinedInventories() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Inventory")
	FRPGItemData GetInventoryItemByID(const FString ID, const bool bSpecifiedType, const EItemType Type, bool& bFound);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Inventory")
	FRPGItemData GetInventoryItemByData(const FRPGItemData ItemData, bool& bFound);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool CheckInventorySpace(const EItemType Type);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void HighlightInventorySlot(const int32 SlotIndex);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void ReplaceItemInInventory(const FRPGItemData ItemData);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool IsInventoryOverweighted(); 
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void CanBeAddedToSlotInInventory(const FRPGItemData ItemData, bool& bAdded);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddItemToInventory(const FRPGItemData ItemData, bool& bSuccess);

public:
	UFUNCTION(BlueprintCallable, Category = "Player")
	bool IsPlayerGoldEnough(const FRPGItemData ItemData) const;

	UFUNCTION(BlueprintCallable, Category = "Player")
	void AddItemGold(const FRPGItemData ItemData);

	UFUNCTION(BlueprintCallable, Category = "Player")
	void RemoveItemGold(const FRPGItemData ItemData);

	UFUNCTION(BlueprintCallable, Category = "Player")
	void AddGoldToPlayerInventory(const float Amount = 0.f);

	UFUNCTION(BlueprintCallable, Category = "Player")
	void RemoveGoldFromPlayerInventory(const float Amount = 0.f);

public:
	UFUNCTION(BlueprintCallable, Category = "Sorting Items")
	void SortByType(const EItemType Type);

	UFUNCTION(BlueprintCallable, Category = "Sorting Items")
	void SortItemsInInventory(const bool bEveryPanel, const ESortMethod Method);

	UFUNCTION(BlueprintCallable, Category = "Sorting Items")
	void SortByRarity(const EItemType Type);

	UFUNCTION(BlueprintCallable, Category = "Sorting Items")
	void SortByValue(const EItemType Type);

	UFUNCTION(BlueprintCallable, Category = "Sorting Items")
	void SortByWeight(const EItemType Type);

	UFUNCTION(BlueprintCallable, Category = "Sorting Items")
	void QuickSort(const EItemType Type);

public:
	UFUNCTION(BlueprintCallable, Category = "Gamepad")
	EWidgetType GetFocusedWidget() const { return FocusedWidget; }

	UFUNCTION(BlueprintCallable, Category = "Gamepad")
	void SetFocusedWidget(EWidgetType InFocusedWidget) { FocusedWidget = InFocusedWidget; }

public:
	UFUNCTION(BlueprintCallable, Category = "Inputs")
	void AssignCurrentWidgetInput(const EInputMethod InputMethod, const EWidgetType WidgetType);

	UFUNCTION(BlueprintCallable, Category = "Inputs")
	void GetCurrentWidgetInput(EInputMethod& InputMethod, EWidgetType& WidgetType);

public:
	UFUNCTION(BlueprintCallable, Category = "Item Capture")
	void ResetCaptureRotation();

	UFUNCTION(BlueprintCallable, Category = "Item Capture")
	void PassItemCaptureReference(ARPGItemCaptureBase* InItemCaptureRef);

public:
	UFUNCTION(BlueprintCallable)
	FSlateColor SetRarityColor(const EItemRarity Rarity) const;

public:
	TMap<EItemType, FRPGInventoryPanelData> GetInventoryData() const { return InventoryData; }
	void SetInventoryData(TMap<EItemType, FRPGInventoryPanelData> InInventoryData) { InventoryData = InInventoryData; }

	float GetCurrentInventoryWeight() const { return CurrentInventoryWeight; }
	void SetCurrentInventoryWeight(float InCurrentInventoryWeight) { CurrentInventoryWeight = InCurrentInventoryWeight; }

	float GetMaxInventoryWeight() const { return MaxInventoryWeight; }
	void SetMaxInventoryWeight(float InMaxInventoryWeight) { MaxInventoryWeight = InMaxInventoryWeight; }

	bool GetInventoryOpen() const { return bInventoryOpen; }
	void SetInventoryOpen(bool InbInventoryOpen) { bInventoryOpen = InbInventoryOpen; }

	float GetPlayerGold() const { return PlayerGold; }
	void SetPlayerGold(float InPlayerGold) { PlayerGold = InPlayerGold; }

	bool GetGamepadControls() const { return bGamepadControls; }
	void SetGamepadControls(bool InbGamepadControls) { bGamepadControls = InbGamepadControls; }

	TSet<FKey> GetInventoryKeybindings() const { return InventoryKeybindings; }

	TSet<FKey> GetExitKeybindings() const { return ExitKeybindings; }

	TSet<FKey> GetLoadGameKeyBindings() const { return LoadGameKeyBindings; }

	URPGInventoryOverallWidget* GetInventoryOverall_Widget() const { return InventoryOverall_Widget; }

	bool GetCheckRequiredItemLevel() const { return bCheckRequiredItemLevel; }
};
