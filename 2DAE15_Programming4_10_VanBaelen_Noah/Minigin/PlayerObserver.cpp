#include "PlayerObserver.h"
#include "PlayerUIComponent.h"
#include "TextComponent.h"
#include "PlayerStatsComponent.h"

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
	default:
		break;
	}
}
