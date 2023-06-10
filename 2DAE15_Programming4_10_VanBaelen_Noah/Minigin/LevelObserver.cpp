#include "LevelObserver.h"
#include "GridComponent.h"

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
		break;
	default:
		break;
	}
}
