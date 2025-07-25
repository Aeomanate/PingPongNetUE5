#pragma once

#include "CoreMinimal.h"
#include "UtilityGameTypes.generated.h"

class APlayerGate;
class AScoreActor;

UENUM(BlueprintType)
enum class EScoreOwner : uint8
{
    Client,
    Opponent
};

USTRUCT(BlueprintType)
struct FPingPongPlayer
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite, Category = PingPongDefaults)
    bool InputInverseX = { };

    UPROPERTY(BlueprintReadWrite, Category = PingPongDefaults)
    ACameraActor* Camera = { };

    UPROPERTY(BlueprintReadWrite, Category = PingPongDefaults)
    APlayerGate* Gate = { };

    UPROPERTY(BlueprintReadWrite, Category = PingPongDefaults)
    FVector PawnSpawnPoint = { FVector::Zero() };
};

USTRUCT(BlueprintType)
struct FPingPongClasses
{
    GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PingPongDefaults)
    TSubclassOf<APawn> PlayerPawn = { };

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PingPongDefaults)
    TSubclassOf<AActor> Ball = { };
};

USTRUCT(BlueprintType)
struct FPingPongDefaultsField
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite, Category = PingPongDefaults)
    FPingPongClasses Classes = { };

    UPROPERTY(BlueprintReadWrite, Category = PingPongDefaults)
    FVector SpawnPointBall = { FVector::Zero() };

    UPROPERTY(BlueprintReadWrite, Category = PingPongDefaults)
    AScoreActor* ActorScore = { };

    UPROPERTY(BlueprintReadWrite, Category = PingPongDefaults)
    TArray<FPingPongPlayer> Players = { };
};

USTRUCT(BlueprintType)
struct FPingPongDefaultsGameplay
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadOnly, Category = PingPongDefaults)
    int MaxPlayers = 2;

    UPROPERTY(BlueprintReadOnly, Category = PingPongDefaults)
    int MaxScore = 10;
};

USTRUCT(BlueprintType)
struct FPingPongDefaults 
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite, Category = PingPongDefaults)
    FPingPongDefaultsField Field = { }; // Filling is in the level blueprint

    UPROPERTY(BlueprintReadWrite, Category = PingPongDefaults)
    FPingPongDefaultsGameplay Gameplay = { };
};

