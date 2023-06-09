#pragma once
#include "ICollision_System.h"
#include <iostream>

class Null_Collision_System final : public ICollision_System
{
	virtual void AddCollisionBox(CollisionComponent*) override {};
	virtual std::pair<int, int> HasCollision(CollisionComponent*) override { return std::pair<int, int>{}; };
	virtual std::pair<bool, dae::GameObject*> HasTrigger(const CollisionBox& ) override { return std::pair<bool, dae::GameObject*>(false,nullptr); };
	virtual std::pair<bool, dae::GameObject*> RayCast(glm::vec2, glm::vec2, std::vector<int>) override { return std::pair<bool, dae::GameObject*>(false, nullptr); };
	virtual void RemoveCollisionBox(CollisionComponent*) override {};
	virtual void SetUpComleteMessage() override { std::cout << "Created Null_Collision_System\n"; };
};

static std::unique_ptr<ICollision_System> _cs_instance;

class CollisionServicelocator final
{

public:
	CollisionServicelocator(const CollisionServicelocator& other) = delete;
	CollisionServicelocator(CollisionServicelocator&& other) = delete;
	CollisionServicelocator& operator=(const CollisionServicelocator& other) = delete;
	CollisionServicelocator& operator=(CollisionServicelocator&& other) = delete;

	static ICollision_System& get_collision_system() { return *_cs_instance; }
	static void register_collision_system(std::unique_ptr<ICollision_System>&& cs) 
	{ 
		//_cs_instance = cs == nullptr ? std::make_unique<Null_Collision_System>() : std::move(cs); 
		if (cs == nullptr) {
			_cs_instance = std::make_unique<Null_Collision_System>();
		}
		else {
			_cs_instance = std::move(cs);
		}
	}
};

