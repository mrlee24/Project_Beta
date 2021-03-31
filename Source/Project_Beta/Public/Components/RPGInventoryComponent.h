// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RPGInventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGamepadToggled, bool, bGamepadControls);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameUnfreezed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEquipmentRefreshed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryRefreshed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnItemsBarRefreshed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnVendorStorageRefreshed);

class URPGInteractableComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_BETA_API URPGInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	URPGInteractableComponent* CurrentInteractable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bGamepadControls = false;

public:
	UPROPERTY(BlueprintAssignable)
	FOnGamepadToggled OnGamepadToggled;
	
public:	
	// Sets default values for this component's properties
	URPGInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	bool GetGamepadControls() const { return bGamepadControls; }
	void SetGamepadControls(bool InbGamepadControls) { bGamepadControls = InbGamepadControls; }
};
