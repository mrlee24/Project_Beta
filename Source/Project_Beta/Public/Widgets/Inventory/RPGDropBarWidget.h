// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "RPGDropBarWidget.generated.h"

class URPGInventoryComponent;

UCLASS()
class PROJECT_BETA_API URPGDropBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	URPGInventoryComponent* InventoryComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	UBorder* Bar_Border;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	UButton* Drop_Button;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	UImage* Drop_Image;

protected:
	virtual void NativeConstruct() override;
};
