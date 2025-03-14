// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PCWeaponProjectileBase.generated.h"

class UProjectileMovementComponent;
class UNiagaraComponent;
class USceneComponent;

UCLASS()
class PERFECTCITY_API APCWeaponProjectileBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APCWeaponProjectileBase();

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	USceneComponent* Root;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	UNiagaraComponent* ProjectileFX;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	UProjectileMovementComponent* ProjectileMovement;

	virtual void BeginPlay() override;
};
