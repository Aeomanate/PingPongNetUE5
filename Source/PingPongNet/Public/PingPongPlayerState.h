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

	UPROPERTY(Replicated)
	int PlayerIngameId = -1;

	// Function to register properties for replication
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
