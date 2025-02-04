// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Spawner/PCEnemySpawner.h"
#include "NavigationSystem.h"
#include "AI/NavigationSystemBase.h"
#include "AI/PCAICharacterBase.h"
#include "Components/BillboardComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"


// Sets default values
APCEnemySpawner::APCEnemySpawner()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnZoneVisual = CreateDefaultSubobject<UBillboardComponent>(TEXT("SpawnZoneVisual"));
	RootComponent = SpawnZoneVisual;

	SpawnZone = CreateDefaultSubobject<USphereComponent>(TEXT("SpawnZone"));
	SpawnZone->SetupAttachment(SpawnZoneVisual);
	SpawnZone->SetSphereRadius(1000.0f);
	SpawnZone->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SpawnZone->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
}


void APCEnemySpawner::WarnAllEnemies(APCCharacterBase* Target)
{
	for (const auto& Enemy : SpawnedEnemies)
	{
		if (Enemy)
		{
			Enemy->SetTargetActor(Target,false);
		}
	}
}


void APCEnemySpawner::EnemyKilled(const AActor* Killer, const AActor* Victim)
{
	RequestDeleteEnemy(Cast<APCAICharacterBase>(const_cast<AActor*>(Victim)));
}


void APCEnemySpawner::RequestEnemySpawn(bool bControlEnemyLimits)
{
	CheckSpawnedEnemies();
	
	if(bControlEnemyLimits && SpawnedEnemies.Num() >= TotalEnemyCount)
	{
		UE_LOG(LogTemp, Log, TEXT("Enemy limit reached"));
		return;
	}
	
	// Get a random spawn point
	FVector SpawnPoint = GetRandomSpawnLocation();

	TSubclassOf<APCAICharacterBase> RandomEnemy = EnemyClasses[FMath::RandRange(0, EnemyClasses.Num() - 1)];
	
	if (RandomEnemy)
	{
		// Spawn the Enemy
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = nullptr;
		SpawnParams.bNoFail = false;

		if (APCAICharacterBase* Enemy = GetWorld()->SpawnActor<APCAICharacterBase>(RandomEnemy, SpawnPoint , FRotator::ZeroRotator, SpawnParams))
		{
			SpawnedEnemies.Add(Enemy);
			Enemy->OnCharacterKilled.AddDynamic(this, &APCEnemySpawner::EnemyKilled);
		}
	}
}


void APCEnemySpawner::RequestDeleteEnemy(APCAICharacterBase* Enemy)
{
	if (HasAuthority())
	{
		if (SpawnedEnemies.Find(Enemy) != INDEX_NONE)
		{
			Enemy->OnCharacterKilled.RemoveDynamic(this, &APCEnemySpawner::EnemyKilled);
			SpawnedEnemies.Remove(Enemy);
		}
	}
}


void APCEnemySpawner::SpawnerTimer()
{
	PassedTime += 0.1f;
	if (PassedTime >= NextSpawnTime)
	{
		RequestEnemySpawn(true);
		PassedTime = 0.0f;
		NextSpawnTime = FMath::RandRange(MinSpawnWaitDuration, MaxSpawnWaitDuration);
	}
}


void APCEnemySpawner::CheckSpawnedEnemies()
{
	for (int32 i = SpawnedEnemies.Num() - 1; i >= 0; i--)
	{
		if (!SpawnedEnemies[i])
		{
			SpawnedEnemies.RemoveAt(i);
		}
	}
}


FVector APCEnemySpawner::GetRandomSpawnLocation() const
{
	// Use Random Reachable Point in Radius
	if (const auto NavSystem = Cast<UNavigationSystemV1>(GetWorld()->GetNavigationSystem()))
	{
		FNavLocation NavLocation;
		if (NavSystem->GetRandomReachablePointInRadius(GetActorLocation(), SpawnZone->GetScaledSphereRadius(), NavLocation))
		{
			return NavLocation.Location + FVector(0, 0, 50);
		}
	}
	return FVector::ZeroVector; 
}


AActor* APCEnemySpawner::GetRandomTargetActor() const
{
	if (GetWorld()->GetGameState())
	{
		TArray<TObjectPtr<APlayerState>> Players = GetWorld()->GetGameState()->PlayerArray;
		
		if (Players.Num() > 0)
		{
			TObjectPtr<APlayerState> Player = Players[FMath::RandRange(0, Players.Num() - 1)];
			if (Player)
			{
				return Player->GetPawn();
			}
		}
	}
	return nullptr;
}


void APCEnemySpawner::OnRep_SpawnedEnemies() {}


void APCEnemySpawner::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APCEnemySpawner, SpawnedEnemies);
}


// Called when the game starts or when spawned
void APCEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

	// Load the settings
	if (HasAuthority())
	{
		NextSpawnTime = FMath::RandRange(MinSpawnWaitDuration, MaxSpawnWaitDuration);
		GetWorld()->GetTimerManager().SetTimer(DirectorTimerHandle, this, &APCEnemySpawner::SpawnerTimer, 0.1, true);
	}
}

