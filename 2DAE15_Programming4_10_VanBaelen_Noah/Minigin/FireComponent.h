#pragma once
#include "BaseComponent.h"

class FireComponent final : public BaseComponent
{
public:
	FireComponent(dae::GameObject* pOwner);

	FireComponent(const FireComponent& other) = delete;
	FireComponent(FireComponent&& other) = delete;
	FireComponent& operator=(const FireComponent& other) = delete;
	FireComponent& operator=(FireComponent&& other) = delete;

	void Update(float deltaTime) override;

private:
	float m_LifeTime{ 12.f };
};

