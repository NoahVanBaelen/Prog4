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

	if (!m_CanRender) {return;}
	if (m_pTexture != nullptr)
	{
		const auto& pos{ GetOwner()->GetWorldPosition() };
		dae::Renderer::GetInstance().RenderTexture(*m_pTexture, static_cast<float>(pos.x), static_cast<float>(pos.y), static_cast<float>(m_width), static_cast<float>(m_height));
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

void RenderComponent::SetCanRender(bool canRender)
{
	m_CanRender = canRender;
}
