// Fill out your copyright notice in the Description page of Project Settings.


#include "PingPongState.h"
#include "Net/UnrealNetwork.h"
#include "PingPongGameMode.h"
#include "Utility.h"

void APingPongState::HandleMatchIsWaitingToStart()
{
    if (!HasAuthority())
    {
        return;
    }

    UWorld* World = GetValidWorld();
    AGameModeBase* BaseGamemode = World->GetAuthGameMode();
    APingPongGameMode* GameMode = Cast<APingPongGameMode>(BaseGamemode);
    GameMode->OnPlayerGotScore.AddUObject(this, &APingPongState::HandlePlayerGotScore);
}

void APingPongState::HandlePlayerGotScore(int PlayerNetID)
{
    ++PlayerScores.FindOrAdd(PlayerNetID, 0);
    SCREEN_LOG("Player " + FString::FromInt(PlayerNetID) + " got a score. Total: " + FString::FromInt(PlayerScores[PlayerNetID]));

}
