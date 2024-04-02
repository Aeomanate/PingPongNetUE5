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
    bool IsPlayerInitSuccess = UPlayerLoginAdjuster(NewPlayer, NumPlayers - 1, &GameDefaults, GetValidWorld()).Adjust();

    int PlayerNetID = NewPlayer->GetPlayerState<APingPongPlayerState>()->GetPlayerId();
    FString PlayerNetIDStr = FString::FromInt(PlayerNetID);
    SCREEN_LOG("Init player " + PlayerNetIDStr + " " + (IsPlayerInitSuccess ? "SUCCESS" : "FAIL"));

    if (NumPlayers == GameDefaults.Gameplay.MaxPlayers)
    {
        SpawnBall();
        IsMatchReady = true;
    }
}

void APingPongGameMode::OnBallTriggersGate(int PlayerID)
{
    OnPlayerGotScore.Broadcast(PlayerID);
}

void APingPongGameMode::BeginPlay()
{
    if (!GetValidWorld())
    {
        return;
    }

    APingPongState* PingPongState = Cast<APingPongState>(GetValidWorld()->GetGameState());
    if (!PingPongState)
    {
        ERROR("APingPongState is invalid, wow!");
        return;
    }

    GameDefaults.Gameplay.MaxPlayers = 2;
    GameDefaults.Gameplay.MaxScore = 10;
}


AActor* APingPongGameMode::SpawnBall()
{
    FTransform BallStartTransform;
    BallStartTransform.SetTranslation(GameDefaults.Field.SpawnPointBall);

    UClass* BallClass = GameDefaults.Field.Classes.Ball->GetDefaultObject()->GetClass();
    AActor* Ball = GetWorld()->SpawnActor(BallClass, &BallStartTransform);
    if (!Ball)
    {
        ERROR("Ball not spawned!");
        return nullptr;
    }
    SCREEN_LOG("Ball spawned!");
    return Ball;
}

