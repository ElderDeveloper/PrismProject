// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Async/AbilityAsync_WaitAttributeChanged.h"
#include "PCWaitAttributeChangedInterp.generated.h"

/**
 * 
 */
UCLASS()
class PERFECTCITY_API UPCWaitAttributeChangedInterp : public UAbilityAsync_WaitAttributeChanged
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (DefaultToSelf = "TargetActor", BlueprintInternalUseOnly = "TRUE"))
	static UPCWaitAttributeChangedInterp* WaitForAttributeChangedInterp(AActor* TargetActor, FGameplayAttribute Attribute, bool OnlyTriggerOnce = false , float InterpSpeed = 1.0f);


	DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FAsyncWaitAttributeChangedDelegateInterp, FGameplayAttribute, Attribute, float, NewValue,float, OldValue, float, InterpolatedValue);
	UPROPERTY(BlueprintAssignable)
	FAsyncWaitAttributeChangedDelegateInterp InterpLoop;

	
protected:

	UPROPERTY()
	AActor* AbilityActor;

	FTimerHandle InterpTimerHandle;

	FGameplayAttribute CurrentAttribute;
	float Old;
	float New;
	float InterpValue;
	float InterpSpeed = 1.0f;

	UFUNCTION()
	void OnAttributeChangedStartInterp(FGameplayAttribute NewAttribute, float NewValue,float OldValue);
	void Interp();
	virtual void Activate() override;
};
