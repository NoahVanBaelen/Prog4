#include "Command.h"
#include "TransformComponent.h"
#include "ScoreComponent.h"
#include "LiveComponent.h"
#include "RenderComponent.h"
#include "BombComponent.h"
#include "GridComponent.h"
#include "PlayerStatsComponent.h"

#include "Logging_Sound_System.h"
#include "Servicelocator.h"
#include "SDL_Sound_System.h"

#include "CollisionComponent.h"
#include "BombObserver.h"

#include "SceneManager.h"
#include "GameState.h"

#include "Input.h"

Command::Command()
{}

void Command::Execute(float)
{}

MoveCommand::MoveCommand(dae::GameObject* gameObject, glm::vec3 direction)
	:Command()
	,m_Direction(direction)
	,m_pGameObject(gameObject)
{}

void MoveCommand::Execute(float deltaTime)
{
	glm::vec3 newMovement = m_Direction * (m_pGameObject->GetComponent<PlayerStatsComponent>()->GetSpeed() * deltaTime);
	glm::vec3 currentPosition = m_pGameObject->GetWorldPosition();

	m_pGameObject->GetComponent<TransformComponent>()->SetLocalPosition(currentPosition + newMovement);
}

SpawnBombCommand::SpawnBombCommand(std::shared_ptr<dae::GameObject> player, std::shared_ptr<dae::GameObject> grid, int widthOffset, int heightOffset, int placeBombSoundID, int explosionSoundID)
	:Command()
	,m_WidthOffset(widthOffset)
	,m_HeightOffset(heightOffset)
	,m_PlaceBombSoundID(placeBombSoundID)
	,m_ExplosionSoundID(explosionSoundID)
{
	m_pPlayer = player;
	m_pGrid = grid;
}

void SpawnBombCommand::Execute(float)
{
	if (m_pPlayer->GetComponent<PlayerStatsComponent>()->GetCurrentBombs() < m_pPlayer->GetComponent<PlayerStatsComponent>()->GetMaxBombs())
	{
		m_pPlayer->GetComponent<PlayerStatsComponent>()->IncreaseCurrentBombs();
		auto& ss = Servicelocator::get_sound_system();
		ss.play(static_cast<sound_id>(m_PlaceBombSoundID), 30);
		std::vector<int> collisionIDs{ 0 };

		auto go_Bomb = std::make_shared<dae::GameObject>();
		go_Bomb->AddComponent<RenderComponent>();
		go_Bomb->AddComponent<BombComponent>();
		go_Bomb->AddComponent<CollisionComponent>()->SetUpCollisionBox(m_WidthOffset,m_HeightOffset,4,collisionIDs);
		go_Bomb->GetComponent<BombComponent>()->SetFireOffset(m_WidthOffset, m_HeightOffset);
		go_Bomb->GetComponent<BombComponent>()->SetFirePower(m_pPlayer->GetComponent<PlayerStatsComponent>()->GetFirePower());
		go_Bomb->GetComponent<BombComponent>()->SetSoundID(m_ExplosionSoundID);
		go_Bomb->GetComponent<BombComponent>()->AddObserver(new BombObserver{m_pPlayer.get()});
		go_Bomb->GetComponent<RenderComponent>()->SetTexture("Resources/Bomb.png");

		m_pPlayer->GetComponent<PlayerStatsComponent>()->AddObserver(new BombObserver{ go_Bomb.get() });

		glm::vec3 playerPosition = m_pPlayer->GetWorldPosition();
		Tile closestTile = m_pGrid->GetComponent<GridComponent>()->ClosestTile(playerPosition.x, playerPosition.y);
		go_Bomb->GetComponent<TransformComponent>()->SetLocalPosition(glm::vec3{ closestTile.left,closestTile.top,0 });
		go_Bomb->SetParent(m_pGrid, true);
	}
}

DetonateBombCommand::DetonateBombCommand(std::shared_ptr<dae::GameObject> player)
	:Command()
{
	if (dae::SceneManager::GetInstance().GetState() && dae::SceneManager::GetInstance().GetState()->GetCurrentMode() == GameState::CurrentMode::MAIN_MENU)
	{
		return;
	}
	m_pPlayer = player;
}

void DetonateBombCommand::Execute(float)
{
	m_pPlayer->GetComponent<PlayerStatsComponent>()->DetonateEarly();
}

MoveInListDownCommand::MoveInListDownCommand(std::shared_ptr<dae::GameObject> icon, std::vector<glm::vec2> positions)
	:Command()
{
	m_pIcon = icon;
	m_Positions = positions;
}

void MoveInListDownCommand::Execute(float)
{
	for (int i = 0; i < m_Positions.size(); i++)
	{
		glm::vec2 iconPosition{ m_pIcon->GetWorldPosition() };
		if (iconPosition.x == m_Positions[i].x && iconPosition.y == m_Positions[i].y)
		{
			if (i + 1 < m_Positions.size())
			{
				int newIndex{ i + 1 };
				m_pIcon->GetComponent<TransformComponent>()->SetLocalPosition(glm::vec3(m_Positions[newIndex].x, m_Positions[newIndex].y, 0));
			}
			return;
		}
	}
}

MoveInListUpCommand::MoveInListUpCommand(std::shared_ptr<dae::GameObject> icon, std::vector<glm::vec2> positions)
	:Command()
{
	m_pIcon = icon;
	m_Positions = positions;
}

void MoveInListUpCommand::Execute(float)
{
	for (int i = 0; i < m_Positions.size(); i++)
	{
		glm::vec2 iconPosition{ m_pIcon->GetWorldPosition() };
		if (iconPosition.x == m_Positions[i].x && iconPosition.y == m_Positions[i].y)
		{
			if (i - 1 > -1)
			{
				int newIndex{ i - 1 };
				m_pIcon->GetComponent<TransformComponent>()->SetLocalPosition(glm::vec3(m_Positions[newIndex].x, m_Positions[newIndex].y, 0));
			}
			return;
		}
	}
}

SelectModeCommand::SelectModeCommand(std::shared_ptr<dae::GameObject> icon, int positionYMode1, int positionYMode2, int positionYMode3)
	:m_PositionYMode1(positionYMode1)
	,m_PositionYMode2(positionYMode2)
	,m_PositionYMode3(positionYMode3)
{
	m_pIcon = icon;
}

void SelectModeCommand::Execute(float)
{
	glm::vec2 iconPosition{ m_pIcon->GetWorldPosition() };

	if (static_cast<int>(iconPosition.y) == m_PositionYMode1)
	{
		auto& sceneManager = dae::SceneManager::GetInstance();
		sceneManager.SetState(std::make_shared<SinglePlayerState>(sceneManager.GetSceneByName("SinglePlayer").get(), sceneManager.GetState()->GetCommandVector()));
	}

	if (static_cast<int>(iconPosition.y) == m_PositionYMode2)
	{
		std::cout << "Coop Mode\n";
	}

	if (static_cast<int>(iconPosition.y) == m_PositionYMode3)
	{
		std::cout << "Versus Mode\n";
	}
}
