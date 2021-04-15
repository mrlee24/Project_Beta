// Fill out your copyright notice in the Description page of Project Settings.


#include "Captures/RPGItemCaptureBase.h"
#include "Engine/SkeletalMesh.h"

// Sets default values
ARPGItemCaptureBase::ARPGItemCaptureBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = SceneComponent;

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Component"));
	SkeletalMeshComponent->SetupAttachment(SceneComponent);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Component"));
	StaticMeshComponent->SetupAttachment(SceneComponent);

	SceneCaptureComponent2D = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("Scene Capture Component 2D"));
	SceneCaptureComponent2D->SetupAttachment(SceneComponent);

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	ArrowComponent->SetupAttachment(SceneCaptureComponent2D);

	SpotlightComponent = CreateDefaultSubobject<USpotLightComponent>(TEXT("Spot Light"));
	SpotlightComponent->SetupAttachment(SceneCaptureComponent2D);
}

void ARPGItemCaptureBase::AttachItem(const FRPGItemData ItemData)
{
	if (!ItemData.EquippableSkeletalMesh && !ItemData.EquippableStaticMesh) return;

	USkeletalMesh* LSkeletalMesh = ItemData.EquippableSkeletalMesh;
	UStaticMesh* LStaticMesh = ItemData.EquippableStaticMesh;

	if (LSkeletalMesh)
		SkeletalMeshComponent->SetSkeletalMesh(LSkeletalMesh); return;

	if (LStaticMesh)
		StaticMeshComponent->SetStaticMesh(LStaticMesh); return;

}

void ARPGItemCaptureBase::DetachItem(const FRPGItemData ItemData)
{
	SkeletalMeshComponent->SetSkeletalMesh(nullptr);
	StaticMeshComponent->SetStaticMesh(nullptr);
}

