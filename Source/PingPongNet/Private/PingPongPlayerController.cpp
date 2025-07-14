// Fill out your copyright notice in the Description page of Project Settings.


#include "PingPongPlayerController.h"
#include "ScoreActor.h"
#include "Utility.h"
#include "Kismet/GameplayStatics.h"

void APingPongPlayerController::AdjustScoreRotationRPC_Implementation(FVector CameraLocation, AScoreActor* ScoreActor)
{
	ScoreActor->RotateScoreToPlayerCamera(CameraLocation);
}

AScoreActor* APingPongPlayerController::FindScoreActor() const
{
    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("ScoreActor"), FoundActors);

    // Skip in editor preview
    if (GetWorld()->IsEditorWorld() && !GetWorld()->IsPlayInEditor())
    {
        return nullptr;
    }
    
    if (FoundActors.Num() == 0)
    {
        return nullptr;
    }
    
    return Cast<AScoreActor>(FoundActors[0]);
}

void APingPongPlayerController::NotifyClientScoreChangedRPC_Implementation(int ClientScore, int OpponentScore) const
{
    // Skip in editor preview
    if (GetWorld()->IsEditorWorld() && !GetWorld()->IsPlayInEditor())
    {
        return;
    }
    
    FindScoreActor()->OnScoresChanged(ClientScore, OpponentScore);
}

void APingPongPlayerController::BeginPlay()
{
    Super::BeginPlay();
}
