#pragma once
#include "BaseComponent.h"
#include "NVB_Collision_System.h"

class CollisionComponent final : public BaseComponent
{
public:
	CollisionComponent(dae::GameObject* pOwner);

	CollisionComponent(const CollisionComponent& other) = delete;
	CollisionComponent(CollisionComponent&& other) = delete;
	CollisionComponent& operator=(const CollisionComponent& other) = delete;
	CollisionComponent& operator=(CollisionComponent&& other) = delete;

	void Update(float deltaTime) override;
	void SetUpCollisionBox(const int width, const int height, const int collisionGroupID,const std::vector<int> collisionGroupsToCollideWithIDs);
	void SetIsStatic(bool isStatic);
	void RemoveCollisionBox();
	CollisionBox GetCollisionBox();

private:
	CollisionBox m_CollisionBox;
	bool m_IsStatic{ false };
};

