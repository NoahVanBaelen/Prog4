#include "LiveComponent.h"
#include "UIDisplay.h"
#include "TransformComponent.h"

LiveComponent::LiveComponent(dae::GameObject* pOwner)
    :BaseComponent(pOwner)
    ,m_Lives{3}
    ,m_RespawnPosition{}
{
}

void LiveComponent::SetLives(int lives)
{
    m_Lives = lives;
}

int LiveComponent::GetLives()
{
    return m_Lives;
}

void LiveComponent::LoseLive()
{
    if (m_Lives != 0)
    {
        --m_Lives;
        m_UIElements->NotifyObservers(Observer::Event::LIVE_CHANGE, GetOwner());
    }
    Respawn();
}

void LiveComponent::AddObserver(Observer* observer)
{
    m_UIElements->AddObserver(observer);
}

void LiveComponent::SetRespawn(glm::vec3 respawnPosition)
{
    m_RespawnPosition = respawnPosition;
}

void LiveComponent::Respawn()
{
    GetOwner()->GetComponent<TransformComponent>()->SetLocalPosition(m_RespawnPosition);
}
