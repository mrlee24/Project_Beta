// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/RPGPlayerCharacterInterface.h"
#include "RPGInteractionComponent.generated.h"

class URPGInventoryComponent;
class URPGInteractableComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_BETA_API URPGInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

	IRPGPlayerCharacterInterface* PlayerInterfaceRef;

	UPROPERTY(BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	URPGInventoryComponent* InventoryComponent;

	UPROPERTY(BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	URPGInteractableComponent* CurrentInteractable;

	UPROPERTY(BlueprintReadWrite, Category = "Timer", meta = (AllowPrivateAccess = "true"))
	FTimerHandle InteractionHandle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
	bool bTraceComplex = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
	float DrawTime = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
	FLinearColor TraceColor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
	FLinearColor TraceHitColor;

public:	
	// Sets default values for this component's properties
	URPGInteractionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UFUNCTION(BlueprintCallable)
	void CheckPlayerIsInInteractableArea(URPGInteractableComponent* LInteractable);

	UFUNCTION(BlueprintCallable)
	void PlayerAlreadyHighlightsActor();

public:
	UFUNCTION(BlueprintCallable)
	void ToggleInteractionTimer(const bool bOnOff);

	UFUNCTION(BlueprintCallable)
	void UpdateInteraction();

	UFUNCTION(BlueprintCallable)
	void RemoveInteractionFromCurrent(); // Unsolved comment

	UFUNCTION(BlueprintCallable)
	void AssignInteractionToLocal(class URPGInteractableComponent* LInteractable);

	UFUNCTION(BlueprintCallable)
	void CheckCurrentInteractableIsHighlighted();
		
};
