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
			m_Subjects->NotifyObservers(Observer::Event::END_OF_LEVEL, GetOwner());
			trigger.second->GetComponent<PlayerStatsComponent>()->ResetToStartPosition();
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

void DoorComponent::AddObserver(Observer* observer)
{
	m_Subjects->AddObserver(observer);
}
