// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PingPongPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class PINGPONGNET_API APingPongPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:

	int PlayerId;

	
};
