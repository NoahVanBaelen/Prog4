#pragma once
#include <glm/glm.hpp>
#include "GameObject.h"


class Command
{
public: 
	explicit Command(dae::GameObject* gameObject);
	virtual ~Command() = default;
	Command(const Command& other) = delete;
	Command(Command&& other) = delete;
	Command& operator=(const Command& other) = delete;
	Command& operator=(Command&& other) = delete;

	virtual void Execute(float deltaTime);

protected:
	dae::GameObject* m_pGameObject;
};

class MoveCommand final : public Command
{
public:
	MoveCommand(dae::GameObject* gameObject, float speed, glm::vec3 direction);
	void Execute(float deltaTime) override;
private:
	glm::vec3 m_Direction;
	float m_Speed;
};

class AddScoreCommand final : public Command
{
public:
	AddScoreCommand(dae::GameObject* gameObject, int point);
	void Execute(float deltaTime) override;
private:
	int m_Points;
};

class LoseLiveCommand final : public Command
{
public:
	LoseLiveCommand(dae::GameObject* gameObject);
	void Execute(float deltaTime) override;
};
