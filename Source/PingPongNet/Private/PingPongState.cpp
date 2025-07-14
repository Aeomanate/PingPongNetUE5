// Fill out your copyright notice in the Description page of Project Settings.


#include "PingPongState.h"
#include "PingPongGameMode.h"
#include "Utility.h"

void APingPongState::HandleMatchIsWaitingToStart()
{
    if (!HasAuthority())
    {
        return;
    }

    UWorld* World = GET_VALID_WORLD();
    AGameModeBase* BaseGamemode = World->GetAuthGameMode();
    APingPongGameMode* GameMode = Cast<APingPongGameMode>(BaseGamemode);
    GameMode->OnPlayerGotScore.AddUObject(this, &APingPongState::HandlePlayerGotScore);
}

void APingPongState::HandlePlayerGotScore(int PlayerIngameId)
{    
    ++PlayerScores[PlayerIngameId-1];
    SCREEN_LOG("Player {} got a score. Total: {}", PlayerIngameId, PlayerScores[PlayerIngameId-1]);
}

void APingPongState::BeginPlay()
{
    Super::BeginPlay();

    // Skip initialization in editor preview
    if (GetWorld()->IsEditorWorld() && !GetWorld()->IsPlayInEditor())
    {
        return;
    }

    PlayerScores.Init(0, Cast<APingPongGameMode>(GetDefaultGameMode())->GameDefaults.Gameplay.MaxPlayers);
}
