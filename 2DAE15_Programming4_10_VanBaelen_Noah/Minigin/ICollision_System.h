#pragma once
#include "Transform.h"
#include "GameObject.h"
#include <vector>

struct CollisionBox
{
	glm::vec2 centerPosition{ 0,0 };
	int widthBox{ 0 };
	int heightBox{ 0 };
	int collisionGroupID{ -1 };//our id of with group we belong to
	std::vector<int> groupIdToCollideWith{};//groups we collide with
	dae::GameObject* pOwner;//The GameObject that owns this CollisionBox
	int left{ 0 };
	int right{ 0 };
	int bottom{ 0 };
	int top{ 0 };
	bool isStatic = false;
};

class CollisionComponent;
class ICollision_System //Interface Handels collision
{
public:
	ICollision_System() = default;

	ICollision_System(const ICollision_System& other) = delete;
	ICollision_System(ICollision_System&& other) = delete;
	ICollision_System& operator=(const ICollision_System& other) = delete;
	ICollision_System& operator=(ICollision_System&& other) = delete;

	virtual ~ICollision_System() = default;
	virtual void AddCollisionBox(CollisionComponent* collisionBox) = 0;
	virtual std::pair<int,int> HasCollision(CollisionComponent* ourCollisionBox) = 0;
	virtual std::pair<bool, dae::GameObject*> RayCast(glm::vec2 rayStart, glm::vec2 rayEnd, std::vector<int> groupIDsToCollideWith) = 0;
	virtual std::pair<bool, dae::GameObject*> HasTrigger(const CollisionBox& ourCollisionBox) = 0;
	virtual void RemoveCollisionBox(CollisionComponent* collisionBox) = 0;
	virtual void SetUpComleteMessage() = 0;
};

