// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interfaces/PCAbilityInterface.h"
#include "PCCharacterBase.generated.h"

class UGameplayAbility;
class UPCAbilitySystemComponent;
class UPCAttributeSet;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnCharacterTookDamage, float, Damage, float, CurrentHealth, const AActor*, DamageCauser);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCharacterKilled,const AActor*, Killer, const AActor*, Victim);

UCLASS()
class PERFECTCITY_API APCCharacterBase : public ACharacter , public IAbilitySystemInterface , public IPCAbilityInterface
{
	GENERATED_BODY()

public:
	APCCharacterBase();

	UPROPERTY(BlueprintAssignable, Category = "Character")
	FOnCharacterTookDamage OnCharacterTookDamage;

	UPROPERTY(BlueprintAssignable, Category = "Character")
	FOnCharacterKilled OnCharacterKilled;

protected:
	UPROPERTY(BlueprintReadOnly,VisibleDefaultsOnly)
	UPCAbilitySystemComponent* PCAbilitySystemComponent;

	UPROPERTY(VisibleDefaultsOnly)
	const UPCAttributeSet* PCAttributeSet;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character")
	UAnimMontage* DeathMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character")
	UAnimMontage* HitMontage;
	
	virtual UAnimMontage* GetDeathMontage_Implementation() const override;
	virtual UAnimMontage* GetHitMontage_Implementation() const override;
	
	UPROPERTY()
	AActor* LastAttacker;

	void ControlSpeedAttribute();
	void ControlHealthAttribute();
	virtual void CharacterDeath(const AActor* KilledBy);;
	virtual void OnTakeHealthDamage(float Damage, float CurrentHealth);
	
	virtual void BeginPlay() override;
	virtual void ProjectileSpawnLocationRotation_Implementation(FVector& SpawnLocation, FRotator& SpawnRotation) override;


public:

	UFUNCTION(BlueprintPure, Category = "AbilitySystem")
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintPure, Category = "AbilitySystem")
	virtual const UAttributeSet* GetPCAttributeSet() const;

	UFUNCTION(BlueprintPure, Category = "AbilitySystem")
	bool CanActivateAbility(const TSubclassOf<UGameplayAbility>& AbilityToActivate) const;

	UFUNCTION(BlueprintPure, Category = "AbilitySystem")
	bool CanActivateAbilityByTag(const FGameplayTag& AbilityTag) const;

	UFUNCTION(BlueprintCallable, Category = "AbilitySystem")
	AActor* GetLastAttacker() const { return LastAttacker; }

};
