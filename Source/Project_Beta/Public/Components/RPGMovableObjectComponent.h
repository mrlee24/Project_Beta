// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RPGMovableObjectComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMove);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnReverse);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStop);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFinished);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class PROJECT_BETA_API URPGMovableObjectComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(BlueprintAssignable)
	FOnMove OnMove;

	UPROPERTY(BlueprintAssignable)
	FOnMove OnReverse;

	UPROPERTY(BlueprintAssignable)
	FOnMove OnStop;

	UPROPERTY(BlueprintAssignable)
	FOnMove OnFinished;

public:	
	// Sets default values for this component's properties
	URPGMovableObjectComponent();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Move();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Reverse();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Stop();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Finished();

public:
	FOnMove GetOnMove() const { return OnMove; }
	FOnMove GetOnReverse() const { return OnReverse; }
	FOnMove GetOnStop() const { return OnStop; }
	FOnMove GetOnFinished() const { return OnFinished; }
};
