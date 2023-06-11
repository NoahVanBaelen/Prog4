#pragma once
#include "ICollision_System.h"

class CollisionComponent;
class NVB_Collision_System final : public ICollision_System
{
public:
	NVB_Collision_System() = default;
	~NVB_Collision_System() = default;
	NVB_Collision_System(const NVB_Collision_System& other) = delete;
	NVB_Collision_System(NVB_Collision_System&& other) = delete;
	NVB_Collision_System& operator=(const NVB_Collision_System& other) = delete;
	NVB_Collision_System& operator=(NVB_Collision_System&& other) = delete;

	void AddCollisionBox(CollisionComponent* collisionBox) override;
	std::pair<int,int> HasCollision(CollisionComponent* ourCollisionBox) override;
	std::pair<bool, dae::GameObject*> HasTrigger(const CollisionBox& ourCollisionBox) override;
	std::pair<bool, dae::GameObject*> RayCast(glm::vec2 rayStart, glm::vec2 rayEnd, std::vector<int> groupIDsToCollideWith) override;
	void RemoveCollisionBox(CollisionComponent* collisionBox) override;
	void SetUpComleteMessage() override;

protected:

	bool AreBoxesOverlapping(const CollisionBox& box1, const CollisionBox& box2);
	bool IsLineAndBoxOverlapping(const glm::vec2& start, const glm::vec2& end, const CollisionBox& box);
	bool CompareBoxesByDistance(const CollisionBox& box1, const CollisionBox& box2, const glm::vec2& rayStart);
	std::pair<int, int> CalculateOffset(const CollisionBox& box1, const CollisionBox& box2);
	std::vector<CollisionComponent*>m_pAllCollisionBoxes{};
};

