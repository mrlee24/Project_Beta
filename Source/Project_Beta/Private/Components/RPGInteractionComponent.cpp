// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/RPGInteractionComponent.h"
#include "Components/RPGInventoryComponent.h"
#include "Components/RPGInteractableComponent.h"
#include "Characters/RPGPlayerCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Camera/CameraComponent.h"
#include "Libraries/RPGInventoryFunctionLibrary.h"

// Sets default values for this component's properties
URPGInteractionComponent::URPGInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void URPGInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayerInterfaceRef = Cast<IRPGPlayerCharacterInterface>(URPGInventoryFunctionLibrary::GetPlayerReference());
	InventoryComponent = URPGInventoryFunctionLibrary::GetInventoryComponent();
}

void URPGInteractionComponent::CheckPlayerIsInInteractableArea(URPGInteractableComponent* LInteractable)
{
	if (!LInteractable->GetInteractableArea() || LInteractable->GetInteractableArea()->IsOverlappingActor(URPGInventoryFunctionLibrary::GetPlayerReference()))
		PlayerAlreadyHighlightsActor();

	AssignInteractionToLocal(LInteractable);
}

void URPGInteractionComponent::PlayerAlreadyHighlightsActor()
{
	if (!CurrentInteractable) return;

	if (!CurrentInteractable->GetInteractableArea() || !CurrentInteractable->GetInteractableArea()->IsOverlappingActor(URPGInventoryFunctionLibrary::GetPlayerReference()))
		RemoveInteractionFromCurrent();
}

void URPGInteractionComponent::ToggleInteractionTimer(const bool bOnOff)
{
	if (bOnOff)
	{
		GetWorld()->GetTimerManager().SetTimer
		(
			InteractionHandle,
			[this] { UpdateInteraction(); },
			0.1f,
			true
		);
		return;
	}

	GetWorld()->GetTimerManager().ClearTimer(InteractionHandle);

	CheckCurrentInteractableIsHighlighted();
}

void URPGInteractionComponent::UpdateInteraction()
{
	FVector StartVector = UKismetMathLibrary::Add_VectorVector(Cast<USceneComponent>(PlayerInterfaceRef->GetSkeletalMesh())->GetComponentLocation(), FVector(0.f, 0.f, 210.f));
	FVector EndVector = UKismetMathLibrary::Multiply_VectorFloat(Cast<USceneComponent>(PlayerInterfaceRef->GetCameraComponent())->GetForwardVector(), 5000.f);

	FHitResult OutHit;
	TArray<AActor*> ActorsToIgnore;

	const bool bIsHit = UKismetSystemLibrary::CapsuleTraceSingle
	(
		GetWorld(),
		StartVector,
		StartVector + EndVector,
		35.f,
		0.f,
		ETraceTypeQuery::TraceTypeQuery3,
		bTraceComplex,
		ActorsToIgnore,
		EDrawDebugTrace::Type::ForDuration,
		OutHit,
		true,
		TraceColor,
		TraceHitColor,
		DrawTime
	);

	if (!bIsHit || !OutHit.Actor->FindComponentByClass<URPGInteractableComponent>() || !OutHit.Actor->FindComponentByClass<URPGInteractableComponent>()->GetIsInteractable())
	{
		PlayerAlreadyHighlightsActor();
		return;
	}

	URPGInteractableComponent* LInteractable = OutHit.Actor->FindComponentByClass<URPGInteractableComponent>();

	CheckPlayerIsInInteractableArea(LInteractable);
}

void URPGInteractionComponent::RemoveInteractionFromCurrent()
{
	if (CurrentInteractable)
	{
		CurrentInteractable->ToggleHighlight(false);

		/*if (InventoryComponent->bIsItemsBarOpen)
			InventoryComponent->RemoveItemsBar();
		CurrentInteractable = nullptr;
		InventoryComponent->CurrentInteractable = nullptr;*/
	}
}

void URPGInteractionComponent::AssignInteractionToLocal(class URPGInteractableComponent* LInteractable)
{
	if (CurrentInteractable)
		CurrentInteractable->ToggleHighlight(false);

	LInteractable->ToggleHighlight(true);
	CurrentInteractable = LInteractable;
	//InventoryComponent->SetCurrentInteractable(CurrentInteractable);
}

void URPGInteractionComponent::CheckCurrentInteractableIsHighlighted()
{
	if (!CurrentInteractable) return;

	if (CurrentInteractable)
	{
		if (CurrentInteractable->GetInteractableArea())
		{
			if (CurrentInteractable->GetInteractableArea()->IsOverlappingActor(URPGInventoryFunctionLibrary::GetPlayerReference()))
				return;
		}

		RemoveInteractionFromCurrent();
		return;
	}
}

