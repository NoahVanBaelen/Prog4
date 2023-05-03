#pragma once
#include "BaseComponent.h"
#include "RenderComponent.h"

class BombComponent final : public BaseComponent
{
public:
	BombComponent(dae::GameObject* pOwner);

	BombComponent(const BombComponent& other) = delete;
	BombComponent(BombComponent&& other) = delete;
	BombComponent& operator=(const BombComponent& other) = delete;
	BombComponent& operator=(BombComponent&& other) = delete;

	void Update(float deltaTime) override;
	void SetUpSpriteSheet(int row, int column);


private:

	void MoveColumn();
	void SetSourceRect();

	int m_Width{};
	int m_Height{};

	int m_MaxColumn{};
	int m_CurrentColumn{ 0 };

	float m_CurrentExplosionTime{ 180.f };

	float m_MaxSpriteTime{ 5.f };
	float m_CurrentSpriteTime{ 0 };

	std::shared_ptr<RenderComponent> m_pRenderComponent;
};

