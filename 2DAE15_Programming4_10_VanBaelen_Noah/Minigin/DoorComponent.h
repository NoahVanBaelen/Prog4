#pragma once
#include "BaseComponent.h"
class DoorComponent final : public BaseComponent
{
public:
	DoorComponent(dae::GameObject* pOwner);

	DoorComponent(const DoorComponent& other) = delete;
	DoorComponent(DoorComponent&& other) = delete;
	DoorComponent& operator=(const DoorComponent& other) = delete;
	DoorComponent& operator=(DoorComponent&& other) = delete;

	void Update(float deltaTime) override;
	void SetAmountOfEnemy(int amount);
	void DecreaseCurrentCount();

private:
	int m_AmountOfEnemies{ 0 };
};

