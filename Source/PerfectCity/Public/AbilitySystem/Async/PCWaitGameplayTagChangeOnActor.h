// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilities/Public/Abilities/Async/AbilityAsync_WaitGameplayTag.h"
#include "PCWaitGameplayTagChangeOnActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAsyncWaitGameplayTagChanged,bool, Added);

UCLASS()
class PERFECTCITY_API UPCWaitGameplayTagChangeOnActor : public UAbilityAsync_WaitGameplayTag
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FAsyncWaitGameplayTagChanged Changed;

	bool GameplayTagExists = false;
	/**
	 * Wait until the specified gameplay tag is Changed On Target Actor's ability component
	 * If the tag is already present when this task is started, it will immediately broadcast the Added event. It will keep listening as long as OnlyTriggerOnce = false.
	 * If used in an ability graph, this async action will wait even after activation ends. It's recommended to use WaitGameplayTagAdd instead.
	 */
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (DefaultToSelf = "TargetActor", BlueprintInternalUseOnly = "TRUE"))
	static UPCWaitGameplayTagChangeOnActor* WaitGameplayTagChangedOnActor(AActor* TargetActor, FGameplayTag Tag, bool OnlyTriggerOnce=false);

	virtual void Activate() override;
	
protected:
	
	virtual void BroadcastDelegate() override;
	virtual void GameplayTagCallback(const FGameplayTag NewTag, int32 NewCount) override;
};
