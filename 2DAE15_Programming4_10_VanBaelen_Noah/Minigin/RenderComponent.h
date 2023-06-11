#pragma once
#include <memory>
#include "BaseComponent.h"
#include "Transform.h"
#include "Texture2D.h"
#include <iostream>
#include "TransformComponent.h"
#include <SDL.h>
#include <vector>

class RenderComponent final : public BaseComponent
{
public:
	RenderComponent(dae::GameObject* pOwner);

	RenderComponent(const RenderComponent& other) = delete;
	RenderComponent(RenderComponent&& other) = delete;
	RenderComponent& operator=(const RenderComponent& other) = delete;
	RenderComponent& operator=(RenderComponent&& other) = delete;

	void Render() const;
	void SetTexture(SDL_Texture* texture);
	void SetTexture(const std::string& filename);

	int GetTextureWidth();
	int GetTextureHeight();
	void ScaleTexture(const float scale);

	void SetCanRender(bool canRender);

private:

	std::shared_ptr<dae::Texture2D> m_pTexture;
	int m_width{};
	int m_height{};
	bool m_CanRender{ true };
};

