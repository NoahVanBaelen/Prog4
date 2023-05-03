#include "PlayerEvents.h"
#include "PlayerSpriteComponent.h"

PlayerEvents::PlayerEvents(dae::GameObject* player)
	:m_Player{ player }
{
}

void PlayerEvents::Notify(Event event, dae::GameObject* /*notifyer*/)
{
	switch (event)
	{
	case Observer::Event::MOVE_LEFT:
		m_Player->GetComponent<PlayerSpriteComponent>()->MoveLeft();
		break;
	case Observer::Event::MOVE_RIGHT:
		m_Player->GetComponent<PlayerSpriteComponent>()->MoveRight();
		break;
	case Observer::Event::MOVE_UP:
		m_Player->GetComponent<PlayerSpriteComponent>()->MoveUp();
		break;
	case Observer::Event::MOVE_DOWN:
		m_Player->GetComponent<PlayerSpriteComponent>()->MoveDown();
		break;
	case Observer::Event::MOVE_STANDSTILL:
		m_Player->GetComponent<PlayerSpriteComponent>()->StandStill();
		break;
	default:
		break;
	}
}
