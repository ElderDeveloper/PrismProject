// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PCCharacterBase.h"
#include "AbilitySystem/PCAbilitySystemComponent.h"
#include "AbilitySystem/PCAttributeSet.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameplayEffectExtension.h"


// Sets default values
APCCharacterBase::APCCharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PCAbilitySystemComponent = CreateDefaultSubobject<UPCAbilitySystemComponent>(TEXT("PCAbilitySystemComponent"));
	PCAbilitySystemComponent->SetIsReplicated(true);
	PCAbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	//PCAttributeSet = CreateDefaultSubobject<UPCAttributeSet>(TEXT("PCAttributeSet"));
	 
}

void APCCharacterBase::ControlSpeedAttribute()
{
	bool found;
	auto Attribute = PCAttributeSet->GetSpeedAttribute();
	float SpeedAttribute = PCAbilitySystemComponent->GetGameplayAttributeValue(Attribute, found);
	GetCharacterMovement()->MaxWalkSpeed = SpeedAttribute;
	
	auto& Delegate = PCAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute);
	Delegate.AddWeakLambda(this, [this](auto)
	{
		GetCharacterMovement()->MaxWalkSpeed = PCAttributeSet->GetSpeed();
	});
}

void APCCharacterBase::ControlHealthAttribute()
{
	auto Attribute = PCAttributeSet->GetHealthAttribute();
	auto& HealthDelegate = PCAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute);

	HealthDelegate.AddWeakLambda(this, [this](const FOnAttributeChangeData& Data)
	{
		if (Data.GEModData && Data.GEModData->EffectSpec.GetContext().GetOriginalInstigator())
		{
			LastAttacker = Data.GEModData->EffectSpec.GetContext().GetOriginalInstigator();
		}
		OnTakeHealthDamage(Data.OldValue - Data.NewValue, Data.NewValue);
		
		if (PCAttributeSet->GetHealth() <= 0)
		{
			if (GetAbilitySystemComponent()->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag("Gameplay.Character.State.Dead")))
			{
				return;
			}
			GetAbilitySystemComponent()->AddLooseGameplayTag(FGameplayTag::RequestGameplayTag("Gameplay.Character.State.Dead"));
			CharacterDeath(LastAttacker);
		}
	});
}

void APCCharacterBase::CharacterDeath(const AActor* KilledBy)
{
	GetCharacterMovement()->DisableMovement();
	GetCharacterMovement()->StopMovementImmediately();
	GetCharacterMovement()->SetComponentTickEnabled(false);
	OnCharacterKilled.Broadcast(KilledBy, this);
}

void APCCharacterBase::OnTakeHealthDamage(float Damage, float CurrentHealth)
{
	OnCharacterTookDamage.Broadcast(Damage,CurrentHealth, GetLastAttacker()); 
}

// Called when the game starts or when spawned
void APCCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	PCAttributeSet = PCAbilitySystemComponent->AddSet<UPCAttributeSet>();
	PCAbilitySystemComponent->InitAbilityActorInfo(this, this);

	ControlSpeedAttribute();
	ControlHealthAttribute();
}

void APCCharacterBase::ProjectileSpawnLocationRotation_Implementation(FVector& SpawnLocation, FRotator& SpawnRotation)
{
	IPCAbilityInterface::ProjectileSpawnLocationRotation_Implementation(SpawnLocation, SpawnRotation);
	SpawnLocation = GetActorLocation();
	SpawnRotation = GetActorRotation();
}

UAnimMontage* APCCharacterBase::GetDeathMontage_Implementation() const
{
	return DeathMontage;
}

UAnimMontage* APCCharacterBase::GetHitMontage_Implementation() const
{
	return HitMontage;
}

UAbilitySystemComponent* APCCharacterBase::GetAbilitySystemComponent() const
{
	return PCAbilitySystemComponent;
}

const UAttributeSet* APCCharacterBase::GetPCAttributeSet() const
{
	return PCAttributeSet;
}

bool APCCharacterBase::CanActivateAbility(const TSubclassOf<UGameplayAbility>& AbilityToActivate) const
{
	if (FGameplayAbilitySpec* Spec = GetAbilitySystemComponent()->FindAbilitySpecFromClass(AbilityToActivate))
	{
		return Spec->Ability->CanActivateAbility(Spec->Handle, GetAbilitySystemComponent()->AbilityActorInfo.Get(), nullptr, nullptr, nullptr);
	}
	return false;
}

bool APCCharacterBase::CanActivateAbilityByTag(const FGameplayTag& AbilityTag) const
{
	FGameplayTagContainer TagContainer = FGameplayTagContainer(AbilityTag);
	TArray<FGameplayAbilitySpecHandle> Specs;
	GetAbilitySystemComponent()->FindAllAbilitiesWithTags(Specs, TagContainer);
	bool bCanActivate = false;
	for (const auto& SpecHandle : Specs)
	{
		if (FGameplayAbilitySpec* Spec = GetAbilitySystemComponent()->FindAbilitySpecFromHandle(SpecHandle))
		{
			if (Spec->Ability->CanActivateAbility(Spec->Handle, GetAbilitySystemComponent()->AbilityActorInfo.Get(), nullptr, nullptr, nullptr))
			{
				bCanActivate = true;
			}
		}
	}
	return bCanActivate;
}

