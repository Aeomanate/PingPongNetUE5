#include "PlayerGate.h"

#include "PingPongGameMode.h"
#include "Utility.h"


void APlayerGate::OnCollideWithBall() const
{
	if (auto* GameMode = Cast<APingPongGameMode>(GET_VALID_WORLD()->GetAuthGameMode()))
	{
		GameMode->OnBallTriggersGate(PlayerId);
		SCREEN_LOG("Ball triggered gate on server!");
	}
	else
	{
		SCREEN_LOG("GameMode is invalid on client!");
	}
}
