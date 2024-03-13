// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "PingPongGameMode.generated.h"

class APlayerPawn;

/**
 * 
 */
UCLASS()
class PINGPONGNET_API APingPongGameMode : public AGameMode
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Game")
    bool ReadyToStartMatch_Implementation();

    UFUNCTION(BlueprintCallable, Category = "Game")
    bool ReadyToEndMatch_Implementation();

    void OnPostLogin(AController* NewPlayer) override;

    UFUNCTION(BlueprintCallable, Category = "Game")
    void BeginPlay() override;

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

protected:

private:
    bool CheckPrerequires() const;
    APlayerController* GetPlayerController(AController* NewPlayer);
    APlayerPawn* SpawnPlayerPawn();
    void PreparePawn(APlayerPawn* PlayerPawn);
    void PreparePlayerController(APlayerController* PlayerController);

    AActor* SpawnBall();
};
