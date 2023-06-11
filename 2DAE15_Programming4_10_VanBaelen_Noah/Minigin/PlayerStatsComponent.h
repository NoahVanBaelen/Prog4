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

	void Update(float deltaTime) override;
	void SetStartPosition(glm::vec2 startPosition);

	float GetSpeed() const;
	int GetLives() const;
	int GetMaxBombs() const;
	int GetCurrentBombs() const;
	int GetFirePower() const;
	int GetSpeedCount() const;
	bool GetCanDetonateEarly()const;

	void DetonateEarly() const;

	void IncreaseSpeed(float speedIncrease);
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

	bool GetIsDead() const;

private:

	glm::vec2 m_StartPosition;
	float m_Speed;
	int m_Lives;
	int m_MaxAmountOfBombs;//max amount of bombs you may place
	int m_CurrentAmountOfBombs;//amount of bombs that are currently placed
	int m_FirePower;
	bool m_AllowToDetonateBombEarly;
	int m_SpeedCount{ 0 };

	bool m_GotHurt{ false };
	bool m_GotSomeThing{ false };
	bool m_IsDead{ false };

	float m_MaxWaitPickUpTime{ 5.0f };
	float m_MaxWaitHurtTime{ 10.0f };
	float m_CurrentCanPickUpTime{ 0 };
	float m_CurrentCanGetHurtAgainTime{ 0 };

	std::unique_ptr<Subject> m_Subjects = std::make_unique<Subject>();
};

