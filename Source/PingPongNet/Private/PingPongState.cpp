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
    int MaxPlayers = Cast<APingPongGameMode>(GetDefaultGameMode())->GameDefaults.Gameplay.MaxPlayers;
    int ScoreTo = PlayerIngameId % MaxPlayers;
    ++PlayerScores[ScoreTo];
    SCREEN_LOG("Player {} got a score. Total: {}", ScoreTo + 1, PlayerScores[ScoreTo]);
}

void APingPongState::BeginPlay()
{
    Super::BeginPlay();

    int MaxPlayers = Cast<APingPongGameMode>(GetDefaultGameMode())->GameDefaults.Gameplay.MaxPlayers;
    PlayerScores.Init(0, MaxPlayers);
}
