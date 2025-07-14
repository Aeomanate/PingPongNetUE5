#include "PlayerGate.h"

#include "PingPongGameMode.h"
#include "PingPongPlayerController.h"
#include "PingPongPlayerState.h"
#include "PingPongState.h"
#include "Utility.h"


void APlayerGate::OnCollideWithBall() const
{
	SCREEN_LOG("Ball triggered gate on server!");
	auto* GameMode = Cast<APingPongGameMode>(GET_VALID_WORLD()->GetAuthGameMode());
	GameMode->OnBallTriggersGate(PlayerIngameId);

	int PlayerScore1 = GameMode->GetGameState<APingPongState>()->PlayerScores[0];
	int PlayerScore2 = GameMode->GetGameState<APingPongState>()->PlayerScores[1];
	
	for (auto It: GetWorld()->GetGameState()->PlayerArray)
	{
		APingPongPlayerController* Player = Cast<APingPongPlayerController>(It->GetPlayerController());
		int CurId = Cast<APingPongPlayerState>(It)->PlayerIngameId;
		if (CurId == 1)
		{
			SCREEN_LOG("Sending to player #{} new scores: {} - {}", CurId, PlayerScore1, PlayerScore2);
			Player->NotifyClientScoreChangedRPC(PlayerScore1, PlayerScore2);
		}
		else
		{
			SCREEN_LOG("Sending to player #{} new scores: {} - {}", CurId, PlayerScore2, PlayerScore1);
			Player->NotifyClientScoreChangedRPC(PlayerScore2, PlayerScore1);
		}
	}
}
