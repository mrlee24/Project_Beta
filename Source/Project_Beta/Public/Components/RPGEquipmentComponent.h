// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RPGTypes.h"
#include "RPGEquipmentComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEquipmentRefreshed);

class URPGInventoryComponent;
class URPGAttributeComponent;
class URPGLevelingComponent;
class URPGEquipmentWidget;
class ARPGItemCaptureBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class PROJECT_BETA_API URPGEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	URPGInventoryComponent* InventoryComponent;

	UPROPERTY(BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	URPGAttributeComponent* AttributeComponent;

	UPROPERTY(BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	URPGLevelingComponent* LevelingComponent;

	UPROPERTY(BlueprintReadWrite, Category = "Equipment", meta = (AllowPrivateAccess = "true"))
	URPGEquipmentWidget* Equipment_Widget;

	UPROPERTY(BlueprintReadWrite, Category = "Equipment", meta = (AllowPrivateAccess = "true"))
	bool bEquipmentVisible = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment", meta = (AllowPrivateAccess = "true"))
	TMap<FRPGItemSlot, FRPGItemData> EquipmentData;

	UPROPERTY(BlueprintReadWrite, Category = "Item Capture", meta = (AllowPrivateAccess = "true"))
	ARPGItemCaptureBase* ItemCaptureRef;

	UPROPERTY(BlueprintReadWrite, Category = "Item Capture", meta = (AllowPrivateAccess = "true"))
	float DefaultCaptureRotation = 0.f;

	UPROPERTY(BlueprintAssignable)
	FOnEquipmentRefreshed OnEquipmentRefreshed;

private:
	void Init();

public:	
	// Sets default values for this component's properties
	URPGEquipmentComponent();

	TMap<FRPGItemSlot, FRPGItemData>* GetEquipmentData() { return &EquipmentData; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	bool TryToAddToPartialStackInEquipment(const FRPGItemData ItemData);

	UFUNCTION(BlueprintCallable)
	void AddStackedToEquipment(const int32 Index, const FRPGItemData ItemData);

	UFUNCTION(BlueprintCallable)
	void RefreshEquipment();
	
	UFUNCTION(BlueprintCallable)
	void RemoveFromEquipmentDataArray(const FRPGItemData ItemData);

	UFUNCTION(BlueprintCallable)
	void AddItemToEquipmentDataArray(FRPGItemData ItemData);

	UFUNCTION(BlueprintCallable)
	void ReturnQuantityToEquipment(const FRPGItemData RestStackableData);

	UFUNCTION(BlueprintCallable)
	FRPGItemData GetEquipmentItemByID(const FString ID, bool& bFound);

	void RemoveQuantityFromEquipment(FRPGItemData* ItemData, const int32 Quantity);

	UFUNCTION(BlueprintCallable)
	URPGEquipmentSlotWidget* GetEquipmentSlot(const FRPGItemSlot Slot);

	UFUNCTION(BlueprintCallable)
	bool CanItemBeEquipped(const FRPGItemData ItemToEquip) const;

	UFUNCTION(BlueprintCallable)
	FRPGItemData GetEquipmentItemBySlot(const FRPGItemSlot Slot, bool& bIsValid) const;

public:
	UFUNCTION(BlueprintCallable, Category = "Item Capture")
	void ResetCaptureRotation();

	UFUNCTION(BlueprintCallable, Category = "Item Capture")
	void PassItemCaptureReference(ARPGItemCaptureBase* InItemCaptureRef);
};
