// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "PlayerGate.generated.h"

/**
 * 
 */
UCLASS()
class PINGPONGNET_API APlayerGate : public ATriggerBox
{
	GENERATED_BODY()
public:


public:
	UPROPERTY(BlueprintReadOnly, Category = PingPong)
	int PlayerID;
};
