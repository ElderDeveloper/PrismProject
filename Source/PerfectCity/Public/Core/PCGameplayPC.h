// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PCGameplayPC.generated.h"

/**
 * 
 */
UCLASS()
class PERFECTCITY_API APCGameplayPC : public APlayerController
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	class UInputMappingContext* InputMappingContext;

	UFUNCTION(Server, Reliable)
	void RequestRespawn();
	void OnCharacterRespawned(ACharacter* RespawnedCharacter);

	virtual void BeginPlay() override;
};

