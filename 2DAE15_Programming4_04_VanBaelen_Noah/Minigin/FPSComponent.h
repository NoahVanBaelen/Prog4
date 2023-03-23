#pragma once
#include "BaseComponent.h"
#include <SDL_ttf.h>
#include <string>
#include <memory>

class TextComponent;
class FPSComponent final : public BaseComponent
{
public:
	FPSComponent(dae::GameObject* pOwner);

	FPSComponent(const FPSComponent& other) = delete;
	FPSComponent(FPSComponent&& other) = delete;
	FPSComponent& operator=(const FPSComponent& other) = delete;
	FPSComponent& operator=(FPSComponent&& other) = delete;

	void Update(float deltaTime) override;

private:
	void SetFPS();
	bool HasTextComponent();

	int m_numberOfFrames;
	float m_timePassed;
	std::shared_ptr<TextComponent> m_pTextComponent;
};

