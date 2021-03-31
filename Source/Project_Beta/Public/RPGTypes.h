// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataTable.h"
#include "Styling/SlateBrush.h"
#include "Components/TimelineComponent.h"
#include "Libraries/MeshMergeFunctionLibrary.h"
#include "RPGTypes.generated.h"

class ARPGItemBase;
class UStaticMesh;
class USkeletalMesh;
class AActor;

UENUM(BlueprintType)
enum class EGamepadInputs : uint8
{
	FaceButtonBottom,
	FaceButtonRight,
	FaceButtonLeft,
	FaceButtonTop,
	LeftThumbstick,
	LeftThumbstickButton,
	RightThumbstick,
	RightThumbstickButton,
	LeftShoulder,
	RightShoulder,
	LeftTrigger,
	RightTrigger,
	DpadUp,
	DpadDown,
	DpadRight,
	DpadLeft,
	SpecialLeft,
	SpecialRight
};

UENUM(BlueprintType)
enum class EInputMethod : uint8
{
	None,
	RightClick,
	DragDrop
};

UENUM(BlueprintType)
enum class EWidgetType : uint8
{
	None,
	Inventory,
	Equipment,
	Crafting,
	Vendor,
	Storage,
	LoadGame,
	Abilities,
	SplitStack,
	ReadableText,
	ConfirmationMenu,
	DropWindow
};

UENUM(BlueprintType)
enum class EInteractionResponse : uint8
{
	Persistent,
	OnlyOnce,
	Temporary
};

UENUM(BlueprintType)
enum class EInteractionState : uint8
{
	None,
	Complete,
	Reset
};

UENUM(BlueprintType)
enum class ESaveType : uint8
{
	None,
	QuickSave,
	ManualSave,
	Checkpoint
};

UENUM(BlueprintType)
enum class EInteractionInputType : uint8
{
	Single,
	Holding,
	MultipleMashing
};

UENUM(BlueprintType)
enum class EInteractableType : uint8
{
	Default,
	LootBox,
	Vendor,
	Storage,
	Forge
};

UENUM(BlueprintType)
enum class ESortMethod : uint8
{
	None,
	QuickSort,
	ByRarity,
	ByType,
	ByValue,
	ByWeight
};

UENUM(BlueprintType)
enum class EInventoryPanel : uint8
{
	None,
	P1,
	P2,
	P3,
	P4
};

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	None,
	OneHanded,
	TwoHanded,
	Ranged,
	Polearm
};

UENUM(BlueprintType)
enum class EWeaponCategory : uint8
{
	None,
	Sword,
	Warhammer,
	Axe,
	Mace
};

UENUM(BlueprintType)
enum class EItemRarity : uint8
{
	None,
	Common,
	Rare,
	Epic,
	Legendary,
	Useable,
	Consumable
};

UENUM(BlueprintType)
enum class EItemType : uint8
{
	None,
	Weapon,
	Shield,
	Armor,
	Ammo,
	Accessory,
	Potion,
	CraftingIngredient,
	QuestItem,
	Currency
};

UENUM(BlueprintType)
enum class EEffectCategory : uint8
{
	None,
	Instantly,
	OverDuration,
	ForDuration
};

UENUM(BlueprintType)
enum class EAdditionalEffect : uint8
{
	None,
	Drunk,
	NightVision
};

UENUM(BlueprintType)
enum class EItemUseType : uint8
{
	None,
	ReadableText
};

UENUM(BlueprintType)
enum class EItemRemoveType : uint8
{
	None,
	OnConfirmation,
	CannotBeRemoved
};

UENUM(BlueprintType)
enum class EStatCategory : uint8
{
	None,
	Health,
	MaxHealth,
	Stamina,
	MaxStamina,
	Mana,
	MaxMana,
	Armor,
	Damage,
	AttackSpeed
};
USTRUCT(BlueprintType)
struct PROJECT_BETA_API FRPGStatRow
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EStatCategory Stat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Value;
};

USTRUCT(BlueprintType)
struct FRPGConsumableAction
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEffectCategory Category;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EStatCategory Stat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NumberOfRepetitions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Duration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAdditionalEffect AdditionEffect;
};

USTRUCT(BlueprintType)
struct FRPGSingleDTItem : public FTableRowBase
{
	GENERATED_BODY()

	FRPGSingleDTItem() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Single Datatable Item")
	FDataTableRowHandle TableAndRow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Single Datatable Item")
	int32 Quantity;
};

USTRUCT(BlueprintType)
struct FRPGCrafting : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRPGSingleDTItem CraftableItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FRPGSingleDTItem> RequiredItems;
};

USTRUCT(BlueprintType)
struct FRPGMultiplier : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mulitplier")
	float MultiplyValue;
};

USTRUCT(BlueprintType)
struct FRPGRandomizedLootTable
{
	GENERATED_BODY()

	FRPGRandomizedLootTable() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Randomized Loot Table")
	TArray<UDataTable*> DataTables;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Randomized Loot Table")
	TMap<EItemType, int32> MaxSameTypesAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Randomized Loot Table")
	TMap<EItemType, int32> MinSameTypesAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Randomized Loot Table")
	int32 MaxLootItems;
};


USTRUCT(BlueprintType)
struct FRPGRandomIntegerValue
{
	GENERATED_BODY()

	FRPGRandomIntegerValue() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Integer Randomizer")
	int32 MinValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Integer Randomizer")
	int32 MaxValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Integer Randomizer")
	UDataTable* MultiplierDataTable;
};

USTRUCT(BlueprintType)
struct FRPGRandomFloatValue
{
	GENERATED_BODY()

	FRPGRandomFloatValue() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Float Randomizer")
	float MinValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Float Randomizer")
	float MaxValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Float Randomizer")
	UDataTable* MultiplierDataTable;
};

USTRUCT(BlueprintType)
struct FRPGItemDesc
{
	GENERATED_BODY()

	FRPGItemDesc() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Description")
	FString ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Description")
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Description")
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Description")
	FText ReadableText;
};

USTRUCT(BlueprintType)
struct FRPGItemDurability
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Stat Row")
	bool bUseDurability;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Stat Row")
	int32 CurrentDurability;
};

USTRUCT(BlueprintType)
struct FRPGItemStat
{
	GENERATED_BODY()

	FRPGItemStat() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Stats")
	float Weight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Stats")
	float Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Stats")
	TArray<FRPGStatRow> Stats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Stats")
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Stats")
	FRPGConsumableAction ConsumableAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Stats")
	FRPGItemDurability Durability;
};

USTRUCT(BlueprintType)
struct FRPGItemStack
{
	GENERATED_BODY()

	FRPGItemStack() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Stack")
	bool bStackable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Stack")
	int32 Quantity;
};

USTRUCT(BlueprintType)
struct FRPGItemUse
{
	GENERATED_BODY()

	FRPGItemUse() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Use")
	EItemUseType UseableType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Use")
	bool bIsAlreadyUsed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Use")
	EItemRemoveType RemoveType;
};

USTRUCT(BlueprintType)
struct FRPGItemRandomStats
{
	GENERATED_BODY()

	FRPGItemRandomStats() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Use")
	EStatCategory Stat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Use")
	FRPGRandomFloatValue ValueAndMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Use")
	bool bRountToInt;
};

USTRUCT(BlueprintType)
struct FRPGItemRandomLoot
{
	GENERATED_BODY()

	FRPGItemRandomLoot() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Random Loot")
	int32 DropPercentage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Random Loot")
	int32 MinQuantity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Random Loot")
	int32 MaxQuantity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Random Loot")
	int32 MinDurability;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Random Loot")
	int32 MaxDurability;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Random Loot")
	TArray<FRPGItemRandomStats> RandomStats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Random Loot")
	FRPGRandomFloatValue RandomValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Random Loot")
	FRPGRandomIntegerValue RandomLevel;
};

USTRUCT(BlueprintType)
struct PROJECT_BETA_API FRPGItemDescription
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ReadableText;
};

USTRUCT(BlueprintType)
struct PROJECT_BETA_API FRPGItemSlot
{
	GENERATED_BODY()

	/** Constructor, -1 means an invalid slot */
		FRPGItemSlot()
		: SlotNumber(-1)
	{}

	FRPGItemSlot(const EItemType& InItemType, int32 InSlotNumber)
		: ItemType(InItemType)
		, SlotNumber(InSlotNumber)
	{}

	/** The type of items that can go in this slot */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	EItemType ItemType;

	/** The number of this slot, 0 indexed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	int32 SlotNumber;

	/** Equality operators */
	bool operator==(const FRPGItemSlot& Other) const
	{
		return ItemType == Other.ItemType && SlotNumber == Other.SlotNumber;
	}
	bool operator!=(const FRPGItemSlot& Other) const
	{
		return !(*this == Other);
	}

	/** Implemented so it can be used in Maps/Sets */
	friend inline uint32 GetTypeHash(const FRPGItemSlot& Key)
	{
		uint32 Hash = 0;

		Hash = HashCombine(Hash, GetTypeHash(Key.ItemType));
		Hash = HashCombine(Hash, (uint32)Key.SlotNumber);
		return Hash;
	}

	/** Returns true if slot is valid */
	bool IsValid() const
	{
		return ItemType != EItemType::None && SlotNumber >= 0;
	}
};

USTRUCT(BlueprintType)
struct PROJECT_BETA_API FRPGItemData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	EItemType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	EItemRarity Rarity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FRPGItemSlot Slot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	EWeaponCategory WeaponCategory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TArray<EWeaponType> WeaponTypes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	EInventoryPanel InventoryPanel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults")
	TSubclassOf<ARPGItemBase> Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults")
	UStaticMesh* EquippableStaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults")
	USkeletalMesh* EquippableSkeletalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults")
	FSkeletalMeshMergeParams MeshMergeParameters;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults")
	FSlateBrush Thumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults")
	int32 Index;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Description")
	FRPGItemDescription Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
	FRPGItemStat Stats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
	FRPGItemStack Stacks;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Usage")
	FRPGItemUse Use;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults")
	bool bEquipped;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Randomizer")
	FRPGItemRandomLoot LootRandomizer;

	bool operator==(const FRPGItemData& Other) const
	{
		return Type != Other.Type && Description.ID == Other.Description.ID;
	}

	bool operator!=(const FRPGItemData& Other) const
	{
		return !(*this == Other);
	}

	bool IsValid() const 
	{
		return Type != EItemType::None;
	}

	bool IsStackable() const 
	{
		return Stacks.bStackable; 
	}

	bool IsStackableAndHasStacks() const 
	{
		return Stacks.bStackable && Stacks.Quantity > 1; 
	}
};

USTRUCT(BlueprintType)
struct PROJECT_BETA_API FRPGInventoryPanelData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EInventoryPanel Panel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Size;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FRPGItemData> ArrayData;
};

USTRUCT(BlueprintType)
struct PROJECT_BETA_API FRPGSaveBuffs
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRPGConsumableAction BuffData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentReps;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTimerHandle TimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimelinePosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PlayRate;
};

USTRUCT(BlueprintType)
struct PROJECT_BETA_API FRPGSaveSlotDetails
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SlotName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ESaveType SaveType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSlateBrush Image;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ImageFileName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString QuestName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString LocationName;
};

USTRUCT(BlueprintType)
struct PROJECT_BETA_API FRPGSaveStats
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Gold = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentInventoryWeight = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxInventoryWeight = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FRPGStatRow> Stats;
};

USTRUCT(BlueprintType)
struct PROJECT_BETA_API FRPGSaveCheckpoints
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AActor> Checkpoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTransform Transform;
};

USTRUCT(BlueprintType)
struct PROJECT_BETA_API FRPGSaveInteractables
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* InteractableActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> SpawnActorClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTransform Transform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FRPGItemData> ItemData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bDestroyAfterPickup;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 InventorySize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float VendorGold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsInteractable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* AttachedParentActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimelinePosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<ETimelineDirection::Type> TimelineDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bAlreadyInteracted;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 InteractionValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EInteractionResponse InteractionResponse;
};

