// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "PCAbilitySystemComponent.generated.h"

USTRUCT(BlueprintType)
struct FAbilityClassWithInput
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UGameplayAbility> AbilityClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 AbilityLevel = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 InputId = -1;

	FGameplayAbilitySpec GetAbilitySpec() const
	{
		FGameplayAbilitySpec Spec(AbilityClass, AbilityLevel, InputId);
		return Spec;
	}
};


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PERFECTCITY_API UPCAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	UPCAbilitySystemComponent();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Starting Abilities")
	TArray<FAbilityClassWithInput> StartingAbilities;
	
	virtual void BeginPlay() override;

};
