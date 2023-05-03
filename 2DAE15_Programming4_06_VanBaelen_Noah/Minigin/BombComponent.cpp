#include "BombComponent.h"

BombComponent::BombComponent(dae::GameObject* pOwner)
	: BaseComponent(pOwner)
{
}

void BombComponent::Update(float deltaTime)
{
	m_CurrentSpriteTime -= deltaTime;
	if (m_CurrentSpriteTime <= 0)
	{
		MoveColumn();
	}

	m_CurrentExplosionTime -= deltaTime;
	if (m_CurrentExplosionTime <= 0)
	{
		
	}
}

void BombComponent::SetUpSpriteSheet(int row, int column)
{
	if (m_pRenderComponent == nullptr)
	{
		if (GetOwner()->HasComponent<RenderComponent>())
		{
			m_pRenderComponent = GetOwner()->GetComponent<RenderComponent>();
		}
	}

	if (m_pRenderComponent)
	{
		m_Height = m_pRenderComponent->GetTextureHeight() / row;
		m_Width = m_pRenderComponent->GetTextureWidth() / column;

		//m_pRenderComponent->SetDestinationWidthAndHeight(m_Width, m_Height);
		m_MaxColumn = column;

		SetSourceRect();
	}
}

void BombComponent::MoveColumn()
{
	m_CurrentColumn = (m_CurrentColumn + 1) % m_MaxColumn;
	SetSourceRect();
}

void BombComponent::SetSourceRect()
{
	if (m_pRenderComponent)
	{
		//m_pRenderComponent->SetSourceRect(m_Width * m_CurrentColumn, 0, m_Width, m_Height);
	}
}
