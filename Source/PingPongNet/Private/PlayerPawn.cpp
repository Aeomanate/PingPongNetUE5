// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"

#include "PingPongPlayerState.h"
#include "Utility.h"

#include "GameFramework/FloatingPawnMovement.h"
#include "Net/UnrealNetwork.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame. 
	PrimaryActorTick.bCanEverTick = true;
	MovingSpeed = 20;
	InverseAxisX = false;
	MovableComponent = nullptr;
	SetReplicates(true);
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerPawn::MoveLeftRightRPC_Implementation(float Bias)
{
	MoveLeftRightBroadcast(Bias);
}

void APlayerPawn::MoveLeftRightBroadcast_Implementation(float Bias)
{	
	if (!MovableComponent)
	{
		return;
	}

	Bias *= (InverseAxisX ? -1 : 1);
	FVector MoveVector { MovingSpeed, 0, 0 };
	MoveVector *= Bias;

	FTransform Transform;
	Transform.SetLocation(Transform.GetLocation() + MoveVector);
	MovableComponent->AddWorldOffset(MoveVector, /* sweep */ true);
}

void APlayerPawn::SetMovableComponentIntoCache(UPrimitiveComponent* Component)
{
	MovableComponent = Component;
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MovingLeftRight"), this, &APlayerPawn::MoveLeftRightRPC);

	APingPongPlayerState* State = GetPlayerState<APingPongPlayerState>();
	if (State)
	{
		SCREEN_WARNING("You are player #{}", State->PlayerIngameId);
	}
}

