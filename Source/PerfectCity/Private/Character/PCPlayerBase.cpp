// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PCPlayerBase.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "AbilitySystem/PCAbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "AbilitySystem/PCWeaponAttributeSet.h"
#include "Core/PCGameplayPC.h"


// Sets default values
APCPlayerBase::APCPlayerBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bUsePawnControlRotation = true;
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	WeaponAttributeSet = CreateDefaultSubobject<UPCWeaponAttributeSet>(TEXT("WeaponAttributeSet"));
}


void APCPlayerBase::PrimaryAttack(const FInputActionValue& InputActionValue)
{
}

void APCPlayerBase::SecondaryAttack(const FInputActionValue& InputActionValue)
{
}

void APCPlayerBase::PrimaryAbility(const FInputActionValue& InputActionValue)
{
}

void APCPlayerBase::CharacterDeath(const AActor* KilledBy)
{
	Super::CharacterDeath(KilledBy);

	if (const auto PC = Cast<APCGameplayPC>(GetController()))
	{
		PC->RequestRespawn();
		Destroy();
	}
}


void APCPlayerBase::BeginPlay()
{
	WeaponAttributeSet = PCAbilitySystemComponent->AddSet<UPCWeaponAttributeSet>();
	Super::BeginPlay();
}

void APCPlayerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void APCPlayerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APCPlayerBase::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APCPlayerBase::Look);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &APCPlayerBase::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &APCPlayerBase::StopJumping);
		EnhancedInputComponent->BindAction(PrimaryAttackAction, ETriggerEvent::Triggered, this, &APCPlayerBase::PrimaryAttack);
		EnhancedInputComponent->BindAction(SecondaryAttackAction, ETriggerEvent::Triggered, this, &APCPlayerBase::SecondaryAttack);
		EnhancedInputComponent->BindAction(PrimaryAbilityAction, ETriggerEvent::Triggered, this, &APCPlayerBase::PrimaryAbility);
	}
}

void APCPlayerBase::Move(const FInputActionValue& InputActionInstance)
{
	const FVector2D Direction = InputActionInstance.Get<FVector2D>();
	FVector Move =  GetActorForwardVector() * Direction.X 
	 				+ GetActorRightVector() * Direction.Y;
	AddMovementInput(Move);
}

void APCPlayerBase::Look(const FInputActionValue& InputActionValue)
{
	FVector2D LookAxis = InputActionValue.Get<FVector2D>();
	LookAxis.X = LookAxis.X * LookSensitivity * GetWorld()->GetDeltaSeconds();
	LookAxis.Y = LookAxis.Y * LookSensitivity * GetWorld()->GetDeltaSeconds();
	AddControllerPitchInput(LookAxis.Y * -1);
	AddControllerYawInput(LookAxis.X);
}