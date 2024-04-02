// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PingPongPlayerController.generated.h"

class AScoreActor;

/**
 * 
 */
UCLASS()
class PINGPONGNET_API APingPongPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(Unreliable, Client)
	void AdjustScoreRotationRPC(FVector CameraLocation, AScoreActor* ScoreActor);
	void AdjustScoreRotationRPC_Implementation(FVector CameraLocation, AScoreActor* ScoreActor);
};
