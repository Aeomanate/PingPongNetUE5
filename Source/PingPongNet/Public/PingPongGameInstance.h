#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PingPongGameInstance.generated.h"

/**
 * Game instance to handle server connection configuration
 */
UCLASS()
class PINGPONGNET_API UPingPongGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;
	virtual void PostLoad() override;
};
