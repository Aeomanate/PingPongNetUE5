// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

UCLASS()
class PINGPONGNET_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public:
	UPROPERTY(BlueprintReadWrite)
	bool InverseAxisX;

	UPROPERTY(BlueprintReadWrite)
	double MovingSpeed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(Server, Unreliable)
	void MoveLeftRightRPC(float Bias);
	void MoveLeftRightRPC_Implementation(float Bias);

	UFUNCTION(Server, Unreliable)
	void MoveLeftRightBroadcast(float Bias);
	void MoveLeftRightBroadcast_Implementation(float Bias);

	UFUNCTION(BlueprintCallable, Category = "Game")
	void SetMovableComponentIntoCache(UPrimitiveComponent* Component);

private:
	UPrimitiveComponent* MovableComponent;

};
