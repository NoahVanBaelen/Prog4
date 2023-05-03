#pragma once
#include "BaseComponent.h"
#include "RenderComponent.h"
#include "Subject.h"
class PlayerSpriteComponent final : public BaseComponent
{
public:
	PlayerSpriteComponent(dae::GameObject* pOwner);

	PlayerSpriteComponent(const PlayerSpriteComponent& other) = delete;
	PlayerSpriteComponent(PlayerSpriteComponent&& other) = delete;
	PlayerSpriteComponent& operator=(const PlayerSpriteComponent& other) = delete;
	PlayerSpriteComponent& operator=(PlayerSpriteComponent&& other) = delete;

	void SetUpSpriteSheet(int row, int column);
	void AddObserver(Observer* observer);

	void MoveUp();
	void MoveDown();
	void MoveRight();
	void MoveLeft();
	void StandStill();

private:

	void MoveColumn();
	void SetSourceRect();

	float m_XPos{ 0 };
	float m_YPos{ 0 };
	int m_Width{};
	int m_Height{};
	int m_TextureFullheight{};

	int m_MaxRow{};
	int m_MaxColumn{};
	int m_CurrentRow{ 1 };
	int m_CurrentColumn{ 2 };

	std::shared_ptr<RenderComponent> m_pRenderComponent;
	std::unique_ptr<Subject> m_MovementElements = std::make_unique<Subject>();
};

