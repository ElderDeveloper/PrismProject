// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "PCBTS_CalculateDistance.generated.h"

/**
 * 
 */
UCLASS()
class PERFECTCITY_API UPCBTS_CalculateDistance : public UBTService
{
	GENERATED_BODY()

public:

	UPCBTS_CalculateDistance();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Distance")
	FBlackboardKeySelector DistanceKey;

protected:

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
