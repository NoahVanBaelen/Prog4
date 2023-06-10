#pragma once
#include "BaseComponent.h"

class SpawnComponent final : public BaseComponent
{
public:
	SpawnComponent(dae::GameObject* pOwner);

	SpawnComponent(const SpawnComponent& other) = delete;
	SpawnComponent(SpawnComponent&& other) = delete;
	SpawnComponent& operator=(const SpawnComponent& other) = delete;
	SpawnComponent& operator=(SpawnComponent&& other) = delete;

	void Spawn(std::shared_ptr<dae::GameObject> parent);
	void SetObjectToSpawn(std::shared_ptr<dae::GameObject> gameObject);

private:
	std::shared_ptr<dae::GameObject> m_pObjectToSpawn;
};

