// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "RPGDragAndDropWidget.generated.h"

UCLASS()
class PROJECT_BETA_API URPGDragAndDropWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	UImage* Dragable_Image;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	UImage* DropSlot_Image;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	UImage* SwapSlot_Image;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	UImage* WrongSlot_Image;
};
