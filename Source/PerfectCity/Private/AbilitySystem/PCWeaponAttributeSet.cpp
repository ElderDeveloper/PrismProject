// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/PCWeaponAttributeSet.h"

#include "Net/UnrealNetwork.h"


void UPCWeaponAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UPCWeaponAttributeSet, Damage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPCWeaponAttributeSet, FireRate, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPCWeaponAttributeSet, ClipSize, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPCWeaponAttributeSet, Ammo, COND_None, REPNOTIFY_Always);
}

void UPCWeaponAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
}

void UPCWeaponAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	
	if (Attribute == GetAmmoAttribute())
	{
		NewValue = FMath::Clamp<float>(NewValue, 0.0f, GetClipSize());
	}
}


void UPCWeaponAttributeSet::OnRep_Damage(const FGameplayAttributeData& OldDamage)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPCWeaponAttributeSet, Damage, OldDamage);
}

void UPCWeaponAttributeSet::OnRep_FireRate(const FGameplayAttributeData& OldFireRate)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPCWeaponAttributeSet, FireRate, OldFireRate);
}

void UPCWeaponAttributeSet::OnRep_ClipSize(const FGameplayAttributeData& OldClipSize)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPCWeaponAttributeSet, ClipSize, OldClipSize);
}

void UPCWeaponAttributeSet::OnRep_Ammo(const FGameplayAttributeData& OldAmmo)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPCWeaponAttributeSet, Ammo, OldAmmo);
}
