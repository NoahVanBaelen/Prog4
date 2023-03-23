#include "MoveInCircleComponent.h"

MoveInCircleComponent::MoveInCircleComponent(dae::GameObject* pOwner)
	:m_radius{0.f}
	,m_angle{0.f}
	,m_speed{1.f}
	,BaseComponent(pOwner)
{
	m_center = GetOwner()->GetWorldPosition();
	m_pTransformComponent = GetOwner()->GetComponent<TransformComponent>();
}

void MoveInCircleComponent::FixedUpdate(float fixedTimeStep)
{
	if (!m_moveCounterClockWise)
	{
		m_angle += glm::radians(fixedTimeStep * m_speed);
	}
	else
	{
		m_angle -= glm::radians(fixedTimeStep * m_speed);
	}

	float xPos = 0;
	float yPos = 0;

	if (GetOwner()->GetParent() != nullptr)
	{
		m_center = GetOwner()->GetParent()->GetWorldPosition();
		xPos = m_radius * cosf(m_angle) + m_center.x;
		yPos = m_radius * sinf(m_angle) + m_center.y;
		m_pTransformComponent->SetLocalPosition(glm::vec3(xPos - m_center.x, yPos - m_center.y, m_center.z));
	}
	else
	{
		xPos = m_radius * cosf(m_angle) + m_center.x;
		yPos = m_radius * sinf(m_angle) + m_center.y;
		m_pTransformComponent->SetLocalPosition(glm::vec3(xPos, yPos, m_center.z));
	}
}

void MoveInCircleComponent::SetMoveCounterClockWise(bool moveCounterClockWise)
{
	m_moveCounterClockWise = moveCounterClockWise;
}

void MoveInCircleComponent::SetRadius(float radius)
{
	m_radius = radius;
}

void MoveInCircleComponent::SetCenter(const glm::vec3& center)
{
	m_center = center;
}

void MoveInCircleComponent::SetSpeed(float speed)
{
	m_speed = speed;
}
