// Fill out your copyright notice in the Description page of Project Settings.


#include "PingPongPlayerController.h"
#include "ScoreActor.h"

#include "Kismet/GameplayStatics.h"

void APingPongPlayerController::AdjustScoreRotationRPC_Implementation(FVector CameraLocation, AScoreActor* ScoreActor)
{
	ScoreActor->RotateScoreToPlayerCamera(CameraLocation);
}

void APingPongPlayerController::NotifyClientScoreChangedRPC_Implementation(int ClientScore, int OpponentScore) const
{
    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("ScoreActor"), FoundActors);

    check(FoundActors.Num() == 1);
    auto* ScoreActor = Cast<AScoreActor>(FoundActors[0]);
	
    ScoreActor->OnScoresChanged(ClientScore, OpponentScore);
}

void APingPongPlayerController::BeginPlay()
{
	Super::BeginPlay();
	NotifyClientScoreChangedRPC(0, 0);
}
