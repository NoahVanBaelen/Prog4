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

AddScoreCommand::AddScoreCommand(dae::GameObject* gameObject, int point)
	:Command()
	,m_Points(point)
	, m_pGameObject(gameObject)
{}

void AddScoreCommand::Execute(float)
{
	m_pGameObject->GetComponent<ScoreComponent>()->AddScore(m_Points);
}

LoseLiveCommand::LoseLiveCommand(dae::GameObject* gameObject)
	:Command()
	, m_pGameObject(gameObject)
{}

void LoseLiveCommand::Execute(float)
{
	m_pGameObject->GetComponent<LiveComponent>()->LoseLive();
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
		auto& ss = Servicelocator::get_sound_system();
		ss.play(static_cast<sound_id>(m_PlaceBombSoundID), 30);

		auto go_Bomb = std::make_shared<dae::GameObject>();
		go_Bomb->AddComponent<RenderComponent>();
		go_Bomb->AddComponent<BombComponent>();
		go_Bomb->GetComponent<BombComponent>()->SetFireOffset(m_WidthOffset, m_HeightOffset);
		go_Bomb->GetComponent<BombComponent>()->SetFirePower(m_pPlayer->GetComponent<PlayerStatsComponent>()->GetFirePower());
		go_Bomb->GetComponent<BombComponent>()->SetSoundID(m_ExplosionSoundID);
		go_Bomb->GetComponent<RenderComponent>()->SetTexture("Resources/Bomb.png");

		glm::vec3 playerPosition = m_pPlayer->GetWorldPosition();
		Tile closestTile = m_pGrid->GetComponent<GridComponent>()->ClosestTile(playerPosition.x, playerPosition.y);
		go_Bomb->GetComponent<TransformComponent>()->SetLocalPosition(glm::vec3{ closestTile.left,closestTile.top,0 });
		m_pGrid->AddChild(go_Bomb, true);
	}
}
