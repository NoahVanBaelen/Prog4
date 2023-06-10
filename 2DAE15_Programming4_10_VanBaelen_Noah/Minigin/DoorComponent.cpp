#include "DoorComponent.h"
#include "TriggerComponent.h"
#include "PlayerStatsComponent.h"

DoorComponent::DoorComponent(dae::GameObject* pOwner)
	:BaseComponent(pOwner)
{
}

void DoorComponent::Update(float)
{
	if (m_AmountOfEnemies <= 0 && GetOwner()->HasComponent<TriggerComponent>())
	{
		std::pair<bool, dae::GameObject*> trigger{ GetOwner()->GetComponent<TriggerComponent>()->GetHasTriggerLastFrame() };
		if (trigger.first == true && trigger.second->HasComponent<PlayerStatsComponent>())
		{
			std::cout << "EndLevel";
		}
	}
}

void DoorComponent::SetAmountOfEnemy(int amount)
{
	m_AmountOfEnemies = amount;
}

void DoorComponent::DecreaseCurrentCount()
{
	--m_AmountOfEnemies;
}
