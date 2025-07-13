#include "PlayerGate.h"

#include "PingPongGameMode.h"
#include "Utility.h"


void APlayerGate::OnCollideWithBall() const
{
	auto* GameMode = Cast<APingPongGameMode>(GET_VALID_WORLD()->GetAuthGameMode());
	GameMode->OnBallTriggersGate(PlayerId);
	SCREEN_LOG("Ball triggered gate on server!");
}
