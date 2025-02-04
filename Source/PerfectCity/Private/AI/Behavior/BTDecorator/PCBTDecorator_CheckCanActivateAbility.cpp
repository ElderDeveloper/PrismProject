// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Behavior/BTDecorator/PCBTDecorator_CheckCanActivateAbility.h"
#include "AIController.h"
#include "Character/PCCharacterBase.h"

UPCBTDecorator_CheckCanActivateAbility::UPCBTDecorator_CheckCanActivateAbility()
{
}

bool UPCBTDecorator_CheckCanActivateAbility::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,uint8* NodeMemory) const
{
	if (AAIController* AIController = Cast<AAIController>(OwnerComp.GetAIOwner()))
	{
		if (APCCharacterBase* AICharacter = Cast<APCCharacterBase>(AIController->GetPawn()))
		{
			return AICharacter->CanActivateAbility(AbilityToCheck);
		}
	}
	return false;
}
