#include "PingPongGameInstance.h"

#include "Utility.h"

#include "Engine/Engine.h"
#include "HAL/PlatformString.h"

void UPingPongGameInstance::Init()
{	
	Super::Init();
	
	// Connect to the server if we're a client
	// if (!IsRunningDedicatedServer())
	// {
	// 	FTimerHandle TimerHandle;
	// 	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
	// 	{
	// 		FString ExecCommand = FString::Printf(TEXT("open %s"), *ServerAddress);
	// 		LOG("Connecting to server: %s", *ExecCommand);
	// 		GEngine->Exec(GetWorld(), *ExecCommand);
	// 	}, 1.0f, false);
	// }
}

void UPingPongGameInstance::PostLoad()
{
	Super::PostLoad();
}
