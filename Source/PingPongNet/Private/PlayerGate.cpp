#include "PlayerGate.h"

#include "PingPongGameMode.h"
#include "PingPongPlayerController.h"
#include "PingPongPlayerState.h"
#include "PingPongState.h"
#include "Utility.h"


void APlayerGate::OnCollideWithBall() const
{
	auto* GameMode = Cast<APingPongGameMode>(GET_VALID_WORLD()->GetAuthGameMode());
	GameMode->OnBallTriggersGate(PlayerIngameId);
	SCREEN_LOG("Ball triggered gate on server!");

	int PlayerScore1 = GameMode->GetGameState<APingPongState>()->PlayerScores[0];
	int PlayerScore2 = GameMode->GetGameState<APingPongState>()->PlayerScores[1];
	
	for (auto It: GetWorld()->GetGameState()->PlayerArray)
	{
		APingPongPlayerController* Player = Cast<APingPongPlayerController>(It->GetPlayerController());
		int CurId = Cast<APingPongPlayerState>(It)->PlayerIngameId;
		if (CurId == 1)
		{
			Player->NotifyClientScoreChangedRPC(PlayerScore1, PlayerScore2);
		}
		else
		{
			Player->NotifyClientScoreChangedRPC(PlayerScore2, PlayerScore1);
		}
	}
}
