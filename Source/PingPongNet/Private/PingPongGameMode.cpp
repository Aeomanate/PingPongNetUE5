// Fill out your copyright notice in the Description page of Project Settings.


#include "PingPongGameMode.h"
#include "Camera/CameraActor.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpectatorPawn.h"
#include "PlayerPawn.h"
#include "Engine/TriggerBox.h"
#include "PlayerGate.h"
#include "PingPongState.h"
#include "PingPongPlayerState.h"

bool APingPongGameMode::ReadyToStartMatch_Implementation()
{
    return IsMatchReady;
}

bool APingPongGameMode::ReadyToEndMatch_Implementation()
{
    return false;
}

void APingPongGameMode::OnPostLogin(AController* NewPlayer)
{
    UPlayerLoginAdjuster(NewPlayer, NumPlayers - 1, &Defaults, GetValidWorld()).Adjust();
    SCREEN_LOG("Player (id " + FString::FromInt(NewPlayer->GetPlayerState<APingPongPlayerState>()->GetPlayerId()) + ") logged in!");

    if (NumPlayers == Defaults.Gameplay.MaxPlayers)
    {
        SpawnBall();
        IsMatchReady = true;
    }
}

void APingPongGameMode::OnBallTriggersGate(int PlayerID)
{
    APingPongState* PingPongState = dynamic_cast<APingPongState*>(GetWorld()->GetGameState());
    ++PingPongState->PlayerScores.FindOrAdd(PlayerID);
    OnPlayerGotScore.Broadcast(PlayerID);
    SCREEN_LOG("Player " + FString::FromInt(PlayerID) + " got a score. Total: " + FString::FromInt(PingPongState->PlayerScores[PlayerID]));
}

void APingPongGameMode::BeginPlay()
{
    if (!GetValidWorld())
    {
        return;
    }

    APingPongState* PingPongState = dynamic_cast<APingPongState*>(GetValidWorld()->GetGameState());
    if (!PingPongState)
    {
        ERROR("APingPongState is invalid, wow!");
        return;
    }

    Defaults.Gameplay.MaxPlayers = 2;
    Defaults.Gameplay.MaxScore = 10;
}


AActor* APingPongGameMode::SpawnBall()
{
    FTransform BallStartTransform;
    BallStartTransform.SetTranslation(Defaults.Field.SpawnPointBall);

    UClass* BallClass = Defaults.Field.Classes.Ball->GetDefaultObject()->GetClass();
    AActor* Ball = GetWorld()->SpawnActor(BallClass, &BallStartTransform);
    if (!Ball)
    {
        ERROR("Ball not spawned!");
        return nullptr;
    }
    SCREEN_LOG("Ball spawned!");
    return Ball;
}

