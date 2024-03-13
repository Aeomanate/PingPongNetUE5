// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PingPongGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PINGPONGNET_API UPingPongGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:



public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PingPongDefaults)
    TSubclassOf<APawn> PlayerPawnClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PingPongDefaults)
    TSubclassOf<AActor> BallClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PingPongDefaults)
    TArray<ACameraActor*> PlayerCameras;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PingPongDefaults)
    TArray<FVector> PlayerSpawnPoints;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PingPongDefaults)
    TArray<bool> PlayerInputInverseX;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PingPongDefaults)
    FVector BallSpawnPoint;
};
