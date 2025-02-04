// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "PCCharacterBase.h"
#include "PCPlayerBase.generated.h"

class UPCWeaponAttributeSet;
class UCameraComponent;
class USpringArmComponent;
class UInputMappingContext;
class UInputAction;

UCLASS()
class PERFECTCITY_API APCPlayerBase : public APCCharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APCPlayerBase();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* SpringArm;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	UCameraComponent* Camera;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	float LookSensitivity = 45.0f;

	UFUNCTION(BlueprintPure, Category = "Weapon")
	const UPCWeaponAttributeSet* GetWeaponAttributeSet() const { return WeaponAttributeSet; }

protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	const UPCWeaponAttributeSet* WeaponAttributeSet;
	
	void Move(const FInputActionValue& InputActionInstance);
	void Look(const FInputActionValue& InputActionValue);
	void PrimaryAttack(const FInputActionValue& InputActionValue);
	void SecondaryAttack(const FInputActionValue& InputActionValue);
	void PrimaryAbility(const FInputActionValue& InputActionValue);

	virtual void CharacterDeath(const AActor* KilledBy) override;
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* LookAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* JumpAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* PrimaryAttackAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* SecondaryAttackAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* PrimaryAbilityAction;
};


