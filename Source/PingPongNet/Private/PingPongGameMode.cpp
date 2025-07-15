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
		SCREEN_LOG("Match is ready! Starting gameplay soon...");
	}

	bool IsPlayerInitSuccess = UPlayerLoginAdjuster(
		Cast<APingPongPlayerController>(NewPlayer),
		&GameDefaults,
		GET_VALID_WORLD()
	).Adjust();
	SCREEN_LOG("Init player {} was {}", PlayerIngameId, (IsPlayerInitSuccess ? "SUCCESS" : "FAIL"));

	if (!IsMatchReady)
	{
		SCREEN_LOG("Match is not ready! Waiting for more players... Current: {} / Required: {}", 
			NumPlayers, GameDefaults.Gameplay.MaxPlayers);
	}
}

void APingPongGameMode::OnBallTriggersGate(int PlayerIngameId) const
{
	OnPlayerGotScore.Broadcast(PlayerIngameId);
}

void APingPongGameMode::BeginPlay()
{
	if (GetWorld()->IsEditorWorld() && !GetWorld()->IsPlayInEditor())
	{
		return;
	}

	SCREEN_LOG("GameMode BeginPlay - actual gameplay session");
	SCREEN_WARNING("Running as NetMode: {}", GetNetModeString());
}

void APingPongGameMode::HandleMatchHasStarted()
{
	Super::HandleMatchHasStarted();

	// Only spawn the ball on server (dedicated or listen)
	if (GetNetMode() == NM_DedicatedServer || GetNetMode() == NM_ListenServer)
	{
		SpawnBall();
		SCREEN_LOG("Match started - ball spawned");
	}
}

const char* APingPongGameMode::GetNetModeString() const
{
	switch(GetNetMode())
	{
		case NM_Standalone: return "Standalone";
		case NM_DedicatedServer: return "Dedicated Server";
		case NM_ListenServer: return "Listen Server";
		case NM_Client: return "Client";
		default: return "Unknown";
	}
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
