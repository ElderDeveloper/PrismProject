// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "PCBTDecorator_CheckCanActivateAbility.generated.h"

class UGameplayAbility;
/**
 * 
 */
UCLASS()
class PERFECTCITY_API UPCBTDecorator_CheckCanActivateAbility : public UBTDecorator
{
	GENERATED_BODY()

public:

	UPCBTDecorator_CheckCanActivateAbility();

	UPROPERTY(EditAnywhere, Category = "Ability")
	TSubclassOf<UGameplayAbility> AbilityToCheck;

protected:

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
