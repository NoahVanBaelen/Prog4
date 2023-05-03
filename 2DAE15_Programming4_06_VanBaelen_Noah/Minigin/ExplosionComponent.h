#pragma once
#include "BaseComponent.h"
#include "RenderComponent.h"
class ExplosionComponent final : public BaseComponent
{
public:
	ExplosionComponent(dae::GameObject* pOwner);

	void Update(float deltaTime) override;

	ExplosionComponent(const ExplosionComponent& other) = delete;
	ExplosionComponent(ExplosionComponent&& other) = delete;
	ExplosionComponent& operator=(const ExplosionComponent& other) = delete;
	ExplosionComponent& operator=(ExplosionComponent&& other) = delete;

	void SetUpSpriteSheet(int row, int column);

private:

	void SetTextureSrc();
	
	int m_FlamePower{ 1 };
	std::shared_ptr<RenderComponent> m_pRenderComponent;
	float m_MaxExplosionTime{ 20.f };
	float m_CurrentExplosionTime{};

	int m_MaxRow{};
	int m_MaxColumn{};
	int m_CurrentColumn{ 0 };

	int m_Width{};
	int m_Height{};
	int m_TextureFullheight{};
};

