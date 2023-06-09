#pragma once
#include "BaseComponent.h"
#include "NVB_Collision_System.h"

class TriggerComponent final : public BaseComponent
{
public:
	TriggerComponent(dae::GameObject* pOwner);

	TriggerComponent(const TriggerComponent& other) = delete;
	TriggerComponent(TriggerComponent&& other) = delete;
	TriggerComponent& operator=(const TriggerComponent& other) = delete;
	TriggerComponent& operator=(TriggerComponent&& other) = delete;

	void Update(float deltaTime) override;
	void SetUpCollisionBox(const int width, const int height, const std::vector<int> collisionGroupsToCollideWithIDs);
	std::pair<bool, dae::GameObject*> GetHasTriggerLastFrame();

private:
	CollisionBox m_CollisionBox;

	bool m_IsTriggerdThisFrame{ false };
	bool m_IsTriggerdLastFrame{ false };

	dae::GameObject* m_pGameObjectCollidedThisFrame{};
	dae::GameObject* m_pGameObjectCollidedLastFrame{};
};

