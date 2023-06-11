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

#include "ItemComponent.h"
#include "SpawnComponent.h"
#include "EnemyObserver.h"
#include "LevelObserver.h"
#include "DoorComponent.h"
#include "SceneManager.h"
#include "GameState.h"

GridComponent::GridComponent(dae::GameObject* pOwner)
	:BaseComponent(pOwner)
{
}

void GridComponent::Update(float deltaTime)
{
	if (m_HasTouchDoor)
	{
		m_CurrentTimeDoorTouch += deltaTime * 0.01f;
		if (m_CurrentTimeDoorTouch >= m_MaxTimeDoorTouch)
		{
			m_HasTouchDoor = false;
			m_CurrentTimeDoorTouch = 0;
		}
	}
}

void GridComponent::InitializeGrid(int rowSize, int columnSize, float tileWidth, float tileHeight)
{
	m_RowSize = rowSize;
	m_ColumnSize = columnSize;
	m_TileWidth = tileWidth;
	m_TileHeight = tileHeight;
}

void GridComponent::AddLevel(std::string filePath)
{
	m_LevelFilePaths.push_back(filePath);
}

void GridComponent::GoToLevel(int levelIndex)
{
	if (dae::SceneManager::GetInstance().GetState()->GetCurrentMode() == GameState::CurrentMode::VERSUS && levelIndex > 0)
	{
		m_currentLevel = 0;
		GetOwner()->DestroyAllChildren();
		m_Subjects->NotifyObservers(Observer::Event::RELOAD_LEVEL, GetOwner()); 
		m_Subjects->NotifyObservers(Observer::Event::END_OF_GAME, GetOwner());
		dae::SceneManager::GetInstance().SetState(std::make_shared<MainMenuState>(dae::SceneManager::GetInstance().GetSceneByName("MainMenu").get()));
	}

	if (levelIndex<m_LevelFilePaths.size())
	{
		m_currentLevel = levelIndex;
		GetOwner()->DestroyAllChildren();
		m_Subjects->NotifyObservers(Observer::Event::RELOAD_LEVEL, GetOwner());
		InitializeLevel(m_LevelFilePaths[levelIndex]);
	}
	else
	{
		m_currentLevel = 0;
		GetOwner()->DestroyAllChildren();
		m_Subjects->NotifyObservers(Observer::Event::RELOAD_LEVEL, GetOwner());
		m_Subjects->NotifyObservers(Observer::Event::END_OF_GAME, GetOwner());
		dae::SceneManager::GetInstance().SetState(std::make_shared<ScoreScreenState>(dae::SceneManager::GetInstance().GetSceneByName("ScoreScreen").get()));
	}
}

void GridComponent::GoToStartLevel()
{
	m_Subjects->NotifyObservers(Observer::Event::START_GAME, GetOwner());
	GoToLevel(0);
}

void GridComponent::AddScoreHolders(std::shared_ptr<dae::GameObject> highScore)
{
	m_HighScore = highScore;
}

void GridComponent::InitializeLevel(std::string filePath)
{

	int blockCollisionGroupID{ 2 };
	std::vector<int>unBreakableBlockCollideWithIDs{ 1,3 };

	for (int row = 0; row < m_RowSize; row++)
	{
		for (int column = 0; column < m_ColumnSize; column++)
		{
			Tile tile{};
			tile.row = row;
			tile.column = column;
			tile.top = m_TileHeight * row;
			tile.left = m_TileWidth * column;

			if (row == 0 || row == m_RowSize - 1 || column == 0 || column == m_ColumnSize - 1 || (row % 2 == 0 && column % 2 == 0))
			{
				tile.hasObjectThatStopsExplosion = true;
				auto go_Block = std::make_shared<dae::GameObject>();
				go_Block->GetComponent<TransformComponent>()->SetLocalPosition(glm::vec3(m_TileWidth * column, m_TileWidth * row, 0.f));
				go_Block->AddComponent<CollisionComponent>()->SetUpCollisionBox(static_cast<int>(m_TileWidth), static_cast<int>(m_TileHeight), blockCollisionGroupID, unBreakableBlockCollideWithIDs);
				go_Block->GetComponent<CollisionComponent>()->SetIsStatic(true);
				go_Block->SetParent(GetOwner()->shared_from_this(), true);
			}

			m_Tiles.push_back(tile);
		}
	}

	if (std::ifstream is{ filePath })
	{
		float textureScale{ 1.3f };
		rapidjson::IStreamWrapper isw{ is };
		rapidjson::Document level;
		level.ParseStream(isw);

		auto go_Door = std::make_shared<dae::GameObject>();
		std::vector<int> doorCollideWithIDs{ 1 };
		go_Door->AddComponent<RenderComponent>();
		go_Door->GetComponent<RenderComponent>()->SetTexture("Resources/Door.png");
		go_Door->GetComponent<RenderComponent>()->ScaleTexture(textureScale);
		go_Door->AddComponent<TriggerComponent>()->SetUpCollisionBox(static_cast<int>(m_TileWidth), static_cast<int>(m_TileHeight), doorCollideWithIDs);

		int amountOfEnemies{ 0 };
		if (level.HasMember("enemyInfo"))
		{
			const rapidjson::Value& infoArray = level["enemyInfo"];
			std::vector<int>emenyCollideWithIDs{ 0 };
			std::vector<int>enemyTriggerWithIDs{ 1 };
			int enemyCollisionGroupID{ 3 };
			for (rapidjson::Value::ConstValueIterator index = infoArray.Begin(); index != infoArray.End(); ++index)
			{
				const rapidjson::Value& info = *index;
				const rapidjson::Value& row = info[0];
				const rapidjson::Value& column = info[1];
				const rapidjson::Value& type = info[2];

				auto go_Enemy = std::make_shared<dae::GameObject>();
				go_Enemy->AddComponent<RenderComponent>();
				go_Enemy->GetComponent<TransformComponent>()->SetLocalPosition(glm::vec3(m_TileWidth * column.GetFloat(), m_TileHeight * row.GetFloat(), 0.f));
				go_Enemy->AddComponent<TriggerComponent>()->SetUpCollisionBox(static_cast<int>(m_TileWidth), static_cast<int>(m_TileHeight), enemyTriggerWithIDs);
				go_Enemy->AddComponent<CollisionComponent>()->SetUpCollisionBox(static_cast<int>(m_TileWidth / 2), static_cast<int>(m_TileHeight / 2), enemyCollisionGroupID, emenyCollideWithIDs);

				switch (type.GetInt())//Set Enemy Type
				{
				case 0:
					go_Enemy->GetComponent<RenderComponent>()->SetTexture("Resources/Balloom.png");
					go_Enemy->GetComponent<RenderComponent>()->ScaleTexture(textureScale);
					go_Enemy->AddComponent<EnemyLogicComponent>()->SetUpEnemy(EnemyLogicComponent::EnemySpeed::slow, EnemyLogicComponent::EnemyDifficulty::lowDifficulty,
						100, glm::vec2{ static_cast<int>(m_TileWidth), static_cast<int>(m_TileHeight) });
					break;
				case 1:
					go_Enemy->GetComponent<RenderComponent>()->SetTexture("Resources/Oneal.png");
					go_Enemy->GetComponent<RenderComponent>()->ScaleTexture(textureScale);
					go_Enemy->AddComponent<EnemyLogicComponent>()->SetUpEnemy(EnemyLogicComponent::EnemySpeed::normal, EnemyLogicComponent::EnemyDifficulty::normalDifficulty,
						200, glm::vec2{ static_cast<int>(m_TileWidth), static_cast<int>(m_TileHeight) });
					break;
				case 2:
					go_Enemy->GetComponent<RenderComponent>()->SetTexture("Resources/Doll.png");
					go_Enemy->GetComponent<RenderComponent>()->ScaleTexture(textureScale);
					go_Enemy->AddComponent<EnemyLogicComponent>()->SetUpEnemy(EnemyLogicComponent::EnemySpeed::normal, EnemyLogicComponent::EnemyDifficulty::lowDifficulty,
						400, glm::vec2{ static_cast<int>(m_TileWidth), static_cast<int>(m_TileHeight) });
					break;
				case 3:
					go_Enemy->GetComponent<RenderComponent>()->SetTexture("Resources/Minvo.png");
					go_Enemy->GetComponent<RenderComponent>()->ScaleTexture(textureScale);
					go_Enemy->AddComponent<EnemyLogicComponent>()->SetUpEnemy(EnemyLogicComponent::EnemySpeed::fast, EnemyLogicComponent::EnemyDifficulty::normalDifficulty,
						800, glm::vec2{ static_cast<int>(m_TileWidth), static_cast<int>(m_TileHeight) });
					break;
				default:
					break;
				}

				go_Enemy->GetComponent<EnemyLogicComponent>()->AddObserver(new EnemyObserver{ go_Door.get() });
				go_Enemy->GetComponent<EnemyLogicComponent>()->AddObserver(new EnemyObserver{ m_HighScore.get() });
				go_Enemy->SetParent(GetOwner()->shared_from_this(), true);
				++amountOfEnemies;
			}
		}

		go_Door->AddComponent<DoorComponent>()->SetAmountOfEnemy(amountOfEnemies);
		go_Door->GetComponent<DoorComponent>()->AddObserver(new LevelObserver{ GetOwner() });

		if (level.HasMember("blockInfo"))
		{
			std::vector<int>blockCollideWithIDs{ 1, 3 };
			const rapidjson::Value& infoArray = level["blockInfo"];
			for (rapidjson::Value::ConstValueIterator index = infoArray.Begin(); index != infoArray.End(); ++index)
			{
				const rapidjson::Value& info = *index;
				const rapidjson::Value& row = info[0];
				const rapidjson::Value& column = info[1];
				const rapidjson::Value& item = info[2];

				auto go_Block = std::make_shared<dae::GameObject>();
				go_Block->AddComponent<RenderComponent>();
				go_Block->GetComponent<RenderComponent>()->SetTexture("Resources/Block.png");
				go_Block->GetComponent<RenderComponent>()->ScaleTexture(textureScale);
				go_Block->GetComponent<TransformComponent>()->SetLocalPosition(glm::vec3(m_TileWidth * column.GetFloat(), m_TileWidth * row.GetFloat(), 0.f));
				go_Block->AddComponent<CollisionComponent>()->SetUpCollisionBox(static_cast<int>(m_TileWidth), static_cast<int>(m_TileHeight), blockCollisionGroupID, blockCollideWithIDs);
				go_Block->GetComponent<CollisionComponent>()->SetIsStatic(true);

				std::vector<int> itemsCollideWithIDs{ 1 };
				auto go_Item = std::make_shared<dae::GameObject>();
				switch (item.GetInt())
				{
				case 1:
					go_Item->AddComponent<RenderComponent>()->SetTexture("Resources/ItemBomb.png");
					go_Item->GetComponent<RenderComponent>()->ScaleTexture(textureScale);
					go_Item->AddComponent<TriggerComponent>()->SetUpCollisionBox(static_cast<int>(m_TileWidth), static_cast<int>(m_TileHeight), itemsCollideWithIDs);
					go_Item->AddComponent<ItemComponent>()->SetItemType(ItemComponent::ItemType::EXTRA_BOMB);
					go_Block->AddComponent<SpawnComponent>()->SetObjectToSpawn(go_Item);
					break;
				case 2:
					go_Item->AddComponent<RenderComponent>()->SetTexture("Resources/ItemFire.png");
					go_Item->GetComponent<RenderComponent>()->ScaleTexture(textureScale);
					go_Item->AddComponent<TriggerComponent>()->SetUpCollisionBox(static_cast<int>(m_TileWidth), static_cast<int>(m_TileHeight), itemsCollideWithIDs);
					go_Item->AddComponent<ItemComponent>()->SetItemType(ItemComponent::ItemType::INCREASE_FIRE);
					go_Block->AddComponent<SpawnComponent>()->SetObjectToSpawn(go_Item);
					break;
				case 3:
					go_Item->AddComponent<RenderComponent>()->SetTexture("Resources/ItemSpeed.png");
					go_Item->GetComponent<RenderComponent>()->ScaleTexture(textureScale);
					go_Item->AddComponent<TriggerComponent>()->SetUpCollisionBox(static_cast<int>(m_TileWidth), static_cast<int>(m_TileHeight), itemsCollideWithIDs);
					go_Item->AddComponent<ItemComponent>()->SetItemType(ItemComponent::ItemType::INCREASE_SPEED);
					go_Block->AddComponent<SpawnComponent>()->SetObjectToSpawn(go_Item);
					break;
				case 4:
					go_Item->AddComponent<RenderComponent>()->SetTexture("Resources/ItemRemote.png");
					go_Item->GetComponent<RenderComponent>()->ScaleTexture(textureScale);
					go_Item->AddComponent<TriggerComponent>()->SetUpCollisionBox(static_cast<int>(m_TileWidth), static_cast<int>(m_TileHeight), itemsCollideWithIDs);
					go_Item->AddComponent<ItemComponent>()->SetItemType(ItemComponent::ItemType::EARLY_DETONATOR);
					go_Block->AddComponent<SpawnComponent>()->SetObjectToSpawn(go_Item);
					break;
				case 5:
					go_Block->AddComponent<SpawnComponent>()->SetObjectToSpawn(go_Door);
					break;
				default:
					break;
				}
				
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

		if (closest.block->HasComponent<SpawnComponent>())//spawnItem
		{
			closest.block->GetComponent<SpawnComponent>()->Spawn(GetOwner()->shared_from_this());
		}
	}

	return closest.hasObjectThatStopsExplosion;
}

void GridComponent::GoToNextLevel()
{
	if (m_HasTouchDoor){return;}
	m_HasTouchDoor = true;
	++m_currentLevel;
	GoToLevel(m_currentLevel);
}

void GridComponent::AddObserver(Observer* observer)
{
	m_Subjects->AddObserver(observer);
}

void GridComponent::GameOverGrid()
{
	GetOwner()->DestroyAllChildren();
}
