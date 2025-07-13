// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ScoreActor.generated.h"

UCLASS()
class PINGPONGNET_API AScoreActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AScoreActor();

	void RotateScoreToPlayerCamera(FVector CameraLocation);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent, Category = "PingPong")
	void Init(int MaxScore);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "PingPong")
	void OnIncreasedClientScore();

	UFUNCTION(BlueprintImplementableEvent, Category = "PingPong")
	void OnIncreasedOppopentScore();
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

};
