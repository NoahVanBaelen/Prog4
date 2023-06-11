#include "VersusPlayerComponent.h"
#include "TransformComponent.h"
#include "TriggerComponent.h"
#include "PlayerStatsComponent.h"

VersusPlayerComponent::VersusPlayerComponent(dae::GameObject* pOwner)
	:BaseComponent(pOwner)
{
}

void VersusPlayerComponent::Update(float deltaTime)
{
	if (m_GotKilled == true)
	{
		m_WaitTimeCurrent += deltaTime * 0.01f;
		if (m_WaitTimeCurrent >= m_WaitTimeMax)
		{
			m_WaitTimeCurrent = 0;
			m_GotKilled = false;
		}
	}
	else
	{
		std::pair<bool, dae::GameObject*> trigger{ GetOwner()->GetComponent<TriggerComponent>()->GetHasTriggerLastFrame() };
		if (trigger.first == true && trigger.second->HasComponent<PlayerStatsComponent>())
		{
			trigger.second->GetComponent<PlayerStatsComponent>()->DecreaseLives();
		}
	}
}

void VersusPlayerComponent::SetStartPosition(glm::vec2 startPosition)
{
	m_StartPosition = startPosition;
}

void VersusPlayerComponent::ResetToStartPosition()
{
	glm::vec3 position = GetOwner()->GetWorldPosition();
	position.x = m_StartPosition.x;
	position.y = m_StartPosition.y;

	GetOwner()->GetComponent<TransformComponent>()->SetLocalPosition(position);
}

void VersusPlayerComponent::GetKilled()
{
	m_GotKilled = true;
	ResetToStartPosition();
}

float VersusPlayerComponent::GetSpeed() const
{
	if (m_GotKilled)
	{
		return 0;
	}
	return m_Speed;
}
