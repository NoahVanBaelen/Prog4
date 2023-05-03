#include "PlayerSpriteComponent.h"

PlayerSpriteComponent::PlayerSpriteComponent(dae::GameObject* pOwner)
	: BaseComponent(pOwner)
{}

void PlayerSpriteComponent::SetUpSpriteSheet(int row, int column)
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
		m_TextureFullheight = m_pRenderComponent->GetTextureHeight();
		m_Height = m_TextureFullheight / row;
		m_Width = m_pRenderComponent->GetTextureWidth() / column;

		//m_pRenderComponent->SetDestinationWidthAndHeight(m_Width, m_Height);

		m_MaxRow = row;
		m_MaxColumn = column;

		SetSourceRect();
	}
}

void PlayerSpriteComponent::AddObserver(Observer* observer)
{
	m_MovementElements->AddObserver(observer);
}

void PlayerSpriteComponent::MoveUp()
{
	if (m_CurrentRow != 1)
	{
		m_CurrentRow = 1;
	}

	MoveColumn();

	SetSourceRect();
}

void PlayerSpriteComponent::MoveDown()
{
	if (m_CurrentRow != 0)
	{
		m_CurrentRow = 0;
	}

	MoveColumn();
	SetSourceRect();
}

void PlayerSpriteComponent::MoveRight()
{
	if (m_CurrentRow != 2)
	{
		m_CurrentRow = 2;
	}

	MoveColumn();

	if (m_pRenderComponent)
	{
		//m_pRenderComponent->SetSourceRect(m_Width * m_CurrentColumn, m_TextureFullheight - (m_Height * m_CurrentColumn), -m_Width, m_Height);
	}
}

void PlayerSpriteComponent::MoveLeft()
{
	if (m_CurrentRow != 2)
	{
		m_CurrentRow = 2;
	}

	MoveColumn();
	SetSourceRect();
}

void PlayerSpriteComponent::StandStill()
{
	m_CurrentColumn = 1;
	SetSourceRect();
}

void PlayerSpriteComponent::MoveColumn()
{
	m_CurrentColumn = (m_CurrentColumn + 1) % m_MaxColumn;
}

void PlayerSpriteComponent::SetSourceRect()
{
	if (m_pRenderComponent)
	{
		//m_pRenderComponent->SetSourceRect(m_Width * m_CurrentColumn, m_TextureFullheight - (m_Height * m_CurrentColumn), m_Width, m_Height);
	}
}
