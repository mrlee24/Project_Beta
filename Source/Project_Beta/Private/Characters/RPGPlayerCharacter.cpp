// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/RPGPlayerCharacter.h"
#include "Components/RPGInventoryComponent.h"
#include "Components/RPGInteractionComponent.h"

// Sets default values
ARPGPlayerCharacter::ARPGPlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Tags.Add(TEXT("Player"));

	SK_Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Character Mesh"));
	SK_Mesh->SetupAttachment(GetMesh());

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Main Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	InventoryComponent = CreateDefaultSubobject<URPGInventoryComponent>(TEXT("AC_Inventory"));
	InteractionComponent = CreateDefaultSubobject<URPGInteractionComponent>(TEXT("AC_Interaction"));
}

// Called when the game starts or when spawned
void ARPGPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}
