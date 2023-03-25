#pragma once
#include <glm/glm.hpp>
#include "GameObject.h"


class Command
{
public: 
	explicit Command(std::shared_ptr<dae::GameObject> gameObject);

	Command(const Command& other) = delete;
	Command(Command&& other) = delete;
	Command& operator=(const Command& other) = delete;
	Command& operator=(Command&& other) = delete;

	virtual void Execute(float deltaTime);

protected:
	std::shared_ptr<dae::GameObject> m_pGameObject;
	//std::shared_ptr<dae::GameObject> GetGameObject() const { return m_pGameObject; }
};

class MoveCommand final : public Command
{
public:
	MoveCommand(std::shared_ptr<dae::GameObject> gameObject, float speed, glm::vec3 direction);
	void Execute(float deltaTime) override;
private:
	glm::vec3 m_Direction;
	float m_Speed;
};
