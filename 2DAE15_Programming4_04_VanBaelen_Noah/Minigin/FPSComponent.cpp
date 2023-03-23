#include "FPSComponent.h"
#include "TextComponent.h"

FPSComponent::FPSComponent(dae::GameObject* pOwner)
	:m_numberOfFrames{0}
	,m_timePassed{0}
	,BaseComponent(pOwner)
{
}

void FPSComponent::Update(float deltaTime)
{
	++m_numberOfFrames;
	m_timePassed += deltaTime;
	if (m_timePassed >= 1000.f)
	{
		SetFPS();
		m_numberOfFrames = 0;
		m_timePassed = 0;
	}
}

void FPSComponent::SetFPS()
{
	if (HasTextComponent())
	{
		std::string fps{ "FPS: " + std::to_string(m_numberOfFrames) };
		m_pTextComponent->SetText(fps);
	}
}

bool FPSComponent::HasTextComponent()
{
	if (m_pTextComponent == nullptr)
	{
		if (GetOwner()->HasComponent<TextComponent>())
		{
			m_pTextComponent = GetOwner()->GetComponent<TextComponent>();
			return true;
		}
		return false;
	}
	return true;
}
