// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Interfaces/RPGPlayerCharacterInterface.h"
#include "RPGPlayerCharacter.generated.h"

class URPGInteractionComponent;
class URPGInventoryComponent;
class URPGAttributeComponent;

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

public:
	// Sets default values for this character's properties
	ARPGPlayerCharacter();

	USkeletalMeshComponent* GetSkeletalMesh() const override { return GetMesh(); }
	UCameraComponent* GetCameraComponent() const override { return CameraComponent; }

	URPGInventoryComponent* GetInventoryComponent() const override { return InventoryComponent; }
	URPGInteractionComponent* GetInteractionComponent() const override { return InteractionComponent; }

	URPGAttributeComponent* GetAttributeComponent() const { return AttributeComponent; }
	void SetAttributeComponent(URPGAttributeComponent* InAttributeComponent) { AttributeComponent = InAttributeComponent; }
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
