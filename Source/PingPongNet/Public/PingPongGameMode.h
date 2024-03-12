// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "PingPongGameMode.generated.h"

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

private:
};
