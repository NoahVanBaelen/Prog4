#include "GridComponent.h"

#include <iostream>
#include <rapidjson/rapidjson.h>
#include "rapidjson/document.h"
#include "rapidjson/stream.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/filereadstream.h"
#include <fstream>

#include "RenderComponent.h"


GridComponent::GridComponent(dae::GameObject* pOwner)
	:BaseComponent(pOwner)
{
}

void GridComponent::InitializeGrid(int rowSize, int columnSize, float tileWidth, float tileHeight)
{
	m_RowSize = rowSize;
	m_ColumnSize = columnSize;
	m_TileWidth = tileWidth;
	m_TileHeight = tileHeight;

	for (int row = 0; row < m_RowSize; row++)
	{
		for (int column = 0; column < m_ColumnSize; column++)
		{
			Tile tile{};
			tile.row = row;
			tile.column = column;
			tile.top = tileHeight * row;
			tile.left = tileWidth * column;

			if (row == 0 || row == rowSize-1 || column == 0 || column == columnSize-1 || (row % 2 == 0 && column % 2 == 0))
			{
				tile.hasObjectThatStopsExplosion = true;
			}

			m_Tiles.push_back(tile);
		}
	}
}

void GridComponent::InitializeLevel(std::string filePath, float textureScale)
{
	if (std::ifstream is{ filePath })
	{
		rapidjson::IStreamWrapper isw{ is };
		rapidjson::Document level;
		level.ParseStream(isw);

		if (level.HasMember("blockPositions"))
		{
			const rapidjson::Value& positionArray = level["blockPositions"];
			for (rapidjson::Value::ConstValueIterator index = positionArray.Begin(); index != positionArray.End(); ++index)
			{
				const rapidjson::Value& position = *index;
				const rapidjson::Value& row = position[0];
				const rapidjson::Value& column = position[1];

				auto go_Block = std::make_shared<dae::GameObject>();
				go_Block->AddComponent<RenderComponent>();
				go_Block->GetComponent<RenderComponent>()->SetTexture("Resources/Block.png");
				go_Block->GetComponent<RenderComponent>()->ScaleTexture(textureScale);
				go_Block->GetComponent<TransformComponent>()->SetLocalPosition(glm::vec3(m_TileWidth * column.GetFloat(), m_TileWidth * row.GetFloat(), 0.f));
				GetOwner()->AddChild(go_Block, true);

				for (Tile& tile : m_Tiles)
				{
					if (tile.row == row.GetInt() && tile.column == column.GetInt())
					{
						tile.block = go_Block;
						tile.hasBreakableBlockOnTile = true;
					}
				}
			}
		}

		if (level.HasMember("enemyPositions"))
		{
			const rapidjson::Value& positionArray = level["enemyPositions"];
			for (rapidjson::Value::ConstValueIterator index = positionArray.Begin(); index != positionArray.End(); ++index)
			{
				const rapidjson::Value& position = *index;
				const rapidjson::Value& row = position[0];
				const rapidjson::Value& column = position[1];

				auto go_Enemy = std::make_shared<dae::GameObject>();
				go_Enemy->AddComponent<RenderComponent>();
				go_Enemy->GetComponent<RenderComponent>()->SetTexture("Resources/Enemie1.png");
				go_Enemy->GetComponent<RenderComponent>()->ScaleTexture(textureScale);
				go_Enemy->GetComponent<TransformComponent>()->SetLocalPosition(glm::vec3(m_TileWidth * column.GetFloat(), m_TileHeight * row.GetFloat(), 0.f));
				GetOwner()->AddChild(go_Enemy, true);
			}
		}
	}
}

Tile GridComponent::ClosestTile(float xPos, float yPos)
{
	Tile closestTile{};
	float closestDistance{ (m_RowSize * m_TileHeight) + (m_ColumnSize * m_TileWidth) };
	for (const Tile& tile : m_Tiles)
	{
		float xDistance{ xPos - tile.left };
		float yDistance{ yPos - tile.top };

		if (xDistance < 0) {xDistance *= -1;}
		if (yDistance < 0) { yDistance *= -1; }

		if ((xDistance + yDistance) < closestDistance )
		{
			closestDistance = xDistance + yDistance;
			closestTile = tile;
		}
	}
	return closestTile;
}

bool GridComponent::IsAnUnBreakableTile(float xPos, float yPos)
{
	Tile closest{ ClosestTile(xPos,yPos) };

	if (closest.hasBreakableBlockOnTile)
	{
		closest.block->m_MarkedForDestroy = true;
	}

	return closest.hasObjectThatStopsExplosion;
}
