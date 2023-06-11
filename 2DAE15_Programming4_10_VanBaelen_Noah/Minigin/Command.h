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

class DetonateBombCommand final : public Command
{
public:
	DetonateBombCommand(std::shared_ptr<dae::GameObject> player);
	void Execute(float deltaTime) override;
private:
	std::shared_ptr<dae::GameObject> m_pPlayer;
};

class MoveInListDownCommand final : public Command
{
public:
	MoveInListDownCommand(std::shared_ptr<dae::GameObject> icon, std::vector<glm::vec2> positions);
	void Execute(float deltaTime) override;
private:
	std::shared_ptr<dae::GameObject> m_pIcon;
	std::vector<glm::vec2> m_Positions;
};

class MoveInListUpCommand final : public Command
{
public:
	MoveInListUpCommand(std::shared_ptr<dae::GameObject> icon, std::vector<glm::vec2> positions);
	void Execute(float deltaTime) override;
private:
	std::shared_ptr<dae::GameObject> m_pIcon;
	std::vector<glm::vec2> m_Positions;
};

class SelectModeCommand final : public Command
{
public:
	SelectModeCommand(std::shared_ptr<dae::GameObject> icon, int positionYMode1, int positionYMode2, int positionYMode3);
	void Execute(float deltaTime) override;
private:
	std::shared_ptr<dae::GameObject> m_pIcon;
	int m_PositionYMode1{};
	int m_PositionYMode2{};
	int m_PositionYMode3{};
};