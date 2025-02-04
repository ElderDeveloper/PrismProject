// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PCGameplayGM.generated.h"


class APCGameplayPC;

UCLASS()
class PERFECTCITY_API APCGameplayGM : public AGameModeBase
{
	GENERATED_BODY()

public:

	virtual void RequestPlayerRespawn(APCGameplayPC* PC);

protected:
	virtual void BeginPlay() override;
};
