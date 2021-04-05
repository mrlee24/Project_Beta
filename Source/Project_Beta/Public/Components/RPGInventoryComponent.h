// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RPGTypes.h"
#include "RPGInventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGamepadToggled, bool, bGamepadControls);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameUnfreezed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEquipmentRefreshed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryRefreshed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnItemsBarRefreshed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnVendorStorageRefreshed);

class URPGInteractionComponent;
class URPGInteractableComponent;
class URPGActionConsumablesComponent;
class URPGLevelingComponent;
class URPGVendorWidget;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_BETA_API URPGInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	URPGInteractionComponent* InteractionComponent;

	UPROPERTY(BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	URPGActionConsumablesComponent* ActionConsumablesComponent;
	
	UPROPERTY(BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	URPGInteractableComponent* CurrentInteractableComponent;

	UPROPERTY(BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	URPGLevelingComponent* LevelingComponent;

	UPROPERTY(BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	float CurrentInventoryWeight = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bGamepadControls = false;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customizable", meta = (AllowPrivateAccess = "true"))
	float MaxInventoryWeight = 120.f;

public:
	UPROPERTY(BlueprintAssignable)
	FOnGamepadToggled OnGamepadToggled;

public:
	// Sets default values for this component's properties
	URPGInventoryComponent();

	UFUNCTION(BlueprintCallable, Category = "Player")
	bool IsPlayerGoldEnough(const FRPGItemData ItemData) const;

	UFUNCTION(BlueprintCallable, Category = "Player")
	void AddGoldToPlayerInventory(const float Amount = 0.f);

	UFUNCTION(BlueprintCallable, Category = "Player")
	void RemoveGoldFromPlayerInventory(const float Amount = 0.f);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	float GetCurrentInventoryWeight() const { return CurrentInventoryWeight; }
	void SetCurrentInventoryWeight(float InCurrentInventoryWeight) { CurrentInventoryWeight = InCurrentInventoryWeight; }

	float GetPlayerGold() const { return PlayerGold; }
	void SetPlayerGold(float InPlayerGold) { PlayerGold = InPlayerGold; }

	bool GetGamepadControls() const { return bGamepadControls; }
	void SetGamepadControls(bool InbGamepadControls) { bGamepadControls = InbGamepadControls; }

	float GetMaxInventoryWeight() const { return MaxInventoryWeight; }
	void SetMaxInventoryWeight(float InMaxInventoryWeight) { MaxInventoryWeight = InMaxInventoryWeight; }
};
