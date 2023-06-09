#pragma once
#include "BaseComponent.h"
#include "Subject.h"
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

	void Update(float deltaTime) override;

	void InitializeGrid(int rowSize, int columnSize, float tileWidth, float tileHeight);
	void AddLevel(std::string filePath);
	void GoToLevel(int levelIndex);
	void GoToStartLevel();
	void AddScoreHolders(std::shared_ptr<dae::GameObject> highScore);

	Tile ClosestTile(float xPos, float yPos);
	void SetToClosestTileCenter(glm::vec2& position);
	bool IsAnUnBreakableTile(float xPos, float yPos);
	void GoToNextLevel();
	void AddObserver(Observer* observer);
	void GameOverGrid();

private:

	void InitializeLevel(std::string filePath);

	int m_RowSize{0};
	int m_ColumnSize{0};
	float m_TileHeight{0};
	float m_TileWidth{0};
	int m_currentLevel{ 0 };

	float m_CurrentTimeDoorTouch{ 0 };
	float m_MaxTimeDoorTouch{ 15.f };
	bool m_HasTouchDoor{ false };

	std::vector<Tile> m_Tiles{};
	std::vector<std::string> m_LevelFilePaths{};
	std::unique_ptr<Subject> m_Subjects = std::make_unique<Subject>();

	std::shared_ptr<dae::GameObject> m_HighScore;
};

