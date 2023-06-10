#include "EnemyObserver.h"
#include "DoorComponent.h"

EnemyObserver::EnemyObserver(dae::GameObject* observer)
	:m_Observer{ observer }
{
}

void EnemyObserver::Notify(Event event, dae::GameObject*)
{
	switch (event)
	{
	case Observer::Event::ENEMY_DIES:
		if (m_Observer->HasComponent<DoorComponent>())
		{
			m_Observer->GetComponent<DoorComponent>()->DecreaseCurrentCount();
		}
		break;
	default:
		break;
	}
}
