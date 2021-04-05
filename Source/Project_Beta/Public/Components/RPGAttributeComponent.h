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

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Player", meta = (AllowPrivateAccess = "true"))
	TArray<FRPGStatRow> StatModifiers;

private:
	void FindStatInStatsArray(const EStatCategory InStat, bool& bFound, FRPGStatRow& OutStatRow) const;

public:	
	// Sets default values for this component's properties
	URPGAttributeComponent();

	UFUNCTION(BlueprintCallable)
	void AddModifier(const EStatCategory Index, const int32 Modifier, bool& bIsAdded);

	UFUNCTION(BlueprintCallable)
	void RemoveModifier(const EStatCategory Index, const int32 Modifier, bool& bIsRemoved);

	UFUNCTION(BlueprintCallable)
	int32 ClampToMaxStatValues(const EStatCategory InStat, const int32 InValue = 0) const;

	UFUNCTION(BlueprintCallable)
	int32 GetStatIndex(const EStatCategory Stat) const;

	UFUNCTION(BlueprintCallable)
	float GetStatValue(const EStatCategory Stat) const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};
