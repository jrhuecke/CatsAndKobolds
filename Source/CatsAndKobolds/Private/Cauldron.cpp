// Fill out your copyright notice in the Description page of Project Settings.


#include "Cauldron.h"
#include "Engine/StaticMeshActor.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
ACauldron::ACauldron()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACauldron::BeginPlay()
{
	Super::BeginPlay();
	
	if (HasAuthority())
	{
		GetWorld()->GetTimerManager().SetTimer(TestTimer, this, &ACauldron::CreatePotion, 2.0f, false);
	}
}

// Called every frame
void ACauldron::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DecrementBrewingTimers(DeltaTime);

}

void ACauldron::CreatePotion()
{
	BrewingTimers.Add(1.5f);
}

void ACauldron::DecrementBrewingTimers(float DeltaTime)
{
	int index = 0;
	while (index < BrewingTimers.Num())
	{
		BrewingTimers[index] -= DeltaTime;
		if (BrewingTimers[index] <= 0)
		{
			LaunchPotion();
			BrewingTimers.RemoveAt(index);
		}
		else
		{
			index++;
		}
	}
}

void ACauldron::LaunchPotion()
{
	if (ProjMesh && HasAuthority())
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = this;
		AStaticMeshActor* StaticMeshActor = GetWorld()->SpawnActor<AStaticMeshActor>(SpawnParameters);
		if (StaticMeshActor)
		{
			StaticMeshActor->SetReplicates(true);
			StaticMeshActor->SetReplicateMovement(true);
			StaticMeshActor->SetMobility(EComponentMobility::Movable);
			FVector SpawnLocation = GetActorLocation() + GetActorUpVector() * 100.0f;
			StaticMeshActor->SetActorLocation(SpawnLocation);
			UStaticMeshComponent* StaticMeshComponent = StaticMeshActor->GetStaticMeshComponent();
			if (StaticMeshComponent)
			{
				StaticMeshComponent->SetIsReplicated(true);
				StaticMeshComponent->SetSimulatePhysics(true);
				StaticMeshComponent->SetStaticMesh(ProjMesh);
			}
			
			StaticMeshComponent->AddImpulse(FVector(FMath::RandRange(-30000, 30000), FMath::RandRange(-30000, 30000), 30000));
			GetWorld()->GetTimerManager().SetTimer(TestTimer, this, &ACauldron::CreatePotion, 2.0f, false);
		}
	}
}

