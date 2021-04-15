// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RPGTypes.h"
#include "RPGEquipmentWidget.generated.h"

class URPGInventoryComponent;
class URPGEquipmentComponent;
class URPGEquipmentSlotWidget;

UCLASS()
class PROJECT_BETA_API URPGEquipmentWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	URPGInventoryComponent* InventoryComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	URPGEquipmentComponent* EquipmentComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true"))
	FRPGItemSlot LastFocusedSlot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	URPGEquipmentSlotWidget* RWeapon1_EqSlot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	URPGEquipmentSlotWidget* RWeapon2_EqSlot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	URPGEquipmentSlotWidget* LWeapon1_EqSlot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	URPGEquipmentSlotWidget* LWeapon2_EqSlot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	URPGEquipmentSlotWidget* Head_EqSlot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	URPGEquipmentSlotWidget* Chestplate_EqSlot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	URPGEquipmentSlotWidget* Legs_EqSlot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	URPGEquipmentSlotWidget* Gloves_EqSlot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	URPGEquipmentSlotWidget* Accessory1_EqSlot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	URPGEquipmentSlotWidget* Accessory2_EqSlot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	URPGEquipmentSlotWidget* Consumable1_EqSlot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	URPGEquipmentSlotWidget* Consumable2_EqSlot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	URPGEquipmentSlotWidget* Consumable3_EqSlot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	URPGEquipmentSlotWidget* Consumable4_EqSlot;

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void CreateEquipment();

public:
	UFUNCTION(BlueprintCallable)
	void SetEquipmentSlot(URPGEquipmentSlotWidget* EquipmentSlot_Widget, const FRPGItemData ItemData);
	
	UFUNCTION(BlueprintCallable)
	void SetFocusToSlot(const FRPGItemSlot InSlot);

	UFUNCTION(BlueprintCallable)
	URPGEquipmentSlotWidget* GetWidgetSlotByItemSlot(const FRPGItemSlot InSlot) const;
};
