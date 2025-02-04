// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Behavior/BTService/PCBTS_CalculateDistance.h"

#include "AIController.h"
#include "AI/PCAICharacterBase.h"
#include "BehaviorTree/BlackboardComponent.h"

UPCBTS_CalculateDistance::UPCBTS_CalculateDistance()
{
	bNotifyTick = true;
}

void UPCBTS_CalculateDistance::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (const auto AIComp = OwnerComp.GetAIOwner())
	{
		if (const auto AICharacter = Cast<APCAICharacterBase>(AIComp->GetPawn()))
		{
			AIComp->GetBlackboardComponent()->SetValueAsFloat(DistanceKey.SelectedKeyName, AICharacter->GetDistanceToTarget());
		}
	}
}
