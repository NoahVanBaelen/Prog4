#pragma once
#include "BaseComponent.h"

class VersusPlayerComponent final : public BaseComponent
{
public:
	VersusPlayerComponent(dae::GameObject* pOwner);

	VersusPlayerComponent(const VersusPlayerComponent& other) = delete;
	VersusPlayerComponent(VersusPlayerComponent&& other) = delete;
	VersusPlayerComponent& operator=(const VersusPlayerComponent& other) = delete;
	VersusPlayerComponent& operator=(VersusPlayerComponent&& other) = delete;

	void Update(float deltaTime) override;
	void SetStartPosition(glm::vec2 startPosition);
	void ResetToStartPosition();
	void GetKilled();
	float GetSpeed() const;

private:

	glm::vec2 m_StartPosition{};
	float m_Speed{ 0.05f };
	float m_WaitTimeMax{ 20.f };
	float m_WaitTimeCurrent{};
	bool m_GotKilled{ false };
};

