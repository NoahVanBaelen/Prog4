#include "Achievements.h"
#include "ScoreComponent.h"

Achievements::Achievements(CSteamAchievements* SteamAchievements)
	:m_SteamAchievements{SteamAchievements}
{}

void Achievements::Notify(Event event, dae::GameObject* notifyer)
{
	switch (event)
	{
	case Observer::Event::SCORE_CHANGE:
		if (notifyer->GetComponent<ScoreComponent>()->GetScore() == 500)
		{
			m_SteamAchievements->SetAchievement("ACH_WIN_ONE_GAME");
		}
		break;
	default:
		break;
	}
}
