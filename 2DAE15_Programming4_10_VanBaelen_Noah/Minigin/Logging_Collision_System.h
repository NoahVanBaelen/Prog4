#pragma once
#include "ICollision_System.h"
#include "iostream"

class Logging_Collision_System final : public ICollision_System
{
	std::unique_ptr<ICollision_System> _real_cs;
public:

	Logging_Collision_System(const Logging_Collision_System& other) = delete;
	Logging_Collision_System(Logging_Collision_System&& other) = delete;
	Logging_Collision_System& operator=(const Logging_Collision_System& other) = delete;
	Logging_Collision_System& operator=(Logging_Collision_System&& other) = delete;

	Logging_Collision_System(std::unique_ptr<ICollision_System>&& cs) { _real_cs = std::move(cs); }
	virtual void AddCollisionBox(CollisionComponent* collisionBox) override;
	virtual std::pair<int, int> HasCollision(CollisionComponent* ourCollisionBox) override;
	virtual std::pair<bool, dae::GameObject*> HasTrigger(const CollisionBox& ourCollisionBox) override;
	virtual std::pair<bool, dae::GameObject*> RayCast(glm::vec2 rayStart, glm::vec2 rayEnd, std::vector<int> groupIDsToCollideWith) override;
	virtual void RemoveCollisionBox(CollisionComponent* collisionBox) override;
	virtual void SetUpComleteMessage() override;
};

