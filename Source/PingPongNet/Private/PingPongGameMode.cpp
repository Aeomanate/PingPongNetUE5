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
    if (!GetWorld() || NumPlayers > 2)
    {
        return;
    }

    APlayerController* PlayerController = dynamic_cast<APlayerController*>(NewPlayer);
    if (!PlayerController)
    {
        UE_LOG(LogTemp, Error, TEXT("PlayerController for %d player invalid!"), NumPlayers - 1);
        return;
    }

    APlayerPawn* PlayerPawn = dynamic_cast<APlayerPawn*>(GetWorld()->SpawnActor(PlayerPawnClass->GetDefaultObject()->GetClass(), &PlayerSpawnPoints[NumPlayers-1]));
    if (!PlayerPawn)
    {
        UE_LOG(LogTemp, Error, TEXT("PlayerPawn for %d player not created!"), NumPlayers-1);
        return;
    }
    UE_LOG(LogTemp, Warning, TEXT("PlayerPawn for %d player spawned!"), NumPlayers - 1);
    
    PlayerPawn->InverseAxisX = PlayerInputInverseX[NumPlayers - 1];

    PlayerController->Possess(PlayerPawn);

    if (NumPlayers > PlayerCameras.Num())
    {
        UE_LOG(LogTemp, Error, TEXT("Camera doesn't exist for %d player!"), NumPlayers - 1);
    }

    PlayerController->ClientSetViewTarget(PlayerCameras[NumPlayers - 1]);
    PlayerController->SetViewTargetWithBlend(PlayerCameras[NumPlayers - 1], 1);

    UE_LOG(LogTemp, Warning, TEXT("Camera installed for %d player!"), NumPlayers - 1);

    if (this->NumPlayers == 2)
    {
        FTransform BallStartTransform;
        BallStartTransform.SetTranslation(BallSpawnPoint);
        AActor* Ball = GetWorld()->SpawnActor(BallClass->GetDefaultObject()->GetClass(), &BallStartTransform);
        if (!Ball)
        {
            UE_LOG(LogTemp, Error, TEXT("Ball not spawned!"));
            return;
        }
        UE_LOG(LogTemp, Warning, TEXT("Ball spawned!"));
    }
}

void APingPongGameMode::BeginPlay()
{
    if (ReadyToStartMatch()) {
        UE_LOG(LogTemp, Warning, TEXT("Ready to start"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("NOT Ready to start"));
    }
}
