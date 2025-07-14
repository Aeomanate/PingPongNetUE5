// Fill out your copyright notice in the Description page of Project Settings.


#include "PingPongPlayerController.h"

#include "PingPongGameMode.h"
#include "ScoreActor.h"
#include "Utility.h"

#include "GameFramework/GameModeBase.h"

#include "Kismet/GameplayStatics.h"

void APingPongPlayerController::AdjustScoreRotationRPC_Implementation(FVector CameraLocation, AScoreActor* ScoreActor)
{
	ScoreActor->RotateScoreToPlayerCamera(CameraLocation);
}

AScoreActor* APingPongPlayerController::FindScoreActor() const
{
    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("ScoreActor"), FoundActors);

    if (FoundActors.Num() == 0)
    {
        // No score actors found, possibly in editor
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

    AScoreActor* ScoreActor = FindScoreActor();
    if (!ScoreActor)
    {
        SCREEN_ERROR("Score actor not found!")
    }
    
    ScoreActor->OnScoresChanged(ClientScore, OpponentScore);
    
}

void APingPongPlayerController::BeginPlay()
{
	Super::BeginPlay();
    
    FindScoreActor()->Init(10); // TODO: Refactor
}

void APingPongPlayerController::PostRegisterAllComponents()
{
    Super::PostRegisterAllComponents();
    
    FindScoreActor()->Init(10); // TODO: Refactor
}
