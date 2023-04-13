#include "Command.h"
#include "TransformComponent.h"
#include "ScoreComponent.h"
#include "LiveComponent.h"

Command::Command(dae::GameObject* gameObject)
	:m_pGameObject{gameObject}
{}

void Command::Execute(float)
{}

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

AddScoreCommand::AddScoreCommand(dae::GameObject* gameObject, int point)
	:Command(gameObject)
	,m_Points(point)
{}

void AddScoreCommand::Execute(float)
{
	m_pGameObject->GetComponent<ScoreComponent>()->AddScore(m_Points);
}

LoseLiveCommand::LoseLiveCommand(dae::GameObject* gameObject)
	:Command(gameObject)
{}

void LoseLiveCommand::Execute(float)
{
	m_pGameObject->GetComponent<LiveComponent>()->LoseLive();
}
