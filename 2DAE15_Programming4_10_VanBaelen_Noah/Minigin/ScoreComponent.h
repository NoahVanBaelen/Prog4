#pragma once
#include "BaseComponent.h"
#include "Subject.h"
class ScoreComponent final : public BaseComponent
{
public:
	ScoreComponent(dae::GameObject* pOwner);

	ScoreComponent(const ScoreComponent& other) = delete;
	ScoreComponent(ScoreComponent&& other) = delete;
	ScoreComponent& operator=(const ScoreComponent& other) = delete;
	ScoreComponent& operator=(ScoreComponent&& other) = delete;

	void AddScore(int points);
	int GetScore();
	void AddObserver(Observer* observer);

private:

	int m_Score;
	std::unique_ptr<Subject> m_UIElements = std::make_unique<Subject>();
};

