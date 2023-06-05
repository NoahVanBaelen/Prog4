#include "PlayerStatsComponent.h"

PlayerStatsComponent::PlayerStatsComponent(dae::GameObject* pOwner)
    :BaseComponent(pOwner)
{
    StartNewGame();
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

void PlayerStatsComponent::ResetPowerUpStats()
{
    m_Speed = 0.1f;
    m_MaxAmountOfBombs = 1;
    m_CurrentAmountOfBombs = 0;
    m_FirePower = 1;
}

void PlayerStatsComponent::StartNewGame()
{
    m_Points = 0;
    m_Lives = 3;
    ResetPowerUpStats();
}
