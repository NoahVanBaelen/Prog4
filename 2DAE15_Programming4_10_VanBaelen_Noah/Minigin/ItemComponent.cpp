#include "ItemComponent.h"
#include "PlayerStatsComponent.h"
#include "TriggerComponent.h"

ItemComponent::ItemComponent(dae::GameObject* pOwner)
	:BaseComponent(pOwner)
{
}

void ItemComponent::Update(float)
{
	if (GetOwner()->HasComponent<TriggerComponent>())
	{
		std::pair<bool, dae::GameObject*> trigger{ GetOwner()->GetComponent<TriggerComponent>()->GetHasTriggerLastFrame() };
		if (trigger.first == true && trigger.second->HasComponent<PlayerStatsComponent>())
		{
			switch (m_Type)
			{
			case ItemComponent::ItemType::EXTRA_BOMB:
				trigger.second->GetComponent<PlayerStatsComponent>()->IncreaseMaxBombs();
				break;
			case ItemComponent::ItemType::INCREASE_FIRE:
				trigger.second->GetComponent<PlayerStatsComponent>()->IncreaseFirePower();
				break;
			case ItemComponent::ItemType::INCREASE_SPEED:
				trigger.second->GetComponent<PlayerStatsComponent>()->IncreaseSpeed(0.02f);
				break;
			case ItemComponent::ItemType::EARLY_DETONATOR:
				trigger.second->GetComponent<PlayerStatsComponent>()->AllowEarlyDetonation();
				break;
			default:
				break;
			}
			GetOwner()->m_MarkedForDestroy = true;
		}
	}
}

void ItemComponent::SetItemType(ItemType type)
{
	m_Type = type;
}
