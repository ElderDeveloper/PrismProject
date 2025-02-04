// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/Async/PCWaitGameplayTagChangeOnActor.h"


UPCWaitGameplayTagChangeOnActor* UPCWaitGameplayTagChangeOnActor::WaitGameplayTagChangedOnActor(AActor* TargetActor, FGameplayTag Tag, bool OnlyTriggerOnce)
{
	UPCWaitGameplayTagChangeOnActor* MyObj = NewObject<UPCWaitGameplayTagChangeOnActor>();
	MyObj->SetAbilityActor(TargetActor);
	MyObj->Tag = Tag;
	MyObj->OnlyTriggerOnce = OnlyTriggerOnce;
	MyObj->TargetCount = 1;
	return MyObj;
}

void UPCWaitGameplayTagChangeOnActor::Activate()
{
	Super::Activate();
}

void UPCWaitGameplayTagChangeOnActor::BroadcastDelegate()
{
	Super::BroadcastDelegate();
	Changed.Broadcast(GameplayTagExists);
}

void UPCWaitGameplayTagChangeOnActor::GameplayTagCallback(const FGameplayTag NewTag, int32 NewCount)
{
	GameplayTagExists = NewCount > 0;
	if (ShouldBroadcastDelegates())
	{
		BroadcastDelegate();
		if (OnlyTriggerOnce)
		{
			EndAction();
		}
	}
	else
	{
		EndAction();
	}
}
