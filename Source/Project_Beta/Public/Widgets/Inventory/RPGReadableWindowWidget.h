// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "RPGTypes.h"
#include "RPGReadableWindowWidget.generated.h"

class URPGInventoryComponent;
class URPGInventoryOverallWidget;

UCLASS()
class PROJECT_BETA_API URPGReadableWindowWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	URPGInventoryComponent* InventoryComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	UImage* Background_Image;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	UBorder* ReadableWindow_Border;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	UButton* Back_Button;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	UImage* Item_Image;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	UImage* Button_Image;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	UImage* Dark_Image;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	UImage* Line_Image;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	UScrollBox* Readable_SB;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	UTextBlock* Readable_Text;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true"))
	TSet<FKey> ExitKeybindings;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true"))
	FRPGItemData ItemData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true"))
	bool bGamepadControls;
	
protected:
	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ToggleGamepadInputs();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void PlayAnim();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void CloseWindow();
};
