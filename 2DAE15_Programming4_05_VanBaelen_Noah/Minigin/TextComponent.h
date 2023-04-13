#pragma once
#include "BaseComponent.h"
#include <SDL_ttf.h>
#include "Font.h"
#include <string>
#include <memory>
#include "RenderComponent.h"

class TextComponent final : public BaseComponent
{
public:
	TextComponent(dae::GameObject* pOwner);

	TextComponent(const TextComponent& other) = delete;
	TextComponent(TextComponent&& other) = delete;
	TextComponent& operator=(const TextComponent& other) = delete;
	TextComponent& operator=(TextComponent&& other) = delete;

	void SetText(const std::string& text);
	void SetColor(const SDL_Color& color);
	void SetFont(std::shared_ptr<dae::Font> font);

private:
	void SetTexture();
	bool HasRenderComponent();

	std::shared_ptr<dae::Font> m_font;
	std::string m_text;
	SDL_Color m_color;
	std::shared_ptr<RenderComponent> m_pRenderComponent;
};

