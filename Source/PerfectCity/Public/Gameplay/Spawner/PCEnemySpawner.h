// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PCEnemySpawner.generated.h"

class APCCharacterBase;

USTRUCT(BlueprintType)
struct FSpawnRate
{
	GENERATED_BODY()


};

class USphereComponent;
class UBillboardComponent;
class APCAICharacterBase;

UCLASS()
class PERFECTCITY_API APCEnemySpawner : public APawn
{
	GENERATED_BODY()

public:
	APCEnemySpawner();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spawner")
	UBillboardComponent* SpawnZoneVisual;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spawner")
	USphereComponent* SpawnZone;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MinSpawnWaitDuration = 2.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MaxSpawnWaitDuration = 5.0f;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enemy Settings")
	TArray<TSubclassOf<APCAICharacterBase>> EnemyClasses;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enemy Settings")
	uint8 TotalEnemyCount = 10;

	UFUNCTION(BlueprintCallable)
	void WarnAllEnemies(APCCharacterBase* Target);

	UFUNCTION()
	void EnemyKilled(const AActor* Killer, const AActor* Victim);
	
	UFUNCTION(BlueprintCallable)
	void RequestEnemySpawn(bool bControlEnemyLimits = true);

	UFUNCTION(BlueprintCallable)
	void RequestDeleteEnemy(APCAICharacterBase* Enemy);

	UFUNCTION(BlueprintPure, Category = "Spawner")
	FVector GetRandomSpawnLocation() const;

	UFUNCTION(BlueprintPure, Category = "Spawner")
	AActor* GetRandomTargetActor() const;

protected:

	UPROPERTY(ReplicatedUsing=OnRep_SpawnedEnemies, BlueprintReadOnly, Category = "Spawner")
	TArray<APCAICharacterBase*> SpawnedEnemies;

	UFUNCTION()
	void OnRep_SpawnedEnemies();

	float PassedTime = 0.0f;
	float NextSpawnTime = 0.0f;

	FTimerHandle DirectorTimerHandle;
	void SpawnerTimer();
	void CheckSpawnedEnemies();
	
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

};
