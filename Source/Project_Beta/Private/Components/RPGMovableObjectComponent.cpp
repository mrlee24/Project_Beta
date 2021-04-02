// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/RPGMovableObjectComponent.h"

// Sets default values for this component's properties
URPGMovableObjectComponent::URPGMovableObjectComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void URPGMovableObjectComponent::Move_Implementation()
{
	GetOnMove().Broadcast();
}

void URPGMovableObjectComponent::Reverse_Implementation()
{
	OnReverse.Broadcast();
}

void URPGMovableObjectComponent::Stop_Implementation()
{
	OnStop.Broadcast();
}

void URPGMovableObjectComponent::Finished_Implementation()
{
	OnFinished.Broadcast();
}

