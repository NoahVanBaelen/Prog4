#include "PlayerStatsComponent.h"
#include "TransformComponent.h"

PlayerStatsComponent::PlayerStatsComponent(dae::GameObject* pOwner)
    :BaseComponent(pOwner)
{
    StartNewGame();
}

void PlayerStatsComponent::SetStartPosition(glm::vec2 startPosition)
{
    m_StartPosition = startPosition;
}

float PlayerStatsComponent::GetSpeed() const
{
    return m_Speed;
}

int PlayerStatsComponent::GetPoints() const
{
    return m_Points;
}

int PlayerStatsComponent::GetLives() const
{
    return m_Lives;
}

int PlayerStatsComponent::GetMaxBombs() const
{
    return m_MaxAmountOfBombs;
}

int PlayerStatsComponent::GetCurrentBombs() const
{
    return m_CurrentAmountOfBombs;
}

int PlayerStatsComponent::GetFirePower() const
{
    return m_FirePower;
}

void PlayerStatsComponent::DetonateEarly() const
{
    if (m_AllowToDetonateBombEarly)
    {
        m_Subjects->NotifyObservers(Observer::Event::REMOTE, GetOwner());
    }
}

void PlayerStatsComponent::IncreaseSpeed(float speedIncrease)
{
    m_Speed += speedIncrease;
}

void PlayerStatsComponent::IncreasePoints(int points)
{
    m_Points += points;
}

void PlayerStatsComponent::DecreaseLives()
{
    --m_Lives;
    ResetPowerUpStats();
    ResetToStartPosition();
}

void PlayerStatsComponent::IncreaseMaxBombs()
{
    ++m_MaxAmountOfBombs;
}

void PlayerStatsComponent::IncreaseCurrentBombs()
{
    ++m_CurrentAmountOfBombs;
}

void PlayerStatsComponent::DecreaseCurrentBombs()
{
    --m_CurrentAmountOfBombs;
    if (m_CurrentAmountOfBombs < 0)//shouldn't be possible
    {
        m_CurrentAmountOfBombs = 0;
    }
}

void PlayerStatsComponent::IncreaseFirePower()
{
    ++m_FirePower;
}

void PlayerStatsComponent::AllowEarlyDetonation()
{
    m_AllowToDetonateBombEarly = true;
}

void PlayerStatsComponent::ResetPowerUpStats()
{
    m_Speed = 0.08f;
    m_MaxAmountOfBombs = 1;
    m_CurrentAmountOfBombs = 0;
    m_FirePower = 1;
    m_AllowToDetonateBombEarly = false;
}

void PlayerStatsComponent::StartNewGame()
{
    m_Points = 0;
    m_Lives = 3;
    ResetPowerUpStats();
}

void PlayerStatsComponent::AddObserver(Observer* observer)
{
    m_Subjects->AddObserver(observer);
}

void PlayerStatsComponent::ResetToStartPosition()
{
    glm::vec3 position = GetOwner()->GetWorldPosition();
    position.x = m_StartPosition.x;
    position.y = m_StartPosition.y;

    GetOwner()->GetComponent<TransformComponent>()->SetLocalPosition(position);
}
