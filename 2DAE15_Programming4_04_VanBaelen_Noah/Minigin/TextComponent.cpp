#include "TextComponent.h"
#include "TransformComponent.h"
#include "Renderer.h"
#include <stdexcept>
#include "ResourceManager.h"
#include <utility>


TextComponent::TextComponent(dae::GameObject* pOwner)
	:m_text{" "} //Needs to be " " instead of "" otherwise surf in SetTexture becomes a nullptr
	,m_color{ 255,255,255 }
	,BaseComponent(pOwner)
{
	m_font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
}

void TextComponent::SetText(const std::string& text)
{
	m_text = text;
	SetTexture();
}

void TextComponent::SetColor(const SDL_Color& color)
{
	m_color = color;
	SetTexture();
}

void TextComponent::SetFont(std::shared_ptr<dae::Font> font)
{
	if (font != nullptr)
	{
		m_font = font;
		SetTexture();
	}
}

void TextComponent::SetTexture()
{
	if (HasRenderComponent())
	{
		const auto surf = TTF_RenderText_Blended(m_font->GetFont(), m_text.c_str(), m_color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(dae::Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_pRenderComponent->SetTexture(texture);
	}
}

bool TextComponent::HasRenderComponent()
{
	if (m_pRenderComponent == nullptr)
	{
		if (GetOwner()->HasComponent<RenderComponent>())
		{
			m_pRenderComponent = GetOwner()->GetComponent<RenderComponent>();
			return true;
		}
		return false;
	}
	return true;
}
