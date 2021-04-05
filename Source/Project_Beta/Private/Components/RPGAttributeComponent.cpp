// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/RPGAttributeComponent.h"
#include "Libraries/RPGInventoryFunctionLibrary.h"
#include "Kismet/KismetMathLibrary.h"

void URPGAttributeComponent::FindStatInStatsArray(const EStatCategory InStat, bool& bFound, FRPGStatRow& OutStatRow) const
{
	const int32 StatIndex = GetStatIndex(InStat);

	if (StatIndex != -1)
	{
		bFound = true;
		OutStatRow = Stats[StatIndex];
		return;
	}

	bFound = false;
}

// Sets default values for this component's properties
URPGAttributeComponent::URPGAttributeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


void URPGAttributeComponent::AddModifier(const EStatCategory Index, const int32 Modifier, bool& bIsAdded)
{
	if (Modifier == 0) return;

	FRPGStatRow NewRow = { Index, Modifier };
	StatModifiers.Add(NewRow);
	bIsAdded = true;
}

void URPGAttributeComponent::RemoveModifier(const EStatCategory Index, const int32 Modifier, bool& bIsRemoved)
{
	if (Modifier == 0) return;

	FRPGStatRow RowToBeRemoved = { Index, Modifier };
	StatModifiers.Remove(RowToBeRemoved);
	StatModifiers.Shrink();
	bIsRemoved = true;
}

int32 URPGAttributeComponent::ClampToMaxStatValues(const EStatCategory InStat, const int32 InValue /*= 0.f*/) const
{
	if (InStat == EStatCategory::Health || InStat == EStatCategory::Stamina || InStat == EStatCategory::Mana)
	{
		float MaxStatValue = 0.f;
		switch (InStat)
		{
		case EStatCategory::Health:
			MaxStatValue = GetStatValue(EStatCategory::MaxHealth);
			break;

		case EStatCategory::Stamina:
			MaxStatValue = GetStatValue(EStatCategory::MaxStamina);
			break;

		case EStatCategory::Mana:
			MaxStatValue = GetStatValue(EStatCategory::MaxMana);
			break;

		default:
			MaxStatValue = 0.f;
			break;
		}

		return UKismetMathLibrary::Clamp(InValue, 0.f, MaxStatValue);
	}

	return InValue;
}

int32 URPGAttributeComponent::GetStatIndex(const EStatCategory Stat) const
{
	bool bFound = false;
	int32 StatIndex = -1;
	URPGInventoryFunctionLibrary::FindItemStat(Stats, Stat, bFound, StatIndex);

	return (bFound) ? StatIndex : -1;
}

float URPGAttributeComponent::GetStatValue(const EStatCategory Stat) const
{
	bool bFound = false;
	FRPGStatRow OutStatRow;
	FindStatInStatsArray(Stat, bFound, OutStatRow);

	return (bFound) ? OutStatRow.Value : 0.f;
}

// Called when the game starts
void URPGAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}
