#include "LevelObserver.h"
#include "GridComponent.h"
#include "PlayerStatsComponent.h"
#include "VersusPlayerComponent.h"
#include "HighScoreListComponent.h"

LevelObserver::LevelObserver(dae::GameObject* observer)
	:m_Observer{ observer }
{
}

void LevelObserver::Notify(Event event, dae::GameObject* /*notifyer*/)
{
	switch (event)
	{
	case Observer::Event::END_OF_LEVEL:
		if (m_Observer->HasComponent<GridComponent>())
		{
			m_Observer->GetComponent<GridComponent>()->GoToNextLevel();
		}
		break;
	case Observer::Event::RELOAD_LEVEL:
		if (m_Observer->HasComponent<PlayerStatsComponent>())
		{
			m_Observer->GetComponent<PlayerStatsComponent>()->ResetToStartPosition();
		}
		if (m_Observer->HasComponent<VersusPlayerComponent>())
		{
			m_Observer->GetComponent<VersusPlayerComponent>()->ResetToStartPosition();
		}
		break;
	case Observer::Event::START_GAME:
		if (m_Observer->HasComponent<PlayerStatsComponent>())
		{
			m_Observer->GetComponent<PlayerStatsComponent>()->StartNewGame();
		}
		if (m_Observer->HasComponent<VersusPlayerComponent>())
		{
			m_Observer->GetComponent<VersusPlayerComponent>()->ResetToStartPosition();
		}
		break;
	case Observer::Event::SETUP_GRID_FOR_START:
		if (m_Observer->HasComponent<GridComponent>())
		{
			m_Observer->GetComponent<GridComponent>()->GoToStartLevel();
		}
		break;
	case Observer::Event::END_OF_GAME:
		if (m_Observer->HasComponent<HighScoreListComponent>())
		{
			m_Observer->GetComponent<HighScoreListComponent>()->SetHighScoreList();
		}
		break;
	default:
		break;
	}
}
