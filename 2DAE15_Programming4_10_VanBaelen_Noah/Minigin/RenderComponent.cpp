#include "RenderComponent.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "ResourceManager.h"
#include <utility>

RenderComponent::RenderComponent(dae::GameObject* pOwner)
	:m_pTexture{nullptr}
	,BaseComponent(pOwner)
{

}

void RenderComponent::Render() const
{
	if (m_pTexture != nullptr)
	{
		if (m_UseTextureVector)
		{
			for (int i = 0; i < static_cast<int>(m_pDstRectVector.size()); i++)
			{
				dae::Renderer::GetInstance().RenderTexture(*m_pTexture, *m_pDstRectVector[i].get(), *m_pSrcRectVector[i].get());
			}
		}
		else
		{
			if (m_pSrcRect)
			{
				const auto& pos{ GetOwner()->GetWorldPosition() };
				dae::Renderer::GetInstance().RenderTexture(*m_pTexture, static_cast<float>(pos.x), static_cast<float>(pos.y), static_cast<float>(m_width), static_cast<float>(m_height), *m_pSrcRect.get());
			}
			else
			{
				const auto& pos{ GetOwner()->GetWorldPosition() };
				dae::Renderer::GetInstance().RenderTexture(*m_pTexture, static_cast<float>(pos.x), static_cast<float>(pos.y), static_cast<float>(m_width), static_cast<float>(m_height));
			}
		}
	}
}

void RenderComponent::SetTexture(SDL_Texture* texture)
{
	m_pTexture = std::make_shared<dae::Texture2D>(texture);
	SDL_QueryTexture(m_pTexture->GetSDLTexture(), nullptr, nullptr, &m_width, &m_height);
}

void RenderComponent::SetTexture(const std::string& filename)
{
	m_pTexture = dae::ResourceManager::GetInstance().LoadTexture(filename);
	SDL_QueryTexture(m_pTexture->GetSDLTexture(), nullptr, nullptr, &m_width, &m_height);
}

void RenderComponent::SetTextureVector(const float srcX, const float srcY, const int srcWidth, const int srcHeight, const float dstX, const float dstY, const int dstWidth, const int dstHeight)
{
	m_UseTextureVector = true;

	m_pSrcRectVector.push_back(std::make_unique<SDL_Rect>(static_cast<int>(srcX), static_cast<int>(srcY), srcWidth, srcHeight));
	m_pDstRectVector.push_back(std::make_unique<SDL_Rect>(static_cast<int>(dstX), static_cast<int>(dstY), dstWidth, dstHeight));
}

void RenderComponent::SetTextureVectorSourcePos(const int index, const float srcX, const float srcY)
{
	m_pSrcRectVector[index]->x = static_cast<int>(srcX);
	m_pSrcRectVector[index]->y = static_cast<int>(srcY);
}

void RenderComponent::SetSourceRect(const float x, const float y, const int width, const int height)
{
	m_pSrcRect = std::make_unique<SDL_Rect>(static_cast<int>(x),static_cast<int>(y),width,height);
}

void RenderComponent::SetDestinationWidthAndHeight(const int width, const int height)
{
	m_width = width;
	m_height = height;
}

int RenderComponent::GetTextureWidth()
{
	int width;
	SDL_QueryTexture(m_pTexture->GetSDLTexture(), nullptr, nullptr, &width, nullptr);
	return width;
}

int RenderComponent::GetTextureHeight()
{
	int height;
	SDL_QueryTexture(m_pTexture->GetSDLTexture(), nullptr, nullptr, nullptr, &height);
	return height;
}

void RenderComponent::ScaleTexture(const float scale)
{
	m_width = static_cast<int>(m_width * scale);
	m_height = static_cast<int>(m_height * scale);
}
