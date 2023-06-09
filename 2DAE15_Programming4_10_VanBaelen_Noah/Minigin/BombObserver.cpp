#include "BombObserver.h"
#include "BombComponent.h"
#include "PlayerStatsComponent.h"

BombObserver::BombObserver(dae::GameObject* observer)
	:m_Observer{ observer }
{
}

void BombObserver::Notify(Event event, dae::GameObject* /*notifyer*/)
{
	switch (event)
	{
	case Observer::Event::REMOTE:
		if (m_Observer->HasComponent<BombComponent>())
		{
			m_Observer->GetComponent<BombComponent>()->EarlyDetonation();
		}
		break;
	case Observer::Event::BOMB_EXPLODED:
		if (m_Observer->HasComponent<PlayerStatsComponent>())
		{
			m_Observer->GetComponent<PlayerStatsComponent>()->DecreaseCurrentBombs();
		}
		break;
	default:
		break;
	}
}
