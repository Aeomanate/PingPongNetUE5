// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "UtilityGameTypes.h"
#include "Utility.h"
#include "PlayerLoginAdjuster.h"
#include "Delegates/Delegate.h"
#include "PingPongGameMode.generated.h"

DECLARE_EVENT_OneParam(APingPongGameMode, OnPlayerGotScoreEvent, int PlayerID);

class APlayerPawn;
class ATriggerBox;
class APlayerGate;

/**
 * 
 */
UCLASS()
class PINGPONGNET_API APingPongGameMode : public AGameMode
{
	GENERATED_BODY()

public: // Gamemode logic
    bool ReadyToStartMatch_Implementation();
    bool ReadyToEndMatch_Implementation();

    void OnPostLogin(AController* NewPlayer) override;

    UFUNCTION(BlueprintCallable, Category = "PingPong")
    void OnBallTriggersGate(int PlayerId) const;

    UFUNCTION(BlueprintCallable, Category = "PingPong")
    void BeginPlay() override;

public: // Delegates
    OnPlayerGotScoreEvent OnPlayerGotScore;

private: // Game initialization functions
    AActor* SpawnBall();

public: // Members
    UPROPERTY(BlueprintReadWrite, Category = PingPongDefaults)
    FPingPongDefaults GameDefaults;

    bool IsMatchReady = false;
};
