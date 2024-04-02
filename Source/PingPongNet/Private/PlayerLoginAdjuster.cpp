#include "PlayerLoginAdjuster.h"
#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "PlayerPawn.h"
#include "PlayerGate.h"
#include "Utility.h"
#include "PingPongPlayerState.h"
#include "Containers/StringConv.h"
#include "Kismet/KismetMathLibrary.h"

UPlayerLoginAdjuster::UPlayerLoginAdjuster(AController* NewPlayer, int PlayerIndex, FPingPongDefaults* Defaults, UWorld* World)
    : PlayerIndex{ PlayerIndex }
    , Defaults{ Defaults }
    , DefaultPlayerController{ NewPlayer }
    , PlayerPawn{ nullptr }
    , PlayerController{ nullptr }
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
    if (PlayerIndex >= Defaults->Gameplay.MaxPlayers)
    {
        ERROR("Trying to join %d'th player, above %d!", PlayerIndex+1, Defaults->Gameplay.MaxPlayers);
        return false;
    }
    if (PlayerIndex >= Defaults->Field.Players.Num())
    {
        ERROR("Camera doesn't exist for %d player!", PlayerIndex);
        return false;
    }
    return true;
}

bool UPlayerLoginAdjuster::SpawnPlayerPawn()
{
    UClass* PawnClass = Defaults->Field.Classes.PlayerPawn->GetDefaultObject()->GetClass();
    const FVector* SpawnPoint = &Defaults->Field.Players[PlayerIndex].PawnSpawnPoint;

    PlayerPawn = dynamic_cast<APlayerPawn*>(World->SpawnActor(PawnClass, SpawnPoint));
    if (!PlayerPawn)
    {
        ERROR("PlayerPawn for %d player not created!", PlayerIndex);
        return false;
    }
    SCREEN_LOG("Pawn installed for " + FString::FromInt(PlayerIndex) + " player!");
    return true;
}

void UPlayerLoginAdjuster::AdjustPlayerPawn()
{
    PlayerPawn->InverseAxisX = Defaults->Field.Players[PlayerIndex].InputInverseX;
}

void UPlayerLoginAdjuster::AdjustPlayerController()
{
    PlayerController->Possess(PlayerPawn);
    PlayerController->SetViewTargetWithBlend(Defaults->Field.Players[PlayerIndex].Camera, 1);
    SCREEN_LOG("Camera installed for " + FString::FromInt(PlayerIndex) + " player!");
}

void UPlayerLoginAdjuster::AdjustPlayerGate()
{
    Defaults->Field.Players[PlayerIndex].Gate->PlayerID = PlayerState->GetPlayerId();
    SCREEN_LOG("Gate installed for " + FString::FromInt(PlayerIndex) + " player!");
}

bool UPlayerLoginAdjuster::SetValidPlayerController()
{
    PlayerController = dynamic_cast<APlayerController*>(DefaultPlayerController);
    if (!PlayerController)
    {
        ERROR("PlayerController invalid!");
        return false;
    }
    LOG("PlayerController valid!");
    return true;
}

bool UPlayerLoginAdjuster::SetValidPlayerState()
{
    PlayerState = PlayerController->GetPlayerState<APingPongPlayerState>();
    if (!PlayerState)
    {
        ERROR("PingPongPlayerState invalid!");
        return false;
    }
    LOG("PingPongPlayerState valid!");
    return true;
}