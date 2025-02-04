// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/Calculation/GEMCalculation_Regen.h"
#include "AbilitySystem/PCAttributeSet.h"

UGEMCalculation_RegenHealth::UGEMCalculation_RegenHealth()
{
	DEFINE_ATTRIBUTE_CAPTURE(Health,Target,false);
	DEFINE_ATTRIBUTE_CAPTURE(MaxHealth,Source,true);
	DEFINE_ATTRIBUTE_CAPTURE(HealthRegenRate,Source,false);
}

float UGEMCalculation_RegenHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	DEFINE_ATTRIBUTE_VARIABLE(Health);
	DEFINE_ATTRIBUTE_VARIABLE(MaxHealth);
	DEFINE_ATTRIBUTE_VARIABLE(HealthRegenRate);

	return (MaxHealth - Health) * HealthRegenRate;
}


UGEMCalculation_RegenMana::UGEMCalculation_RegenMana()
{
	DEFINE_ATTRIBUTE_CAPTURE(Mana,Target,false);
	DEFINE_ATTRIBUTE_CAPTURE(MaxMana,Source,true);
	DEFINE_ATTRIBUTE_CAPTURE(ManaRegenRate,Source,false);
}


float UGEMCalculation_RegenMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
     
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;
     	
	DEFINE_ATTRIBUTE_VARIABLE(Mana);
	DEFINE_ATTRIBUTE_VARIABLE(MaxMana);
	DEFINE_ATTRIBUTE_VARIABLE(ManaRegenRate);
	 
	return (MaxMana - Mana) * ManaRegenRate;
}

UGEMCalculation_RegenStamina::UGEMCalculation_RegenStamina()
{
	DEFINE_ATTRIBUTE_CAPTURE(Stamina,Target,false);
	DEFINE_ATTRIBUTE_CAPTURE(MaxStamina,Source,true);
	DEFINE_ATTRIBUTE_CAPTURE(StaminaRegenRate,Source,false);
}


float UGEMCalculation_RegenStamina::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	 
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;
	 	
	DEFINE_ATTRIBUTE_VARIABLE(Stamina);
	DEFINE_ATTRIBUTE_VARIABLE(MaxStamina);
	DEFINE_ATTRIBUTE_VARIABLE(StaminaRegenRate);
	 
	return (MaxStamina - Stamina) * StaminaRegenRate;
}
