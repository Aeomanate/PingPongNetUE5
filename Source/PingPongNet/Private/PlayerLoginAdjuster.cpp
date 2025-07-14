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
    : PlayerIngameId{ PlayerController->GetPlayerState<APingPongPlayerState>()->PlayerIngameId }
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
    if (PlayerIngameId > Defaults->Gameplay.MaxPlayers)
    {
        SCREEN_ERROR("Trying to join player {}, above max {}!", PlayerIngameId, Defaults->Gameplay.MaxPlayers);
        return false;
    }
    if (PlayerIngameId > Defaults->Field.Players.Num())
    {
        SCREEN_ERROR("Camera doesn't exist for player {}!", PlayerIngameId);
        return false;
    }
    return true;
}

bool UPlayerLoginAdjuster::SpawnPlayerPawn()
{
    const FVector* SpawnPoint = &Defaults->Field.Players[PlayerIngameId-1].PawnSpawnPoint;
    PlayerPawn = Cast<APlayerPawn>(World->SpawnActor(Defaults->Field.Classes.PlayerPawn, SpawnPoint));
    if (!PlayerPawn)
    {
        SCREEN_ERROR("PlayerPawn for %d player not created!", PlayerIngameId);
        return false;
    }
    SCREEN_LOG("Pawn installed for {} player!", PlayerIngameId);
    return true;
}

void UPlayerLoginAdjuster::AdjustPlayerPawn()
{
    PlayerPawn->InverseAxisX = Defaults->Field.Players[PlayerIngameId-1].InputInverseX;
}

void UPlayerLoginAdjuster::AdjustPlayerController()
{
    PlayerController->Possess(PlayerPawn);
    PlayerController->SetViewTargetWithBlend(Defaults->Field.Players[PlayerIngameId-1].Camera, 1);
    PlayerController->AdjustScoreRotationRPC(Defaults->Field.Players[PlayerIngameId-1].Camera->GetActorLocation(), Defaults->Field.ActorScore);
    SCREEN_LOG("Camera installed for {} player!", PlayerIngameId);
}

void UPlayerLoginAdjuster::AdjustPlayerGate()
{
    Defaults->Field.Players[PlayerIngameId-1].Gate->PlayerIngameId = PlayerIngameId;
    SCREEN_LOG("Gate installed for player with index {}!", PlayerIngameId);
}