#include "GridComponent.h"

#include <iostream>
#include <rapidjson/rapidjson.h>
#include "rapidjson/document.h"
#include "rapidjson/stream.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/filereadstream.h"
#include <fstream>

#include "RenderComponent.h"
#include "CollisionComponent.h"
#include "TriggerComponent.h"
#include "EnemyLogicComponent.h"


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
	int blockCollisionGroupID{ 2 };
	std::vector<int>blockCollideWithIDs{ 1,3 };

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
				auto go_Block = std::make_shared<dae::GameObject>();
				go_Block->GetComponent<TransformComponent>()->SetLocalPosition(glm::vec3(m_TileWidth * column, m_TileWidth * row, 0.f));
				go_Block->AddComponent<CollisionComponent>()->SetUpCollisionBox(static_cast<int>(m_TileWidth), static_cast<int>(m_TileHeight), blockCollisionGroupID, blockCollideWithIDs);
				go_Block->GetComponent<CollisionComponent>()->SetIsStatic(true);
				go_Block->SetParent(GetOwner()->shared_from_this(), true);
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
			int blockCollisionGroupID{ 2 };
			std::vector<int>blockCollideWithIDs{ 1, 3 };
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
				go_Block->AddComponent<CollisionComponent>()->SetUpCollisionBox(static_cast<int>(m_TileWidth), static_cast<int>(m_TileHeight), blockCollisionGroupID, blockCollideWithIDs);
				go_Block->GetComponent<CollisionComponent>()->SetIsStatic(true);
				go_Block->SetParent(GetOwner()->shared_from_this(), true);
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
			std::vector<int>emenyCollideWithIDs{ 0 };
			std::vector<int>enemyTriggerWithIDs{ 1 };
			int enemyCollisionGroupID{ 3 };
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
				go_Enemy->AddComponent<TriggerComponent>()->SetUpCollisionBox(static_cast<int>(m_TileWidth), static_cast<int>(m_TileHeight), enemyTriggerWithIDs);
				go_Enemy->AddComponent<CollisionComponent>()->SetUpCollisionBox(static_cast<int>(m_TileWidth/2), static_cast<int>(m_TileHeight/2), enemyCollisionGroupID, emenyCollideWithIDs);
				go_Enemy->AddComponent<EnemyLogicComponent>()->SetUpEnemy(EnemyLogicComponent::EnemySpeed::slow, EnemyLogicComponent::EnemyDifficulty::lowDifficulty, 
																		  100, glm::vec2{ static_cast<int>(m_TileWidth), static_cast<int>(m_TileHeight) });

				go_Enemy->SetParent(GetOwner()->shared_from_this(), true);
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

void GridComponent::SetToClosestTileCenter(glm::vec2& position)
{
	Tile closestTile = ClosestTile(position.x, position.y);
	position.x = closestTile.left;
	position.y = closestTile.top;
}

bool GridComponent::IsAnUnBreakableTile(float xPos, float yPos)
{
	Tile closest{ ClosestTile(xPos,yPos) };

	if (closest.hasBreakableBlockOnTile)
	{
		closest.block->m_MarkedForDestroy = true;
		closest.block->GetComponent<CollisionComponent>()->RemoveCollisionBox();
	}

	return closest.hasObjectThatStopsExplosion;
}
