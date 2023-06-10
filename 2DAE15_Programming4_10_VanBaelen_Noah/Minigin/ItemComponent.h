#pragma once
#include "BaseComponent.h"
class ItemComponent final : public BaseComponent
{
public:

	enum class ItemType
	{
		EXTRA_BOMB = 1,
		INCREASE_FIRE = 2,
		INCREASE_SPEED = 3,
		EARLY_DETONATOR = 4,
	};

	ItemComponent(dae::GameObject* pOwner);

	ItemComponent(const ItemComponent& other) = delete;
	ItemComponent(ItemComponent&& other) = delete;
	ItemComponent& operator=(const ItemComponent& other) = delete;
	ItemComponent& operator=(ItemComponent&& other) = delete;

	void Update(float deltaTime) override;
	void SetItemType(ItemType type);

private:
	ItemType m_Type;
};

