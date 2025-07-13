// Fill out your copyright notice in the Description page of Project Settings.


#include "PingPongState.h"
#include "PingPongGameMode.h"
#include "PingPongPlayerState.h"
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

void APingPongState::HandlePlayerGotScore(int PlayerId)
{    
    ++PlayerScores.FindOrAdd(PlayerId, 0);
    SCREEN_LOG("Player {} got a score. Total: {}", PlayerId, PlayerScores[PlayerId]);
}
