#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PingPongNetGameInstance.generated.h"

/**
 * Game instance to handle server connection configuration
 */
UCLASS()
class PINGPONGNET_API UPingPongNetGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPingPongNetGameInstance(const FObjectInitializer& ObjectInitializer);

	virtual void Init() override;

	// The server address to connect to
	UPROPERTY(Config)
	FString ServerAddress;
};
