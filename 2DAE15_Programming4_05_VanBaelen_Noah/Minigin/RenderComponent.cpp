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
		const auto& pos{GetOwner()->GetWorldPosition()};
		dae::Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
	}
}

void RenderComponent::SetTexture(SDL_Texture* texture)
{
	m_pTexture = std::make_shared<dae::Texture2D>(texture);
}

void RenderComponent::SetTexture(const std::string& filename)
{
	m_pTexture = dae::ResourceManager::GetInstance().LoadTexture(filename);
}
