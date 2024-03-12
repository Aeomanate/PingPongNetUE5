// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ABall::ABall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Speed = 2000;
	Direction = { 0.8, 0.6, 0 };
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();
	UKismetMathLibrary::Vector_Normalize(Direction);
}

void ABall::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other,
	UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, 
	FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!UKismetMathLibrary::NearlyEqual_FloatFloat(HitNormal.Z, 0))
	{
		return;
	}

	FVector Reflected = UKismetMathLibrary::GetReflectionVector(Direction, HitNormal);
	Reflected.Z = 0;
	Direction = Reflected;
	UKismetMathLibrary::Vector_Normalize(Direction);
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

