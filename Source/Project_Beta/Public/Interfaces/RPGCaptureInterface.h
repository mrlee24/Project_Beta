// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RPGTypes.h"
#include "RPGCaptureInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class URPGCaptureInterface : public UInterface
{
	GENERATED_BODY()
};

class PROJECT_BETA_API IRPGCaptureInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void InitializeCapture();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void StartCapture();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void EndCapture();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void AttachToCapture(const FRPGItemData ItemData);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void DetachFromCapture(const FRPGItemData ItemData);

	virtual void AttachItem(const FRPGItemData ItemData) = 0;

	virtual void DetachItem(const FRPGItemData ItemData) = 0;
};
