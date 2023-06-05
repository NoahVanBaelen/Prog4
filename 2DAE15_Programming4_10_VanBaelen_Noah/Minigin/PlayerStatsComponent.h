#pragma once
#include "BaseComponent.h"

class PlayerStatsComponent final : public BaseComponent
{
public:
	PlayerStatsComponent(dae::GameObject* pOwner);

	PlayerStatsComponent(const  PlayerStatsComponent& other) = delete;
	PlayerStatsComponent(PlayerStatsComponent&& other) = delete;
	PlayerStatsComponent& operator=(const  PlayerStatsComponent& other) = delete;
	PlayerStatsComponent& operator=(PlayerStatsComponent&& other) = delete;

	float GetSpeed() const;
	int GetPoints() const;
	int GetLives() const;
	int GetMaxBombs() const;
	int GetCurrentBombs() const;
	int GetFirePower() const;

	void IncreaseSpeed(float speedIncrease);
	void IncreasePoints(int points);
	void DecreaseLives();
	void IncreaseMaxBombs();
	void IncreaseCurrentBombs();
	void DecreaseCurrentBombs();
	void IncreaseFirePower();

	void ResetPowerUpStats();
	void StartNewGame();

private:

	float m_Speed;
	int m_Points;
	int m_Lives;
	int m_MaxAmountOfBombs;//max amount of bombs you may place
	int m_CurrentAmountOfBombs;//amount of bombs that are currently placed
	int m_FirePower;
};

