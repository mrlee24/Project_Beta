// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RPGInventoryWidgetInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class URPGInventoryWidgetInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECT_BETA_API IRPGInventoryWidgetInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ToggleGamepadInputs();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void PlayAnim();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void StopAnim();
};
