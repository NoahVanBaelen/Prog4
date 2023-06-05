#pragma once
#include "BaseComponent.h"

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
private:
	void Explode();
	float m_TimeToExplode;
	int m_WideOffset{0};
	int m_HeightOffset{0};
	int m_FirePower{1};
	bool m_Exploded{ false };
	int m_SoundID;
};

