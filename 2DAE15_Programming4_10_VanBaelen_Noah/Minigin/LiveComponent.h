#pragma once
#include "BaseComponent.h"
#include "Subject.h"
class LiveComponent final : public BaseComponent
{
public:
	LiveComponent(dae::GameObject* pOwner);

	LiveComponent(const LiveComponent& other) = delete;
	LiveComponent(LiveComponent&& other) = delete;
	LiveComponent& operator=(const LiveComponent& other) = delete;
	LiveComponent& operator=(LiveComponent&& other) = delete;

	void SetLives(int lives);
	int GetLives();
	void LoseLive();
	void AddObserver(Observer* observer);
	void SetRespawn(glm::vec3 respawnPosition);

private:
	void Respawn();

	glm::vec3 m_RespawnPosition;
	int m_Lives;
	std::unique_ptr<Subject> m_UIElements = std::make_unique<Subject>();
};

