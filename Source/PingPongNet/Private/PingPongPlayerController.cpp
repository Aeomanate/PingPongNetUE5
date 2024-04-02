// Fill out your copyright notice in the Description page of Project Settings.


#include "PingPongPlayerController.h"
#include "ScoreActor.h"

void APingPongPlayerController::AdjustScoreRotationRPC_Implementation(FVector CameraLocation, AScoreActor* ScoreActor)
{
    ScoreActor->RotateScoreToPlayerCamera(CameraLocation);
}
