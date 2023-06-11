#include "EnemyObserver.h"
#include "DoorComponent.h"
#include "TextComponent.h"
#include "HighScoreListComponent.h"
#include "EnemyLogicComponent.h"

EnemyObserver::EnemyObserver(dae::GameObject* observer)
	:m_Observer{ observer }
{
}

void EnemyObserver::Notify(Event event, dae::GameObject* notifyer)
{
	switch (event)
	{
	case Observer::Event::ENEMY_DIES:
		if (m_Observer->HasComponent<DoorComponent>())
		{
			m_Observer->GetComponent<DoorComponent>()->DecreaseCurrentCount();
		}

		if (m_Observer->HasComponent<HighScoreListComponent>())
		{
			m_Observer->GetComponent<HighScoreListComponent>()->AddScore(notifyer->GetComponent<EnemyLogicComponent>()->GetScore());
		}

		break;
	case Observer::Event::SCORE_CHANGE:
		if (!m_Observer->HasComponent<HighScoreListComponent>() && m_Observer->HasComponent<TextComponent>())
		{
			m_Observer->GetComponent<TextComponent>()->SetText("Score: " + std::to_string(notifyer->GetComponent<HighScoreListComponent>()->GetScore()));
		}
		break;
	default:
		break;
	}
}
