// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "UObject/Object.h"
#include "GEMCalculation_Regen.generated.h"

#define DEFINE_ATTRIBUTE_VARIABLE(Name) float Name; GetCapturedAttributeMagnitude(Name##Def, Spec, EvaluationParameters, Name)


#define DEFINE_ATTRIBUTE_CAPTURE(Name, Source, Snapshot) \
Name##Def.AttributeToCapture = UPCAttributeSet::Get##Name##Attribute(); \
Name##Def.AttributeSource = EGameplayEffectAttributeCaptureSource::##Source; \
Name##Def.bSnapshot = Snapshot

UCLASS()
class PERFECTCITY_API UGEMCalculation_RegenHealth : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

	UGEMCalculation_RegenHealth();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

	FGameplayEffectAttributeCaptureDefinition HealthDef;
	FGameplayEffectAttributeCaptureDefinition MaxHealthDef;
	FGameplayEffectAttributeCaptureDefinition HealthRegenRateDef;
};


UCLASS()
class PERFECTCITY_API UGEMCalculation_RegenMana : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

	UGEMCalculation_RegenMana();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

	FGameplayEffectAttributeCaptureDefinition ManaDef;
	FGameplayEffectAttributeCaptureDefinition MaxManaDef;
	FGameplayEffectAttributeCaptureDefinition ManaRegenRateDef;
};



UCLASS()
class PERFECTCITY_API UGEMCalculation_RegenStamina : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

	UGEMCalculation_RegenStamina();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

	FGameplayEffectAttributeCaptureDefinition StaminaDef;
	FGameplayEffectAttributeCaptureDefinition MaxStaminaDef;
	FGameplayEffectAttributeCaptureDefinition StaminaRegenRateDef;
};


