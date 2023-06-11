#pragma once
#include "BaseComponent.h"
#include "Subject.h"
class BombComponent final : public BaseComponent
{
public:
	BombComponent(dae::GameObject* pOwner);

	BombComponent(const  BombComponent& other) = delete;
	BombComponent(BombComponent&& other) = delete;
	BombComponent& operator=(const  BombComponent& other) = delete;
	BombComponent& operator=(BombComponent&& other) = delete;

	void Update(float deltaTime) override;
	void SetFireOffset(int wideOffset, int heightOffset);
	void SetFirePower(int firePower);
	void SetSoundID(int soundID);
	void EarlyDetonation();

	void AddObserver(Observer* observer);
private:
	void Explode();
	float m_TimeToExplode;
	int m_WideOffset{0};
	int m_HeightOffset{0};
	int m_FirePower{1};
	int m_SoundID;

	std::unique_ptr<Subject> m_Subjects = std::make_unique<Subject>();
};

