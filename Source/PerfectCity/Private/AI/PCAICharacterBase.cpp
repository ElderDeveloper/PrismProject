// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/PCAICharacterBase.h"

#include "AbilitySystem/PCAbilitySystemComponent.h"
#include "AI/PCAIControllerBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/BoxComponent.h"
#include "Gameplay/Spawner/PCEnemySpawner.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"


// Sets default values
APCAICharacterBase::APCAICharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AIControllerClass = APCAIControllerBase::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	// Better visualize the melee damage zone
	MeleeDamageZone = CreateDefaultSubobject<UBoxComponent>(TEXT("MeleeDamageZone"));
	MeleeDamageZone->SetupAttachment(GetRootComponent());
	MeleeDamageZone->SetCollisionResponseToChannels(ECollisionResponse::ECR_Ignore);
	MeleeDamageZone->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
}

void APCAICharacterBase::OnRep_TargetActor()
{
	OnTargetActorChanged.Broadcast(TargetActor);
}

void APCAICharacterBase::CalculateDistanceToTarget()
{
	if (TargetActor)
	{
		DistanceToTarget = FVector::Dist(TargetActor->GetActorLocation(), GetActorLocation());

		if (bIsTargetInRange)
		{
			if (DistanceToTarget >= MaxDistanceToTarget || DistanceToTarget <= MinDistanceToTarget)
			{
				bIsTargetInRange = false;
				OnExitMinMaxDistance.Broadcast(DistanceToTarget);
				OnTargetRangeChanged(false);
			}
		}
		else
		{
			if (DistanceToTarget >= MinDistanceToTarget && DistanceToTarget <= MaxDistanceToTarget)
			{
				bIsTargetInRange = true;
				OnEnterMinMaxDistance.Broadcast(DistanceToTarget);
				OnTargetRangeChanged(true);
			}
		}
	}
}


void APCAICharacterBase::SetTargetActor(AActor* NewTargetActor, bool bWarnOthers)
{
	if (NewTargetActor != TargetActor && NewTargetActor != nullptr)
	{
		AActor* SelectedTarget = TargetActor;
		if (TargetActor)
		{
			float CurrentDistanceSquared = FVector::DistSquared(TargetActor->GetActorLocation(), GetActorLocation());
			float NewTargetDistanceSquared = FVector::DistSquared(NewTargetActor->GetActorLocation(), GetActorLocation());
			if (NewTargetDistanceSquared < CurrentDistanceSquared)
			{
				SelectedTarget = NewTargetActor;
			}
		}
		else
		{
			SelectedTarget = NewTargetActor;
		}

		if (AAIController* AIController = Cast<AAIController>(GetController()))
		{
			TargetActor = SelectedTarget;
			AIController->GetBlackboardComponent()->SetValueAsObject("TargetActor", TargetActor);
			OnTargetActorChanged.Broadcast(TargetActor);

			if (bWarnOthers)
			{
				if (const auto Spawner = Cast<APCEnemySpawner>(GetOwner()))
				{
					Spawner->WarnAllEnemies(Cast<APCAICharacterBase>(TargetActor));
				}
			}
		}
	}
}

void APCAICharacterBase::CharacterDeath(const AActor* KilledBy)
{
	Super::CharacterDeath(KilledBy);

	if (KilledBy)
	{
		if (const auto AbilityInterface = Cast<IAbilitySystemInterface>(KilledBy))
		{
			if (const auto AbilityComp = AbilityInterface->GetAbilitySystemComponent())
			{
				for (auto ApplyEffect : ApplyEffectsToKiller)
				{
					AbilityComp->ApplyGameplayEffectToSelf(ApplyEffect.GetDefaultObject(), 1, AbilityComp->MakeEffectContext());
				}
			}
		}
	}

	PCAbilitySystemComponent->TryActivateAbilityByClass(DeathAbility);
	
}

void APCAICharacterBase::OnTakeHealthDamage(float Damage, float CurrentHealth) 
{
	Super::OnTakeHealthDamage(Damage, CurrentHealth);
	SetTargetActor(GetLastAttacker(),true);
}

// Called when the game starts or when spawned
void APCAICharacterBase::BeginPlay()
{
	Super::BeginPlay();

	// Calculate distance to target every 0.2 seconds
	GetWorld()->GetTimerManager().SetTimer(DistanceToTargetTimerHandle, this, &APCAICharacterBase::CalculateDistanceToTarget, 0.2f, true);
	PCAbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(DeathAbility.GetDefaultObject(), 1, 0));
}

void APCAICharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APCAICharacterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APCAICharacterBase, TargetActor);
}

AActor* APCAICharacterBase::GetTargetActor() const
{
	return TargetActor;
}

float APCAICharacterBase::GetDistanceToTarget() const
{
	return DistanceToTarget;
}

float APCAICharacterBase::GetRandomDistanceInRange() const
{
	return FMath::RandRange(MinDistanceToTarget, MaxDistanceToTarget);
}
