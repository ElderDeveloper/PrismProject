// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Behavior/BTTask/PCBTTask_FindLocationInRange.h"

#include "AI/PCAICharacterBase.h"
#include "AI/PCAIControllerBase.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UPCBTTask_FindLocationInRange::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (const auto AIController = Cast<APCAIControllerBase>(OwnerComp.GetAIOwner()))
	{
		if (const auto AICharacter =Cast<APCAICharacterBase>(AIController->GetPawn()))
		{
			if (AICharacter->GetTargetActor())
			{
				FVector TargetLocation = AICharacter->GetTargetActor()->GetActorLocation();
				FVector OriginLocation = AICharacter->GetActorLocation();
				
				FVector Direction = (OriginLocation - TargetLocation).GetSafeNormal();
				float RandomDistance = AICharacter->GetRandomDistanceInRange();
				FVector NewPosition = TargetLocation + (Direction * RandomDistance);

				// add some random offset
				float RandomAngle = FMath::RandRange(0.f, 360.f);
				FVector Offset = FVector(FMath::Cos(FMath::DegreesToRadians(RandomAngle)), 
										 FMath::Sin(FMath::DegreesToRadians(RandomAngle)), 
										 0.f) * 100.f;
				NewPosition += Offset;
				OwnerComp.GetBlackboardComponent()->SetValueAsVector(TargetLocationKey.SelectedKeyName, NewPosition);
			}
		}
	}





	return EBTNodeResult::Succeeded;
}
