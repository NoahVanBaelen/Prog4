#pragma once
#include <glm/glm.hpp>
#include "GameObject.h"


class Command
{
public: 
	explicit Command();
	virtual ~Command() = default;
	Command(const Command& other) = delete;
	Command(Command&& other) = delete;
	Command& operator=(const Command& other) = delete;
	Command& operator=(Command&& other) = delete;

	virtual void Execute(float deltaTime);
};

class MoveCommand final : public Command
{
public:
	MoveCommand(dae::GameObject* gameObject, glm::vec3 direction);
	void Execute(float deltaTime) override;
private:
	glm::vec3 m_Direction;
	dae::GameObject* m_pGameObject;
};

class AddScoreCommand final : public Command
{
public:
	AddScoreCommand(dae::GameObject* gameObject, int point);
	void Execute(float deltaTime) override;
private:
	int m_Points;
	dae::GameObject* m_pGameObject;
};

class LoseLiveCommand final : public Command
{
public:
	LoseLiveCommand(dae::GameObject* gameObject);
	void Execute(float deltaTime) override;
private:
	dae::GameObject* m_pGameObject;
};

class SpawnBombCommand final : public Command
{
public:
	SpawnBombCommand(std::shared_ptr<dae::GameObject> player, std::shared_ptr<dae::GameObject> grid, int widthOffset, int heightOffset, int placeBombSoundID, int explosionSoundID);
	void Execute(float deltaTime) override;
private:
	std::shared_ptr<dae::GameObject> m_pPlayer;
	std::shared_ptr<dae::GameObject> m_pGrid;
	int m_WidthOffset;
	int m_HeightOffset;
	int m_PlaceBombSoundID;
	int m_ExplosionSoundID;
};
