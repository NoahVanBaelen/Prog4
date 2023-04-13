#pragma once
#include "BaseComponent.h"
#include "Transform.h"

class TransformComponent final : public BaseComponent
{
public:
	TransformComponent(dae::GameObject* pOwner);

	TransformComponent(const TransformComponent& other) = delete;
	TransformComponent(TransformComponent&& other) = delete;
	TransformComponent& operator=(const TransformComponent& other) = delete;
	TransformComponent& operator=(TransformComponent&& other) = delete;

	const glm::vec3& GetWorldPosition();
	void SetLocalPosition(const glm::vec3& pos);
	const glm::vec3& GetLocalPosition() const;
	void SetPositionDirty();

private:
	void UpdateWorldPosition();

	dae::Transform m_localPosition;
	dae::Transform m_worldPosition;
	bool m_PositionIsDirty{ false };
};

