#pragma once
#include <glm/glm.hpp>
#include "GameObject.h"


class Command
{
public: 
	explicit Command(dae::GameObject* gameObject);
	virtual ~Command();
	virtual void Execute(float deltaTime);

protected:
	dae::GameObject* m_pGameObject;

protected:
	dae::GameObject* GetGameObject() const { return m_pGameObject; }
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
