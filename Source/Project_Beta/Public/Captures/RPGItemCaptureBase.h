// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/RPGCaptureInterface.h"
#include "Components/SceneComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SpotLightComponent.h"
#include "RPGTypes.h"
#include "RPGItemCaptureBase.generated.h"

class URPGInventoryComponent;
class URPGEquipmentComponent;

UCLASS()
class PROJECT_BETA_API ARPGItemCaptureBase : public AActor, public IRPGCaptureInterface
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	URPGInventoryComponent* InventoryComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	URPGEquipmentComponent* EquipmentComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* SceneComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* SkeletalMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneCaptureComponent2D* SceneCaptureComponent2D;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UArrowComponent* ArrowComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USpotLightComponent* SpotlightComponent;
	
public:	
	// Sets default values for this actor's properties
	ARPGItemCaptureBase();

	USkeletalMeshComponent* GetSkeletalMeshComponent() const { return SkeletalMeshComponent; }

public:
	UFUNCTION(BlueprintCallable)
	void AttachItem(const FRPGItemData ItemData) override;

	UFUNCTION(BlueprintCallable)
	void DetachItem(const FRPGItemData ItemData) override;
};
