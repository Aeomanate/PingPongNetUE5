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
	int PlayerIngameId = NewPlayer->GetPlayerState<APingPongPlayerState>()->PlayerIngameId = NumPlayers;

	if (NumPlayers == GameDefaults.Gameplay.MaxPlayers)
	{
		IsMatchReady = true;
	}

	bool IsPlayerInitSuccess = UPlayerLoginAdjuster(
		Cast<APingPongPlayerController>(NewPlayer),
		&GameDefaults,
		GET_VALID_WORLD()
	).Adjust();
	SCREEN_LOG("Init player {} was {}", PlayerIngameId, (IsPlayerInitSuccess ? "SUCCESS" : "FAIL"));

	if (IsMatchReady)
	{
		SCREEN_LOG("Match is ready!");
		SpawnBall();
	}
	else
	{
		SCREEN_LOG("Match is not ready! Waiting for the second player...");
	}
}

void APingPongGameMode::OnBallTriggersGate(int PlayerIngameId) const
{
	OnPlayerGotScore.Broadcast(PlayerIngameId);
}

void APingPongGameMode::BeginPlay()
{
	// Skip initialization in editor preview
	if (GetWorld()->IsEditorWorld() && !GetWorld()->IsPlayInEditor())
	{
		return;
	}

	if (!GET_VALID_WORLD() or GetWorld()->GetGameState()->PlayerArray.Num() != 2)
	{
		return;
	}

	SCREEN_LOG("GameMode BeginPlay - actual gameplay session");
}

AActor* APingPongGameMode::SpawnBall() const
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
