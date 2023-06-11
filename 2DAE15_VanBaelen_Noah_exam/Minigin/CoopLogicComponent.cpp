#include "CoopLogicComponent.h"
#include "SceneManager.h"
#include "GameState.h"

CoopLogicComponent::CoopLogicComponent(dae::GameObject* pOwner)
	:BaseComponent(pOwner)
{
}

void CoopLogicComponent::SetPlayerCount(int playerCount)
{
	m_MaxPlayerCount = playerCount;
	m_CurrentPlayerCount = playerCount;
}

void CoopLogicComponent::LowerAmountActivePlayers()
{
	--m_CurrentPlayerCount;
	if (m_CurrentPlayerCount == 0)
	{
		m_CurrentPlayerCount = m_MaxPlayerCount;
		dae::SceneManager::GetInstance().SetState(std::make_shared<ScoreScreenState>(dae::SceneManager::GetInstance().GetSceneByName("ScoreScreen").get()));
	}
}
