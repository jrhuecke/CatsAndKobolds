// Fill out your copyright notice in the Description page of Project Settings.


#include "PotionProjectile.h"

// Sets default values
APotionProjectile::APotionProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	if (!RootComponent) {
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));
	}
	if (!CollisionComponent) {
		CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
		CollisionComponent->InitSphereRadius(15.0f);
		RootComponent = CollisionComponent;
	}
	if (!ProjectileMovementComponent) {
		ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
		ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
		ProjectileMovementComponent->MaxSpeed = 3000.0f;
		ProjectileMovementComponent->InitialSpeed = 3000.0f;
		ProjectileMovementComponent->bRotationFollowsVelocity = true;
		ProjectileMovementComponent->bShouldBounce = true;
		ProjectileMovementComponent->Bounciness - 0.3f;
		ProjectileMovementComponent->ProjectileGravityScale = 0.0f;


	}

}

// Called when the game starts or when spawned
void APotionProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APotionProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APotionProjectile::FireInDirection(const FVector& ShootDirection) {
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

