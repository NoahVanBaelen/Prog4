#pragma once
#include "BaseComponent.h"

struct Tile
{
	int row;
	int column;
	float left;
	float top;
	bool hasObjectThatStopsExplosion{ false };
	bool hasBreakableBlockOnTile{ false };
	std::shared_ptr<dae::GameObject>block;
};

class GridComponent final : public BaseComponent
{
public:
	GridComponent(dae::GameObject* pOwner);

	GridComponent(const  GridComponent& other) = delete;
	GridComponent(GridComponent&& other) = delete;
	GridComponent& operator=(const  GridComponent& other) = delete;
	GridComponent& operator=(GridComponent&& other) = delete;

	void InitializeGrid(int rowSize, int columnSize, float tileWidth, float tileHeight);
	void InitializeLevel(std::string filePath,float textureScale);

	Tile ClosestTile(float xPos, float yPos);
	void SetToClosestTileCenter(glm::vec2& position);
	bool IsAnUnBreakableTile(float xPos, float yPos);

private:
	int m_RowSize{0};
	int m_ColumnSize{0};
	float m_TileHeight{0};
	float m_TileWidth{0};

	std::vector<Tile> m_Tiles{};
};

