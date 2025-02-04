// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/Async/PCWaitAttributeChangedInterp.h"


UPCWaitAttributeChangedInterp* UPCWaitAttributeChangedInterp::WaitForAttributeChangedInterp(AActor* TargetActor,FGameplayAttribute Attribute, bool OnlyTriggerOnce, float InterpSpeed)
{
	UPCWaitAttributeChangedInterp* MyObj = NewObject<UPCWaitAttributeChangedInterp>();
	MyObj->SetAbilityActor(TargetActor);
	MyObj->AbilityActor = TargetActor;
	MyObj->InterpSpeed = InterpSpeed;
	MyObj->Attribute = Attribute;
	MyObj->OnlyTriggerOnce = OnlyTriggerOnce;
	return MyObj;
}

void UPCWaitAttributeChangedInterp::OnAttributeChangedStartInterp(FGameplayAttribute NewAttribute, float NewValue,float OldValue)
{
	CurrentAttribute = NewAttribute;
	Old = OldValue;
	New = NewValue;
	InterpValue = Old;
	InterpLoop.Broadcast(CurrentAttribute, New, Old,InterpValue);

	if (AbilityActor)
	{
		if (AbilityActor->GetWorld())
		{
			if (AbilityActor->GetWorld()->GetTimerManager().TimerExists(InterpTimerHandle))
			{
				AbilityActor->GetWorld()->GetTimerManager().ClearTimer(InterpTimerHandle);
			}
			AbilityActor->GetWorld()->GetTimerManager().SetTimer(InterpTimerHandle, this, &UPCWaitAttributeChangedInterp::Interp, 0.02f, true);
		}
	}
}

void UPCWaitAttributeChangedInterp::Interp()
{
	if (AbilityActor)
	{
		InterpValue = FMath::FInterpTo(InterpValue, New, AbilityActor->GetWorld()->GetDeltaSeconds(), InterpSpeed);
		InterpLoop.Broadcast(CurrentAttribute, New, Old, InterpValue);
		if (FMath::IsNearlyEqual(InterpValue, New, 0.01f))
		{
			if (AbilityActor->GetWorld())
			{
				AbilityActor->GetWorld()->GetTimerManager().ClearTimer(InterpTimerHandle);
			}
			if (OnlyTriggerOnce)
			{
				EndAction();
			}
		}
	}
	else
	{
		EndAction();
	}

}

void UPCWaitAttributeChangedInterp::Activate()
{
	Super::Activate();

	Changed.AddDynamic(this, &UPCWaitAttributeChangedInterp::OnAttributeChangedStartInterp);
}
