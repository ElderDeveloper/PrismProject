// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "PCAbilityBase.generated.h"

/**
 * 
 */
UCLASS()
class PERFECTCITY_API UPCAbilityBase : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	virtual ACharacter* GetAvatarAsCharacter() const;

	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	
};
