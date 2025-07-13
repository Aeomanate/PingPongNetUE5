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
    UPlayerLoginAdjuster(APingPongPlayerController* PlayerController, FPingPongDefaults* Defaults, UWorld* World);

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
    int PlayerId = { };
    FPingPongDefaults* Defaults = { };

    APlayerPawn* PlayerPawn = { };
    APingPongPlayerController* PlayerController = { };
    APingPongPlayerState* PlayerState = { };
    UWorld* World = { };
};

