// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ABall::ABall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Speed = 2000;
	Direction = { FMath::RandRange(-100, 100)*1.f, FMath::RandRange(-100, 100)*1.f, 0 };
	MovableComponent = nullptr;
	IdleTimeSec = 5;
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();
	UKismetMathLibrary::Vector_Normalize(Direction);
}

void ABall::NotifyHit(
	UPrimitiveComponent* MyComp, AActor* Other,
	UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, 
	FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	FVector Reflected = UKismetMathLibrary::GetReflectionVector(Direction, HitNormal);
	Direction = Reflected;
	UKismetMathLibrary::Vector_Normalize(Direction);
}

void ABall::SetMovableComponentIntoCache(UPrimitiveComponent* Component)
{
	MovableComponent = Component;
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!MovableComponent)
	{
		return;
	}

	if (IdleTimePassed < IdleTimeSec)
	{
		IdleTimePassed += DeltaTime;
		return;
	}

	MovableComponent->SetPhysicsLinearVelocity(Direction * Speed);
}

