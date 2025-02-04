// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "PCAIControllerBase.generated.h"

UCLASS()
class PERFECTCITY_API APCAIControllerBase : public AAIController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APCAIControllerBase();

protected:
	void OnPossess(APawn* InPawn) override;
	virtual void BeginPlay() override;

};
