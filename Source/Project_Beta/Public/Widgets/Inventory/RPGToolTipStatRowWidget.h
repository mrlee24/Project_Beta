// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RPGTypes.h"
#include "Components/TextBlock.h"
#include "RPGToolTipStatRowWidget.generated.h"

UCLASS()
class PROJECT_BETA_API URPGToolTipStatRowWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	UTextBlock* ComparisonValue_Text;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	UTextBlock* StatName_Text;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	UTextBlock* StatValue_Text;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true"))
	FRPGStatRow StatRow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true"))
	FText StatName = FText::FromString("StatName");

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true"))
	float ComparisonValue;

protected:
	virtual void NativePreConstruct() override;

public:
	UTextBlock* GetComparisonValue_Text() const { return ComparisonValue_Text; }
	void SetComparisonValue_Text(UTextBlock* InComparisonValue_Text) { ComparisonValue_Text = InComparisonValue_Text; }

	float GetComparisonValue() const { return ComparisonValue; }
	void SetComparisonValue(float InComparisonValue) { ComparisonValue = InComparisonValue; }

	FRPGStatRow GetStatRow() const { return StatRow; }
	void SetStatRow(FRPGStatRow InStatRow) { StatRow = InStatRow; }
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetItemValue(const float Value);

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FText UpdateComparisonValue() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FSlateColor UpdateComparisonColor() const;
};
