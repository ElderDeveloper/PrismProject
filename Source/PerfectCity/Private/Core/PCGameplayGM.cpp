// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/PCGameplayGM.h"
#include "Core/PCGameplayPC.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerStart.h"

void APCGameplayGM::RequestPlayerRespawn(APCGameplayPC* PC)
{
	FTransform SpawnTransform = FTransform::Identity;
	if (AActor* PlayerStart = ChoosePlayerStart(PC))
	{
		SpawnTransform = PlayerStart->GetActorTransform();
	}
	AActor* Spawned = GetWorld()->SpawnActor(PC->GetPawn()->GetClass(), &SpawnTransform);
	if (ACharacter* Character = Cast<ACharacter>(Spawned))
	{
		PC->OnCharacterRespawned(Character);
	}
}

void APCGameplayGM::BeginPlay()
{
	Super::BeginPlay();
}
