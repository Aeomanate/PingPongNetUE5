// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "UtilityGameTypes.h"
#include "Utility.h"
#include "PlayerLoginAdjuster.h"
#include "Delegates/Delegate.h"
#include "PingPongGameMode.generated.h"

DECLARE_EVENT_OneParam(APingPongGameMode, OnPlayerGotScoreEvent, int PlayerIngameId);

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
    void HandleMatchHasStarted() override;

    UFUNCTION(BlueprintCallable, Category = "PingPong")
    void OnBallTriggersGate(int PlayerIngameId) const;

    UFUNCTION(BlueprintCallable, Category = "PingPong")
    void BeginPlay() override;

    const char* GetNetModeString() const;

public: // Delegates
    OnPlayerGotScoreEvent OnPlayerGotScore;

private: // Game initialization functions
    AActor* SpawnBall() const;

public: // Members
    UPROPERTY(BlueprintReadWrite, Category = PingPongDefaults)
    FPingPongDefaults GameDefaults;

    bool IsMatchReady = false;

private:
    // The server address to connect to
    UPROPERTY(Config)
    FString ServerAddress;
};
