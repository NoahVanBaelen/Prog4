#include "ExplosionComponent.h"

ExplosionComponent::ExplosionComponent(dae::GameObject* pOwner)
	:BaseComponent(pOwner)
	,m_CurrentExplosionTime{m_MaxExplosionTime}
{
}

void ExplosionComponent::Update(float deltaTime)
{
	m_CurrentExplosionTime -= deltaTime;
	if (m_CurrentExplosionTime <= 0)
	{
		if (m_CurrentColumn == m_MaxColumn)
		{

		}
		else
		{
			++m_CurrentColumn;
			SetTextureSrc();
			m_CurrentExplosionTime = m_MaxExplosionTime;
		}
	}
}

void ExplosionComponent::SetUpSpriteSheet(int row, int column)
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

		m_MaxRow = row;
		m_MaxColumn = column;

		//const auto& pos{ GetOwner()->GetWorldPosition() };

		//float dstX { pos.x - (m_Width / 2) };
		//float dstY{ pos.y - (m_Width / 2) };

		/*m_pRenderComponent->SetTextureVector(m_Width * m_CurrentColumn, 0, m_Width, m_Height, dstX, dstY, m_Width, m_Height);
		for (int i = 0; i < m_FlamePower; i++)
		{
			if (i == m_FlamePower-1)
			{
				m_pRenderComponent->SetTextureVector(m_Width * m_CurrentColumn, m_TextureFullheight - (m_Height * 2), m_Width, m_Height, dstX, dstY + m_Height, m_Width, m_Height);
				m_pRenderComponent->SetTextureVector(m_Width * m_CurrentColumn, m_TextureFullheight - (m_Height * 2), m_Width, m_Height, dstX, dstY - m_Height, m_Width, m_Height);
				m_pRenderComponent->SetTextureVector(m_Width * m_CurrentColumn, m_TextureFullheight - (m_Height * 2), m_Width, m_Height, dstX + m_Width, dstY, m_Width, m_Height);
				m_pRenderComponent->SetTextureVector(m_Width * m_CurrentColumn, m_TextureFullheight - (m_Height * 2), m_Width, m_Height, dstX - m_Width, dstY, m_Width, m_Height);
			}
			else
			{
				m_pRenderComponent->SetTextureVector(m_Width * m_CurrentColumn, m_TextureFullheight - (m_Height * 1), m_Width, m_Height, dstX, dstY + m_Height, m_Width, m_Height);
				m_pRenderComponent->SetTextureVector(m_Width * m_CurrentColumn, m_TextureFullheight - (m_Height * 1), m_Width, m_Height, dstX, dstY - m_Height, m_Width, m_Height);
				m_pRenderComponent->SetTextureVector(m_Width * m_CurrentColumn, m_TextureFullheight - (m_Height * 1), m_Width, m_Height, dstX + m_Width, dstY, m_Width, m_Height);
				m_pRenderComponent->SetTextureVector(m_Width * m_CurrentColumn, m_TextureFullheight - (m_Height * 1), m_Width, m_Height, dstX - m_Width, dstY, m_Width, m_Height);
			}
		}*/
	}
}

void ExplosionComponent::SetTextureSrc()
{
	/*m_pRenderComponent->SetTextureVectorSourcePos(0,m_Width * m_CurrentColumn, 0);

	for (int i = 0; i < m_FlamePower; i++)
	{
		if (i == m_FlamePower - 1)
		{
			m_pRenderComponent->SetTextureVectorSourcePos(4 * i + 1, m_Width * m_CurrentColumn, m_TextureFullheight - (m_Height * 2));
			m_pRenderComponent->SetTextureVectorSourcePos(4 * i + 2, m_Width * m_CurrentColumn, m_TextureFullheight - (m_Height * 2));
			m_pRenderComponent->SetTextureVectorSourcePos(4 * i + 3, m_Width * m_CurrentColumn, m_TextureFullheight - (m_Height * 2));
			m_pRenderComponent->SetTextureVectorSourcePos(4 * i + 4, m_Width * m_CurrentColumn, m_TextureFullheight - (m_Height * 2));
		}
		else
		{
			m_pRenderComponent->SetTextureVectorSourcePos(4 * i + 1, m_Width * m_CurrentColumn, m_TextureFullheight - (m_Height * 1));
			m_pRenderComponent->SetTextureVectorSourcePos(4 * i + 2, m_Width * m_CurrentColumn, m_TextureFullheight - (m_Height * 1));
			m_pRenderComponent->SetTextureVectorSourcePos(4 * i + 3, m_Width * m_CurrentColumn, m_TextureFullheight - (m_Height * 1));
			m_pRenderComponent->SetTextureVectorSourcePos(4 * i + 4, m_Width * m_CurrentColumn, m_TextureFullheight - (m_Height * 1));
		}
	}*/
}
