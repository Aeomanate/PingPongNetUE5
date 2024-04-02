#pragma once

#include "CoreMinimal.h"
#include "UtilityGameTypes.h"

class APingPongPlayerController;
class APlayerPawn;
class APingPongPlayerState;

class UPlayerLoginAdjuster
{
public:
    UPlayerLoginAdjuster() = default;
    UPlayerLoginAdjuster(AController* NewPlayer, int PlayerIndex, FPingPongDefaults* Defaults, UWorld* World);

    bool Adjust();

private:
    bool CheckPrerequires() const;

    bool SpawnPlayerPawn();
    void AdjustPlayerPawn();

    void AdjustPlayerController();
    void AdjustPlayerGate();

    bool SetValidPlayerController();
    bool SetValidPlayerState();
private:
    int PlayerIndex = { };
    FPingPongDefaults* Defaults = { };

    AController* DefaultPlayerController = { };
    APlayerPawn* PlayerPawn = { };
    APingPongPlayerController* PlayerController = { };
    APingPongPlayerState* PlayerState = { };
    UWorld* World = { };
};

