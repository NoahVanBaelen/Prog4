#pragma once
#include <memory>
#include "BaseComponent.h"
#include "Transform.h"
#include "Texture2D.h"
#include <iostream>
#include "TransformComponent.h"
//#include "backends/imgui_impl_sdl2.h"
//#include "backends/imgui_impl_opengl2.h"
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

	/*void SetTextureVector(const float srcX, const float srcY, const int srcWidth, const int srcHeight, const float dstX, const float dstY, const int dstWidth, const int dstHeight);
	void SetTextureVectorSourcePos(const int index, const float srcX, const float srcY);

	void SetSourceRect(const float x, const float y, const int width, const int height);
	void SetDestinationWidthAndHeight(const int width, const int height);*/
	int GetTextureWidth();
	int GetTextureHeight();


private:

	//std::vector<std::unique_ptr<SDL_Rect>>m_pDstRectVector;
	//std::vector<std::unique_ptr<SDL_Rect>>m_pSrcRectVector;
	std::vector<float> m_VectorPosX;
	std::vector<float> m_VectorPosY;

	std::shared_ptr<dae::Texture2D> m_pTexture;
	//std::unique_ptr<SDL_Rect> m_pSrcRect{nullptr};
	int m_width{};
	int m_height{};
	bool m_UseTextureVector{ false };
};

