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
    // Skip in editor preview
    if (GetWorld()->IsEditorWorld() && !GetWorld()->IsPlayInEditor())
    {
        return;
    }

    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("ScoreActor"), FoundActors);

    if (FoundActors.Num() == 0)
    {
        // No score actors found, possibly in editor
        return;
    }

    auto* ScoreActor = Cast<AScoreActor>(FoundActors[0]);
    if (ScoreActor)
    {
        ScoreActor->OnScoresChanged(ClientScore, OpponentScore);
    }
}

void APingPongPlayerController::BeginPlay()
{
	Super::BeginPlay();
	NotifyClientScoreChangedRPC(0, 0);
}
