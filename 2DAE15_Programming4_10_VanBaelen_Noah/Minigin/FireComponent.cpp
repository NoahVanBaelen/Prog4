#include "FireComponent.h"

FireComponent::FireComponent(dae::GameObject* pOwner)
	:BaseComponent(pOwner)
{
}

void FireComponent::Update(float deltaTime)
{
	m_LifeTime -= deltaTime * 0.01f;
	if (m_LifeTime <= 0)
	{
		GetOwner()->m_MarkedForDestroy = true;
	}
}
