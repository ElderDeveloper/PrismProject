// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PCAbilityInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UPCAbilityInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PERFECTCITY_API IPCAbilityInterface
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Ability")
	void ProjectileSpawnLocationRotation( FVector& SpawnLocation, FRotator& SpawnRotation);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Ability")
	UAnimMontage* GetDeathMontage() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Ability")
	UAnimMontage* GetHitMontage() const;
};
