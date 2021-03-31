// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RPGInteractableInterface.generated.h"

class URPGInteractableComponent;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class URPGInteractableInterface : public UInterface
{
	GENERATED_BODY()

};

class PROJECT_BETA_API IRPGInteractableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnInteraction();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnEndInteraction();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnRemoveInteraction();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnInitialize();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnGameLoad();
};