// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RPGTypes.h"
#include "Interfaces/RPGPlayerCharacterInterface.h"
#include "RPGAttributeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_BETA_API URPGAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

	//IRPGPlayerCharacterInterface PlayerRefInterface;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player", meta = (AllowPrivateAccess = "true"))
	TArray<FRPGAttributeRow> AttributeSet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player", meta = (AllowPrivateAccess = "true"))
	TArray<FRPGStatRow> Stats;

private:
	void FindStatInStatsArray(const EStatCategory InStat, bool& bFound, FRPGStatRow& OutStatRow) const;

public:	
	// Sets default values for this component's properties
	URPGAttributeComponent();

	UFUNCTION(BlueprintCallable)
	float ClampToMaxStatValues(const EStatCategory InStat, const float InValue = 0) const;

	UFUNCTION(BlueprintCallable)
	int32 GetStatIndex(const EStatCategory Stat) const;

	UFUNCTION(BlueprintCallable)
	float GetStatValue(const EStatCategory Stat) const;

	UFUNCTION(BlueprintCallable)
	void SetStatValue(const EStatCategory Stat, const float Value = 0.f);

	UFUNCTION(BlueprintCallable)
	void AddItemStats(const FRPGItemData ItemData);

	UFUNCTION(BlueprintCallable)
	void RemoveItemStats(const FRPGItemData ItemData);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};
