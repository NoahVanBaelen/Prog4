#pragma once
#include "BaseComponent.h"

class CoopLogicComponent final : public BaseComponent
{
public:
	CoopLogicComponent(dae::GameObject* pOwner);

	CoopLogicComponent(const CoopLogicComponent& other) = delete;
	CoopLogicComponent(CoopLogicComponent&& other) = delete;
	CoopLogicComponent& operator=(const CoopLogicComponent& other) = delete;
	CoopLogicComponent& operator=(CoopLogicComponent&& other) = delete;

	void SetPlayerCount(int playerCount);
	void LowerAmountActivePlayers();
private:
	int m_MaxPlayerCount{};
	int m_CurrentPlayerCount{};
};

