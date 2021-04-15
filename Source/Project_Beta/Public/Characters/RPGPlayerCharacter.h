// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Interfaces/RPGPlayerCharacterInterface.h"
#include "RPGTypes.h"
#include "RPGPlayerCharacter.generated.h"

class URPGInteractionComponent;
class URPGInventoryComponent;
class URPGEquipmentComponent;
class URPGAttributeComponent;
class URPGLevelingComponent;
class URPGCraftingComponent;

UCLASS()
class PROJECT_BETA_API ARPGPlayerCharacter : public ACharacter, public IRPGPlayerCharacterInterface
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* SK_Mesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	URPGInventoryComponent* InventoryComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	URPGInteractionComponent* InteractionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	URPGAttributeComponent* AttributeComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	URPGEquipmentComponent* EquipmentComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	URPGLevelingComponent* LevelingComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	URPGCraftingComponent* CraftingComponent;

public:
	// Sets default values for this character's properties
	ARPGPlayerCharacter();

	USkeletalMeshComponent* GetSkeletalMesh() const override { return GetMesh(); }
	UCameraComponent* GetCameraComponent() const override { return CameraComponent; }

	URPGInventoryComponent* GetInventoryComponent() const override { return InventoryComponent; }
	URPGInteractionComponent* GetInteractionComponent() const override { return InteractionComponent; }
	URPGAttributeComponent* GetAttributeComponent() const override { return AttributeComponent; }
	URPGEquipmentComponent* GetEquipmentComponent() const override { return EquipmentComponent; }
	URPGLevelingComponent* GetLevelingComponent() const override { return LevelingComponent; }
	URPGCraftingComponent* GetCraftingComponent() const override { return CraftingComponent; }

	UFUNCTION(BlueprintCallable)
	void TestFUNC(UPARAM(ref) FRPGStatRow& Row, FRPGStatRow& OutRow);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
