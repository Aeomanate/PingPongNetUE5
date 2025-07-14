// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "PingPongState.generated.h"

/**
 * 
 */
UCLASS()
class PINGPONGNET_API APingPongState : public AGameState
{
	GENERATED_BODY()
public:
	using PlayerScoreType = int;

public:
	void HandleMatchIsWaitingToStart() override;

	void HandlePlayerGotScore(int PlayerIngameId);

	virtual void BeginPlay() override;

public:
	TArray<PlayerScoreType> PlayerScores;

private:

};
