#include "ScoreComponent.h"

ScoreComponent::ScoreComponent(dae::GameObject* pOwner)
	:BaseComponent(pOwner)
	,m_Score{0}
{
}

void ScoreComponent::AddScore(int points)
{
	m_Score += points;
	m_UIElements->NotifyObservers(Observer::Event::SCORE_CHANGE, GetOwner());
}

int ScoreComponent::GetScore()
{
	return m_Score;
}

void ScoreComponent::AddObserver(Observer* observer)
{
	m_UIElements->AddObserver(observer);
}
