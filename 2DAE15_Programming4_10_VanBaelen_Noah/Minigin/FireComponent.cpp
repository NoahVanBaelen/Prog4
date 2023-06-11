#include "FireComponent.h"
#include "TriggerComponent.h"
#include "PlayerStatsComponent.h"
#include "EnemyLogicComponent.h"
#include "VersusPlayerComponent.h"
#include "BombComponent.h"

FireComponent::FireComponent(dae::GameObject* pOwner)
	:BaseComponent(pOwner)
{}

void FireComponent::Update(float deltaTime)
{
	if (GetOwner()->HasComponent<TriggerComponent>())
	{
		std::pair<bool, dae::GameObject*> trigger{ GetOwner()->GetComponent<TriggerComponent>()->GetHasTriggerLastFrame() };
		if (trigger.first == true && trigger.second)
		{
			if (trigger.second->HasComponent<PlayerStatsComponent>())//player
			{
				trigger.second->GetComponent<PlayerStatsComponent>()->DecreaseLives();
			}

			if (trigger.second->HasComponent<VersusPlayerComponent>())//versus player
			{
				trigger.second->GetComponent<VersusPlayerComponent>()->GetKilled();
			}

			if (trigger.second->HasComponent<EnemyLogicComponent>())//enemy
			{
				trigger.second->GetComponent<EnemyLogicComponent>()->GetKilled();
			}

			if (trigger.second->HasComponent<BombComponent>())//bomb
			{
				trigger.second->GetComponent<BombComponent>()->EarlyDetonation();
			}
		}
	}

	m_LifeTime -= deltaTime * 0.01f;
	if (m_LifeTime <= 0)
	{
		GetOwner()->m_MarkedForDestroy = true;
	}
}
