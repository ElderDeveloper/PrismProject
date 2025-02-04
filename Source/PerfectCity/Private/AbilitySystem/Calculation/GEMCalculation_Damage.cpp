// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Calculation/GEMCalculation_Damage.h"
#include "AbilitySystem/PCAttributeSet.h"

UGEMCalculation_Damage::UGEMCalculation_Damage()
{
	DefenseDef.AttributeToCapture = UPCAttributeSet::GetDefenseAttribute();
	DefenseDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	DefenseDef.bSnapshot = false;
	
	AttackDef.AttributeToCapture =  UPCAttributeSet::GetAttackAttribute();
	AttackDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	AttackDef.bSnapshot = false;
	
	CritChanceDef.AttributeToCapture = UPCAttributeSet::GetCritChanceAttribute();
	CritChanceDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	CritChanceDef.bSnapshot = false;
	
	CritDamageDef.AttributeToCapture = UPCAttributeSet::GetCritDamageAttribute();
	CritDamageDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	CritDamageDef.bSnapshot = false;
}

float UGEMCalculation_Damage::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float Defense = 0.0f;
	GetCapturedAttributeMagnitude(DefenseDef, Spec, EvaluationParameters, Defense);

	float Attack = 0.0f;
	GetCapturedAttributeMagnitude(AttackDef, Spec, EvaluationParameters, Attack);

	float CritChance = 0.0f;
	GetCapturedAttributeMagnitude(CritChanceDef, Spec, EvaluationParameters, CritChance);

	float CritDamage = 0.0f;
	GetCapturedAttributeMagnitude(CritDamageDef, Spec, EvaluationParameters, CritDamage);
	
	float DamageReduction = 1.0f - (Defense * 0.2 / 100.0f);
	DamageReduction = FMath::Clamp(DamageReduction, 0.1f, 1.0f); // Ensure at least 10% of the attack remains
	
	float BaseDamage = Attack * DamageReduction;
	float CritMultiplier = (FMath::FRand() <= CritChance) ? CritDamage : 1.0f;
	float TotalDamage = BaseDamage * CritMultiplier;
	
	return TotalDamage;
}




UGEMCalculation_DamageSnapshot::UGEMCalculation_DamageSnapshot()
{
	DefenseDef.AttributeToCapture = UPCAttributeSet::GetDefenseAttribute();
	DefenseDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	DefenseDef.bSnapshot = false;
	
	AttackDef.AttributeToCapture =  UPCAttributeSet::GetAttackAttribute();
	AttackDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	AttackDef.bSnapshot = true;
	
	CritChanceDef.AttributeToCapture = UPCAttributeSet::GetCritChanceAttribute();
	CritChanceDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	CritChanceDef.bSnapshot = false;
	
	CritDamageDef.AttributeToCapture = UPCAttributeSet::GetCritDamageAttribute();
	CritDamageDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	CritDamageDef.bSnapshot = false;
}

float UGEMCalculation_DamageSnapshot::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float Defense = 0.0f;
	GetCapturedAttributeMagnitude(DefenseDef, Spec, EvaluationParameters, Defense);

	float Attack = 0.0f;
	GetCapturedAttributeMagnitude(AttackDef, Spec, EvaluationParameters, Attack);

	float CritChance = 0.0f;
	GetCapturedAttributeMagnitude(CritChanceDef, Spec, EvaluationParameters, CritChance);

	float CritDamage = 0.0f;
	GetCapturedAttributeMagnitude(CritDamageDef, Spec, EvaluationParameters, CritDamage);
	
	float DamageReduction = 1.0f - (Defense * 0.2 / 100.0f);
	DamageReduction = FMath::Clamp(DamageReduction, 0.1f, 1.0f); // Ensure at least 10% of the attack remains
	
	float BaseDamage = Attack * DamageReduction;
	float CritMultiplier = (FMath::FRand() <= CritChance) ? CritDamage : 1.0f;
	float TotalDamage = BaseDamage * CritMultiplier;

	/*
		// Apply final lookup curve
		float FinalDamage = BaseDamage;
		const UCurveFloat* FinalLookupCurve = nullptr;
		Spec.GetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Effect.FinalLookupCurve")), false, FinalLookupCurve);
		if (FinalLookupCurve)
		{
			FinalDamage = FinalLookupCurve->GetFloatValue(BaseDamage);
		}
	 */
	
	return TotalDamage;
}
