// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "PCWeaponAttributeSet.generated.h"


#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class PERFECTCITY_API UPCWeaponAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Damage)
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UPCWeaponAttributeSet, Damage)
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_FireRate)
	FGameplayAttributeData FireRate;
	ATTRIBUTE_ACCESSORS(UPCWeaponAttributeSet, FireRate)
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_ClipSize)
	FGameplayAttributeData ClipSize;
	ATTRIBUTE_ACCESSORS(UPCWeaponAttributeSet, ClipSize)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Ammo)
	FGameplayAttributeData Ammo;
	ATTRIBUTE_ACCESSORS(UPCWeaponAttributeSet, Ammo)


	UFUNCTION()
	virtual void OnRep_Damage(const FGameplayAttributeData& OldDamage);
	UFUNCTION()
	virtual void OnRep_FireRate(const FGameplayAttributeData& OldFireRate);
	UFUNCTION()
	virtual void OnRep_ClipSize(const FGameplayAttributeData& OldClipSize);
	UFUNCTION()
	virtual void OnRep_Ammo(const FGameplayAttributeData& OldAmmo);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	
};
