#include "PlayerStatsComponent.h"
#include "TransformComponent.h"

PlayerStatsComponent::PlayerStatsComponent(dae::GameObject* pOwner)
    :BaseComponent(pOwner)
{
    StartNewGame();
}

void PlayerStatsComponent::Update(float deltaTime)
{
    if (m_GotSomeThing)//to prevent getting called every frame
    {
        m_CurrentCanPickUpTime += deltaTime * 0.01f;
        if (m_CurrentCanPickUpTime >= m_MaxWaitTime)
        {
            m_GotSomeThing = false;
        }
    }

    if (m_GotHurt) // to prevent getting called every frame
    {
        m_CurrentCanGetHurtAgainTime += deltaTime * 0.01f;
        if (m_CurrentCanGetHurtAgainTime >= m_MaxWaitTime)
        {
            m_GotHurt = false;
        }
    }
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

int PlayerStatsComponent::GetSpeedCount() const
{
    return m_SpeedCount;
}

bool PlayerStatsComponent::GetCanDetonateEarly() const
{
    return m_AllowToDetonateBombEarly;
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
    if (m_GotSomeThing) { return; };
    m_Speed += speedIncrease;
    ++m_SpeedCount;
    m_Subjects->NotifyObservers(Observer::Event::CHANGE_IN_PLAYER_STATS, GetOwner());
    m_GotSomeThing = true;
}

void PlayerStatsComponent::IncreasePoints(int points)
{
    m_Points += points;
}

void PlayerStatsComponent::DecreaseLives()
{
    if (m_GotHurt) { return; };
    --m_Lives;
    m_Subjects->NotifyObservers(Observer::Event::PLAYER_DIES, GetOwner());
    ResetPowerUpStats();
    ResetToStartPosition();
    m_GotHurt = true;
}

void PlayerStatsComponent::IncreaseMaxBombs()
{
    if (m_GotSomeThing) { return; };
    ++m_MaxAmountOfBombs;
    m_Subjects->NotifyObservers(Observer::Event::CHANGE_IN_PLAYER_STATS, GetOwner());
    m_GotSomeThing = true;
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
    if (m_GotSomeThing) { return; };
    ++m_FirePower;
    m_Subjects->NotifyObservers(Observer::Event::CHANGE_IN_PLAYER_STATS, GetOwner());
    m_GotSomeThing = true;
}

void PlayerStatsComponent::AllowEarlyDetonation()
{
    if (m_GotSomeThing) { return; };
    m_AllowToDetonateBombEarly = true;
    m_Subjects->NotifyObservers(Observer::Event::CHANGE_IN_PLAYER_STATS, GetOwner());
    m_GotSomeThing = true;
}

void PlayerStatsComponent::ResetPowerUpStats()
{
    m_Speed = 0.08f;
    m_SpeedCount = 0;
    m_MaxAmountOfBombs = 1;
    m_CurrentAmountOfBombs = 0;
    m_FirePower = 1;
    m_AllowToDetonateBombEarly = false;
    m_Subjects->NotifyObservers(Observer::Event::CHANGE_IN_PLAYER_STATS, GetOwner());
}

void PlayerStatsComponent::StartNewGame()
{
    m_Points = 0;
    m_Lives = 3;
    m_Subjects->NotifyObservers(Observer::Event::PLAYER_RESET_LIVES, GetOwner());
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
