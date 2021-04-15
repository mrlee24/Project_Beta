// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/RPGCaptureInterface.h"
#include "RPGPlayerCaptureBase.generated.h"

UCLASS()
class PROJECT_BETA_API ARPGPlayerCaptureBase : public AActor, public IRPGCaptureInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARPGPlayerCaptureBase();

public:
	UFUNCTION(BlueprintCallable)
	void AttachItem(const FRPGItemData ItemData) override;

	UFUNCTION(BlueprintCallable)
	void DetachItem(const FRPGItemData ItemData) override;

};
