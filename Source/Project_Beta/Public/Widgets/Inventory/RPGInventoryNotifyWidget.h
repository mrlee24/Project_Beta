// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "RPGInventoryNotifyWidget.generated.h"

UCLASS()
class PROJECT_BETA_API URPGInventoryNotifyWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true"))
	FText Message;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	UImage* Background_Image;

protected:
	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void PlayAnim();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void StopAnim();

public:
	UFUNCTION(BlueprintCallable)
	FText UpdateMessage() const;
};
