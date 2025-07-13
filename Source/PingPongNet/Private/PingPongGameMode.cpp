// Fill out your copyright notice in the Description page of Project Settings.


#include "PingPongGameMode.h"

#include "PingPongPlayerController.h"

#include "GameFramework/PlayerController.h"
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
    int PlayerId = NewPlayer->GetPlayerState<APingPongPlayerState>()->PlayerId = NumPlayers;
    bool IsPlayerInitSuccess = UPlayerLoginAdjuster(
        Cast<APingPongPlayerController>(NewPlayer),
        &GameDefaults,
        GET_VALID_WORLD()
        ).Adjust();

    SCREEN_LOG("Init player {} was {}", PlayerId, (IsPlayerInitSuccess ? "SUCCESS" : "FAIL"));

    if (NumPlayers == GameDefaults.Gameplay.MaxPlayers)
    {
        SpawnBall();
        IsMatchReady = true;
    }
}

void APingPongGameMode::OnBallTriggersGate(int PlayerId) const
{
    OnPlayerGotScore.Broadcast(PlayerId);
}

void APingPongGameMode::BeginPlay()
{
    if (!GET_VALID_WORLD())
    {
        return;
    }

    APingPongState* PingPongState = Cast<APingPongState>(GET_VALID_WORLD()->GetGameState());
    if (!PingPongState)
    {
        SCREEN_ERROR("APingPongState is invalid, wow!");
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
        SCREEN_ERROR("Ball not spawned!");
        return nullptr;
    }
    SCREEN_LOG("Ball spawned!");
    return Ball;
}

