// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RPGTypes.h"
#include "RPGEquipmentComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEquipmentRefreshed);

class URPGInventoryComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_BETA_API URPGEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

	//UPROPERTY(BlueprintReadWrite, Category = "Equipment", meta = (AllowPrivateAccess = "true"))
	//URPGEquipmentWidget* Equipment_Widget;

	UPROPERTY(BlueprintReadWrite, Category = "Equipment", meta = (AllowPrivateAccess = "true"))
	bool bEquipmentVisible = false;

	UPROPERTY(BlueprintReadWrite, Category = "Equipment", meta = (AllowPrivateAccess = "true"))
	TMap<FRPGItemSlot, FRPGItemData> EquipmentData;

public:	
	// Sets default values for this component's properties
	URPGEquipmentComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

};
