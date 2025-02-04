// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Actors/PCWeaponProjectileBase.h"
#include "NiagaraComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
APCWeaponProjectileBase::APCWeaponProjectileBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	ProjectileMesh->SetupAttachment(Root);

	ProjectileFX = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ProjectileFX"));
	ProjectileFX->SetupAttachment(Root);



	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
}

// Called when the game starts or when spawned
void APCWeaponProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
}

