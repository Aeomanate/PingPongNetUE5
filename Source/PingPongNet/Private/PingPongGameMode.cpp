// Fill out your copyright notice in the Description page of Project Settings.


#include "PingPongGameMode.h"
#include "Camera/CameraActor.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpectatorPawn.h"
#include "PlayerPawn.h"

bool APingPongGameMode::ReadyToStartMatch_Implementation()
{
    return this->NumPlayers == 2;
}

bool APingPongGameMode::ReadyToEndMatch_Implementation()
{
    return false;
}

void APingPongGameMode::OnPostLogin(AController* NewPlayer)
{
    if (!CheckPrerequires())
    {
        return;
    }

    APlayerController* PlayerController = nullptr;
    APlayerPawn* PlayerPawn = nullptr;
    
    bool ControllerValid = (PlayerController = GetPlayerController(NewPlayer)) != nullptr;
    bool PreparationDone = ControllerValid && (PlayerPawn = SpawnPlayerPawn()) != nullptr;
    if (!PreparationDone)
    {
        return;
    }
    
    PreparePawn(PlayerPawn);
    PlayerController->Possess(PlayerPawn);
    PreparePlayerController(PlayerController);

    if (this->NumPlayers == 2)
    {
        SpawnBall();
    }
}

void APingPongGameMode::BeginPlay()
{

}

bool APingPongGameMode::CheckPrerequires() const
{
    if (!GetWorld())
    {
        UE_LOG(LogTemp, Warning, TEXT("World is invalid, wow!"));
        return false;
    }
    if (NumPlayers > 2)
    {
        UE_LOG(LogTemp, Warning, TEXT("Trying to join %d'th player!"), NumPlayers);
        return false;
    }
    if (NumPlayers > PlayerCameras.Num())
    {
        UE_LOG(LogTemp, Error, TEXT("Camera doesn't exist for %d player!"), NumPlayers - 1);
        return false;
    }
    return true;
}

APlayerController* APingPongGameMode::GetPlayerController(AController* NewPlayer)
{
    APlayerController* PlayerController = dynamic_cast<APlayerController*>(NewPlayer);
    if (!PlayerController)
    {
        UE_LOG(LogTemp, Error, TEXT("PlayerController for %d player invalid!"), NumPlayers - 1);
        return nullptr;
    }
    UE_LOG(LogTemp, Warning, TEXT("PlayerController for %d player valid!"), NumPlayers - 1);
    return PlayerController;
}

APlayerPawn* APingPongGameMode::SpawnPlayerPawn()
{
    APlayerPawn* PlayerPawn = dynamic_cast<APlayerPawn*>(GetWorld()->SpawnActor(PlayerPawnClass->GetDefaultObject()->GetClass(), &PlayerSpawnPoints[NumPlayers - 1]));
    if (!PlayerPawn)
    {
        UE_LOG(LogTemp, Error, TEXT("PlayerPawn for %d player not created!"), NumPlayers - 1);
        return nullptr;
    }
    UE_LOG(LogTemp, Warning, TEXT("PlayerPawn for %d player spawned!"), NumPlayers - 1);
    return PlayerPawn;
}

void APingPongGameMode::PreparePawn(APlayerPawn* PlayerPawn)
{
    PlayerPawn->InverseAxisX = PlayerInputInverseX[NumPlayers - 1];
}

void APingPongGameMode::PreparePlayerController(APlayerController* PlayerController)
{
    PlayerController->ClientSetViewTarget(PlayerCameras[NumPlayers - 1]);
    PlayerController->SetViewTargetWithBlend(PlayerCameras[NumPlayers - 1], 1);
    UE_LOG(LogTemp, Warning, TEXT("Camera installed for %d player!"), NumPlayers - 1);
}

AActor* APingPongGameMode::SpawnBall()
{
    FTransform BallStartTransform;
    BallStartTransform.SetTranslation(BallSpawnPoint);

    AActor* Ball = GetWorld()->SpawnActor(BallClass->GetDefaultObject()->GetClass(), &BallStartTransform);
    if (!Ball)
    {
        UE_LOG(LogTemp, Error, TEXT("Ball not spawned!"));
        return nullptr;
    }
    UE_LOG(LogTemp, Warning, TEXT("Ball spawned!"));
    return Ball;
}