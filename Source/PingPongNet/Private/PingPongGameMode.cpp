// Fill out your copyright notice in the Description page of Project Settings.


#include "PingPongGameMode.h"

bool APingPongGameMode::ReadyToStartMatch_Implementation()
{
    return this->NumPlayers == 2;
}
