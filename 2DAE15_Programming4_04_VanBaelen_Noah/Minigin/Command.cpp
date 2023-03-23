#include "Command.h"
#include "TransformComponent.h"

Command::Command(dae::GameObject* gameObject)
	:m_pGameObject{gameObject}
{}

Command::~Command()
{
	delete m_pGameObject;
	m_pGameObject = nullptr;
}

MoveCommand::MoveCommand(dae::GameObject* gameObject, float speed, glm::vec3 direction)
	:Command(gameObject)
	,m_Speed(speed)
	,m_Direction(direction)
{}

void MoveCommand::Execute(float deltaTime)
{
	glm::vec3 newMovement = m_Direction * (m_Speed * deltaTime);
	glm::vec3 currentPosition = m_pGameObject->GetWorldPosition();

	m_pGameObject->GetComponent<TransformComponent>()->SetLocalPosition(currentPosition + newMovement);
}