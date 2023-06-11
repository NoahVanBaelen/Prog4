#include "PlayerObserver.h"
#include "PlayerUIComponent.h"
#include "TextComponent.h"
#include "PlayerStatsComponent.h"
#include "GridComponent.h"
#include "SceneManager.h"
#include "GameState.h"
#include "CoopLogicComponent.h"

PlayerObserver::PlayerObserver(dae::GameObject* observer)
	:m_Observer{ observer }
{
}

void PlayerObserver::Notify(Event event, dae::GameObject* notifyer)
{
	switch (event)
	{
	case Observer::Event::CHANGE_IN_PLAYER_STATS:
		if (m_Observer->HasComponent<PlayerUIComponent>() && notifyer->HasComponent<PlayerStatsComponent>())
		{
			m_Observer->GetComponent<PlayerUIComponent>()->SetCounters(notifyer->GetComponent<PlayerStatsComponent>()->GetMaxBombs(), notifyer->GetComponent<PlayerStatsComponent>()->GetFirePower()
				,notifyer->GetComponent<PlayerStatsComponent>()->GetSpeedCount(), notifyer->GetComponent<PlayerStatsComponent>()->GetCanDetonateEarly());
		}
		break;
	case Observer::Event::PLAYER_DIES:
		if (m_Observer->HasComponent<TextComponent>() && !m_Observer->HasComponent<PlayerUIComponent>() && notifyer->HasComponent<PlayerStatsComponent>())
		{
			m_Observer->GetComponent<TextComponent>()->SetText("Lives: " + std::to_string(notifyer->GetComponent<PlayerStatsComponent>()->GetLives()));
		}
		break;
	case Observer::Event::PLAYER_RESET_LIVES:
		if (m_Observer->HasComponent<TextComponent>() && !m_Observer->HasComponent<PlayerUIComponent>() && notifyer->HasComponent<PlayerStatsComponent>())
		{
			m_Observer->GetComponent<TextComponent>()->SetText("Lives: " + std::to_string(notifyer->GetComponent<PlayerStatsComponent>()->GetLives()));
		}
		break;
	case Observer::Event::GAME_OVER:
		if (m_Observer->HasComponent<GridComponent>())
		{
			m_Observer->GetComponent<GridComponent>()->GameOverGrid();
		}

		if (dae::SceneManager::GetInstance().GetState()->GetCurrentMode() == GameState::CurrentMode::COOP && m_Observer->HasComponent<CoopLogicComponent>())
		{
			m_Observer->GetComponent<CoopLogicComponent>()->LowerAmountActivePlayers();
		}

		if(dae::SceneManager::GetInstance().GetState()->GetCurrentMode() != GameState::CurrentMode::COOP)
		{
			dae::SceneManager::GetInstance().SetState(std::make_shared<ScoreScreenState>(dae::SceneManager::GetInstance().GetSceneByName("ScoreScreen").get()));
		}
		break;
	default:
		break;
	}
}
