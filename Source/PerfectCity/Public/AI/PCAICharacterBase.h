// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/PCCharacterBase.h"
#include "PCAICharacterBase.generated.h"

class UGameplayEffect;
class UBoxComponent;
class UBehaviorTree;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTargetActorChanged, AActor*, NewTargetActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnterMinMaxDistance, float, CurrentDistanceToTarget);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnExitMinMaxDistance, float, CurrentDistanceToTarget);

UCLASS()
class PERFECTCITY_API APCAICharacterBase : public APCCharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APCAICharacterBase();

	// Will be used in trace for it's location and BoxExtent
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AI")
	UBoxComponent* MeleeDamageZone;
	
	UPROPERTY(BlueprintAssignable, Category = "AI")
	FOnTargetActorChanged OnTargetActorChanged;

	UPROPERTY(BlueprintAssignable, Category = "AI")
	FOnEnterMinMaxDistance OnEnterMinMaxDistance;

	UPROPERTY(BlueprintAssignable, Category = "AI")
	FOnExitMinMaxDistance OnExitMinMaxDistance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI|Behavior" )
	UBehaviorTree* AIBehaviorTree;
	
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI|Death")
	TSubclassOf<UGameplayAbility> DeathAbility;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI|Death")
	TArray<TSubclassOf<UGameplayEffect>> ApplyEffectsToKiller;

	UPROPERTY(ReplicatedUsing=OnRep_TargetActor, BlueprintReadOnly, Category = "AI|Target")
	AActor* TargetActor = nullptr;

	UFUNCTION()
	void OnRep_TargetActor();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI|Distance")
	float MinDistanceToTarget = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI|Distance")
	float MaxDistanceToTarget = 1000.0f;
	
	float DistanceToTarget = 0.0f;
	FTimerHandle DistanceToTargetTimerHandle;
	bool bIsTargetInRange = false;
	void CalculateDistanceToTarget();
	virtual void OnTargetRangeChanged(bool bIsInRange) {}
	
	virtual void CharacterDeath(const AActor* KilledBy) override;
	virtual void OnTakeHealthDamage(float Damage, float CurrentHealth) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
public:

	UFUNCTION(BlueprintCallable, Category = "AI|Target")
	void SetTargetActor(AActor* NewTargetActor, bool bWarnOthers = false);

	UFUNCTION(BlueprintPure, Category = "AI|Target")
	AActor* GetTargetActor() const;
	
	UFUNCTION(BlueprintPure, Category = "AI|Distance")
	float GetDistanceToTarget() const;

	UFUNCTION(BlueprintPure, Category = "AI|Distance")
	bool IsTargetInRange() const { return bIsTargetInRange; }

	UFUNCTION(BlueprintPure, Category = "AI|Distance")
	float GetMinDistanceToTarget() const { return MinDistanceToTarget; }

	UFUNCTION(BlueprintPure, Category = "AI|Distance")
	float GetMaxDistanceToTarget() const { return MaxDistanceToTarget; }

	UFUNCTION(BlueprintPure, Category = "AI|Distance")
	float GetRandomDistanceInRange() const;
};
