// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "GEMCalculation_Damage.generated.h"

/**
 * 
 */
UCLASS()
class PERFECTCITY_API UGEMCalculation_Damage : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:

	UGEMCalculation_Damage();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

	FGameplayEffectAttributeCaptureDefinition AttackDef;
	FGameplayEffectAttributeCaptureDefinition DefenseDef;
	FGameplayEffectAttributeCaptureDefinition CritChanceDef;
	FGameplayEffectAttributeCaptureDefinition CritDamageDef;
	
};


UCLASS()
class PERFECTCITY_API UGEMCalculation_DamageSnapshot : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:

	UGEMCalculation_DamageSnapshot();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

	FGameplayEffectAttributeCaptureDefinition AttackDef;
	FGameplayEffectAttributeCaptureDefinition DefenseDef;
	FGameplayEffectAttributeCaptureDefinition CritChanceDef;
	FGameplayEffectAttributeCaptureDefinition CritDamageDef;
	
};

