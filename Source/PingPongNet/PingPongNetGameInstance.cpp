#include "PingPongNetGameInstance.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"

UPingPongNetGameInstance::UPingPongNetGameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Default server address if not specified in config
	ServerAddress = TEXT("127.0.0.1");
}

void UPingPongNetGameInstance::Init()
{
	Super::Init();

	// Connect to the server if we're a client
	if (!IsRunningDedicatedServer())
	{
		FString ExecCommand = FString::Printf(TEXT("open %s"), *ServerAddress);
		UE_LOG(LogTemp, Log, TEXT("Connecting to server: %s"), *ServerAddress);
		GEngine->Exec(GetWorld(), *ExecCommand);
	}
}
