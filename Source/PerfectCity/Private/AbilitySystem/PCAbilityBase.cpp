// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/PCAbilityBase.h"
#include "GameFramework/Character.h"

ACharacter* UPCAbilityBase::GetAvatarAsCharacter() const
{
	return Cast<ACharacter>(GetAvatarActorFromActorInfo());
}

bool UPCAbilityBase::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	return Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
}
