// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/PCGameplayPC.h"

#include "EnhancedInputSubsystems.h"
#include "Core/PCGameplayGM.h"
#include "GameFramework/Character.h"


void APCGameplayPC::RequestRespawn_Implementation()
{
	if ( const auto GM = GetWorld()->GetAuthGameMode<APCGameplayGM>() )
	{
		GM->RequestPlayerRespawn(this);
	}
}

void APCGameplayPC::OnCharacterRespawned(ACharacter* RespawnedCharacter)
{
	if (RespawnedCharacter)
	{
		if (GetPawn())
		{
			GetPawn()->Destroy();
		}
		Possess(RespawnedCharacter);
	}
}


void APCGameplayPC::BeginPlay()
{
	Super::BeginPlay();

	if (const auto EnhancedInputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		EnhancedInputSubsystem->AddMappingContext(InputMappingContext,0);
	}

}
