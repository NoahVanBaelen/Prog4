#pragma once
#include "BaseComponent.h"
#include "Subject.h"
class PlayerStatsComponent final : public BaseComponent
{
public:
	PlayerStatsComponent(dae::GameObject* pOwner);

	PlayerStatsComponent(const  PlayerStatsComponent& other) = delete;
	PlayerStatsComponent(PlayerStatsComponent&& other) = delete;
	PlayerStatsComponent& operator=(const  PlayerStatsComponent& other) = delete;
	PlayerStatsComponent& operator=(PlayerStatsComponent&& other) = delete;

	void SetStartPosition(glm::vec2 startPosition);

	float GetSpeed() const;
	int GetPoints() const;
	int GetLives() const;
	int GetMaxBombs() const;
	int GetCurrentBombs() const;
	int GetFirePower() const;

	void DetonateEarly() const;

	void IncreaseSpeed(float speedIncrease);
	void IncreasePoints(int points);
	void DecreaseLives();
	void IncreaseMaxBombs();
	void IncreaseCurrentBombs();
	void DecreaseCurrentBombs();
	void IncreaseFirePower();
	void AllowEarlyDetonation();

	void ResetPowerUpStats();
	void StartNewGame();
	void AddObserver(Observer* observer);
	void ResetToStartPosition();

private:

	glm::vec2 m_StartPosition;
	float m_Speed;
	int m_Points;
	int m_Lives;
	int m_MaxAmountOfBombs;//max amount of bombs you may place
	int m_CurrentAmountOfBombs;//amount of bombs that are currently placed
	int m_FirePower;
	bool m_AllowToDetonateBombEarly;

	std::unique_ptr<Subject> m_Subjects = std::make_unique<Subject>();
};

