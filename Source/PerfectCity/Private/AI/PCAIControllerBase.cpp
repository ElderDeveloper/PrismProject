// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/PCAIControllerBase.h"
#include "AI/PCAICharacterBase.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

// Sets default values
APCAIControllerBase::APCAIControllerBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APCAIControllerBase::BeginPlay()
{
	Super::BeginPlay();
}


void APCAIControllerBase::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (const auto AICharacter = Cast<APCAICharacterBase>(InPawn))
	{
		RunBehaviorTree(AICharacter->AIBehaviorTree);
		if(GetBlackboardComponent())
		{
			GetBlackboardComponent()->SetValueAsObject( "SelfActor", InPawn);
		}

	}
}

