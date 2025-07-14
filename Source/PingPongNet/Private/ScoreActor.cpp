// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreActor.h"
#include "Utility.h"
#include "PingPongGameMode.h"
#include "Kismet/KismetMathLibrary.h"
#include "PingPongPlayerState.h"

// Sets default values
AScoreActor::AScoreActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AScoreActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AScoreActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AScoreActor::RotateScoreToPlayerCamera(FVector CameraLocation)
{
	Init(10);
	FVector ScoreLocation = GetRootComponent()->GetComponentLocation();

	FRotator Rotator = UKismetMathLibrary::FindLookAtRotation(ScoreLocation, CameraLocation);
	Rotator.SetComponentForAxis(EAxis::X, 0);
	Rotator.SetComponentForAxis(EAxis::Y, 0);
	GetRootComponent()->SetWorldRotation(Rotator);
	
}

