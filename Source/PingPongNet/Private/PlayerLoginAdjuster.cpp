#include "PlayerLoginAdjuster.h"
#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "PlayerPawn.h"
#include "PlayerGate.h"
#include "PingPongPlayerController.h"
#include "Utility.h"
#include "PingPongPlayerState.h"
#include "Containers/StringConv.h"
#include "Kismet/KismetMathLibrary.h"
#include <format>

UPlayerLoginAdjuster::UPlayerLoginAdjuster(APingPongPlayerController* PlayerController, FPingPongDefaults* Defaults, UWorld* World)
    : PlayerId{ PlayerController->GetPlayerState<APingPongPlayerState>()->PlayerId }
    , Defaults{ Defaults }
    , PlayerPawn{ nullptr }
    , PlayerController{ PlayerController }
    , World(World)
{
        
}

bool UPlayerLoginAdjuster::Adjust()
{
    bool SuccessPreparation = 
        CheckPrerequires() &&
        SetValidPlayerController() &&
        SetValidPlayerState() &&
        SpawnPlayerPawn();
    if (!SuccessPreparation)
    {
        return false;
    }

    AdjustPlayerPawn();
    AdjustPlayerController();
    AdjustPlayerGate();
    return true;
}

bool UPlayerLoginAdjuster::CheckPrerequires() const
{
    if (!World)
    {
        return false;
    }
    if (PlayerId > Defaults->Gameplay.MaxPlayers)
    {
        SCREEN_ERROR("Trying to join player {}, above max {}!", PlayerId, Defaults->Gameplay.MaxPlayers);
        return false;
    }
    if (PlayerId > Defaults->Field.Players.Num())
    {
        SCREEN_ERROR("Camera doesn't exist for player {}!", PlayerId);
        return false;
    }
    return true;
}

bool UPlayerLoginAdjuster::SpawnPlayerPawn()
{
    UClass* PawnClass = Defaults->Field.Classes.PlayerPawn->GetDefaultObject()->GetClass();
    const FVector* SpawnPoint = &Defaults->Field.Players[PlayerId-1].PawnSpawnPoint;

    PlayerPawn = Cast<APlayerPawn>(World->SpawnActor(PawnClass, SpawnPoint));
    if (!PlayerPawn)
    {
        SCREEN_ERROR("PlayerPawn for %d player not created!", PlayerId);
        return false;
    }
    SCREEN_LOG("Pawn installed for {} player!", PlayerId);
    return true;
}

void UPlayerLoginAdjuster::AdjustPlayerPawn()
{
    PlayerPawn->InverseAxisX = Defaults->Field.Players[PlayerId-1].InputInverseX;
}

void UPlayerLoginAdjuster::AdjustPlayerController()
{
    PlayerController->Possess(PlayerPawn);
    PlayerController->SetViewTargetWithBlend(Defaults->Field.Players[PlayerId-1].Camera, 1);
    PlayerController->AdjustScoreRotationRPC(Defaults->Field.Players[PlayerId-1].Camera->GetActorLocation(), Defaults->Field.ActorScore);
    SCREEN_LOG("Camera installed for {} player!", PlayerId);
}

void UPlayerLoginAdjuster::AdjustPlayerGate()
{
    Defaults->Field.Players[PlayerId-1].Gate->PlayerId = PlayerId;
    SCREEN_LOG("Gate installed for player with index {}!", PlayerId);
}

bool UPlayerLoginAdjuster::SetValidPlayerController()
{
    if (!PlayerController)
    {
        SCREEN_ERROR("PlayerController invalid!");
        return false;
    }
    SCREEN_LOG("PlayerController valid!");
    return true;
}

bool UPlayerLoginAdjuster::SetValidPlayerState()
{
    PlayerState = PlayerController->GetPlayerState<APingPongPlayerState>();
    if (!PlayerState)
    {
        SCREEN_ERROR("PingPongPlayerState invalid!");
        return false;
    }
    SCREEN_LOG("PingPongPlayerState valid!");
    return true;
}