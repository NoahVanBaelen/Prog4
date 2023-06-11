#pragma once
#include "BaseComponent.h"
#include "Subject.h"
class EnemyLogicComponent final : public BaseComponent
{
public:
	EnemyLogicComponent(dae::GameObject* pOwner);

	EnemyLogicComponent(const EnemyLogicComponent& other) = delete;
	EnemyLogicComponent(EnemyLogicComponent&& other) = delete;
	EnemyLogicComponent& operator=(const EnemyLogicComponent& other) = delete;
	EnemyLogicComponent& operator=(EnemyLogicComponent&& other) = delete;

	enum EnemySpeed
	{
		slow = 1,
		normal = 2,
		fast = 3,
	};

	enum EnemyDifficulty
	{
		lowDifficulty = 1,
		normalDifficulty = 2,
	};

	void Update(float deltaTime) override;
	void SetUpEnemy(EnemySpeed speed, EnemyDifficulty difficulty, int score, glm::vec2 rayLenght);
	void GetKilled();
	void AddObserver(Observer* observer);
	int GetScore() const;

private:

	float m_Speed{};
	EnemyDifficulty m_Difficulty;
	int m_Score;
	glm::vec2 m_Target;
	glm::vec2 m_rayLenght;
	bool m_foundPlayer{ false };

	std::unique_ptr<Subject> m_Subjects = std::make_unique<Subject>();
};

