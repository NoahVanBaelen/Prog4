#pragma once
#include "BaseComponent.h"
#include "TransformComponent.h"
class MoveInCircleComponent : public BaseComponent
{
public:
	MoveInCircleComponent(dae::GameObject* pOwner);

	MoveInCircleComponent(const MoveInCircleComponent& other) = delete;
	MoveInCircleComponent(MoveInCircleComponent&& other) = delete;
	MoveInCircleComponent& operator=(const MoveInCircleComponent& other) = delete;
	MoveInCircleComponent& operator=(MoveInCircleComponent&& other) = delete;

	void FixedUpdate(float fixedTimeStep) override;
	void SetMoveCounterClockWise(bool moveCounterClockWise);
	void SetRadius(float radius);
	void SetCenter(const glm::vec3& center);
	void SetSpeed(float speed);
private:
	bool m_moveCounterClockWise{ false };
	float m_radius;
	float m_angle;
	float m_speed;
	glm::vec3 m_center;
	std::shared_ptr<TransformComponent> m_pTransformComponent;
};

