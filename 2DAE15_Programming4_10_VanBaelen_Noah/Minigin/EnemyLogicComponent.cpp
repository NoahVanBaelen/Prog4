#include "EnemyLogicComponent.h"
#include "TriggerComponent.h"
#include "PlayerStatsComponent.h"
#include "TransformComponent.h"
#include "CollisionServicelocator.h"
#include "CollisionComponent.h"
#include "GridComponent.h"

EnemyLogicComponent::EnemyLogicComponent(dae::GameObject* pOwner)
	:BaseComponent(pOwner)
	,m_Target{GetOwner()->GetWorldPosition()}
	,m_Score{0}
	,m_Difficulty{EnemyDifficulty::lowDifficulty}
	,m_rayLenght{ glm::vec2{0,0} }
{
}

void EnemyLogicComponent::Update(float deltaTime)
{
	std::pair<bool, dae::GameObject*> trigger{ GetOwner()->GetComponent<TriggerComponent>()->GetHasTriggerLastFrame() };
	if (trigger.first == true && trigger.second->HasComponent<PlayerStatsComponent>())
	{
		trigger.second->GetComponent<PlayerStatsComponent>()->DecreaseLives();
	}

	glm::vec2 position{ GetOwner()->GetWorldPosition() };

	if ((position.x - m_Target.x) <= 0.25f && (position.x - m_Target.x) >= -0.25f &&
		(position.y - m_Target.y) <= 0.25f && (position.y - m_Target.y) >= -0.25f)
	{
		GetOwner()->GetParent()->GetComponent<GridComponent>()->SetToClosestTileCenter(position);
		m_foundPlayer = false;
		glm::vec2 rayStart{ position };
		glm::vec2 rayEnd{ position };
		auto& collisionSystem = CollisionServicelocator::get_collision_system();

		if (m_Difficulty == EnemyDifficulty::normalDifficulty)
		{
			std::vector<int> enemyCanCollideWithIDs{1};
			std::pair<bool, dae::GameObject*> result{};

			rayEnd.y += (m_rayLenght.y * 3);
			result = collisionSystem.RayCast(rayStart, rayEnd, enemyCanCollideWithIDs);
			if (result.first && result.second->HasComponent<PlayerStatsComponent>())//check Down
			{
				m_foundPlayer = true;
				rayEnd = position;
				rayEnd.y += m_rayLenght.y;
				m_Target = rayEnd;
			}
			else
			{
				rayEnd = position;
				rayEnd.y -= (m_rayLenght.y * 3);
				result = collisionSystem.RayCast(rayStart, rayEnd, enemyCanCollideWithIDs);
				if (result.first && result.second->HasComponent<PlayerStatsComponent>())//check Up
				{
					m_foundPlayer = true;
					rayEnd = position;
					rayEnd.y -= m_rayLenght.y;
					m_Target = rayEnd;
				}
				else
				{
					rayEnd = position;
					rayEnd.x += (m_rayLenght.x * 3);
					result = collisionSystem.RayCast(rayStart, rayEnd, enemyCanCollideWithIDs);
					if (result.first && result.second->HasComponent<PlayerStatsComponent>())//check Right
					{
						m_foundPlayer = true;
						rayEnd = position;
						rayEnd.x += m_rayLenght.x;
						m_Target = rayEnd;
					}
					else
					{
						rayEnd = position;
						rayEnd.x -= (m_rayLenght.x * 3);
						result = collisionSystem.RayCast(rayStart, rayEnd, enemyCanCollideWithIDs);
						if (result.first && result.second->HasComponent<PlayerStatsComponent>())//check Left
						{
							m_foundPlayer = true;
							rayEnd = position;
							rayEnd.x -= m_rayLenght.x;
							m_Target = rayEnd;
						}
					}
				}
			}
		}

		if (m_Difficulty == EnemyDifficulty::lowDifficulty || !m_foundPlayer)
		{
			std::vector<int> enemyCanCollideWithIDs{ 2, 4 };
			std::vector<glm::vec2>m_potentialWays{};

			rayEnd = position;
			rayEnd.y += m_rayLenght.y;
			if (!collisionSystem.RayCast(rayStart, rayEnd, enemyCanCollideWithIDs).first)//check Down
			{
				m_potentialWays.push_back(rayEnd);
			}

			rayEnd = position;
			rayEnd.y -= m_rayLenght.y;
			if (!collisionSystem.RayCast(rayStart, rayEnd, enemyCanCollideWithIDs).first)//check Up
			{
				m_potentialWays.push_back(rayEnd);
			}

			rayEnd = position;
			rayEnd.x += m_rayLenght.x;
			if (!collisionSystem.RayCast(rayStart, rayEnd, enemyCanCollideWithIDs).first)//check Right
			{
				m_potentialWays.push_back(rayEnd);
			}

			rayEnd = position;
			rayEnd.x -= m_rayLenght.x;
			if (!collisionSystem.RayCast(rayStart, rayEnd, enemyCanCollideWithIDs).first)//check Left
			{
				m_potentialWays.push_back(rayEnd);
			}

			if (!m_potentialWays.empty())//if empty means enemy is stuck
			{
				std::srand(static_cast<unsigned int>(std::time(nullptr)));
				int randomIndex = std::rand() % m_potentialWays.size();
				m_Target = m_potentialWays[randomIndex];
			}
		}
	}
	else
	{
		float distanceX{ m_Target.x - position.x };
		float distanceY{ m_Target.y - position.y };

		if ((position.x - m_Target.x) <= 0.25f && (position.x - m_Target.x) >= -0.25f)
		{
			distanceX = 0;
		}

		if ((position.y - m_Target.y) <= 0.25f && (position.y - m_Target.y) >= -0.25f)
		{
			distanceY = 0;
		}

		position.x += distanceX * (m_Speed * deltaTime);
		position.y += distanceY * (m_Speed * deltaTime);
		GetOwner()->GetComponent<TransformComponent>()->SetLocalPosition(glm::vec3{ position.x,position.y,0 });
	}
}

void EnemyLogicComponent::SetUpEnemy(EnemySpeed speed, EnemyDifficulty difficulty, int score, glm::vec2 rayLenght)
{
	switch (speed)
	{
	case EnemyLogicComponent::slow:
		m_Speed = 0.005f;
		break;
	case EnemyLogicComponent::normal:
		m_Speed = 0.01f;
		break;
	case EnemyLogicComponent::fast:
		m_Speed = 0.015f;
		break;
	default:
		break;
	}

	m_Difficulty = difficulty;
	m_Score = score;
	m_rayLenght = rayLenght;
}

void EnemyLogicComponent::GetKilled()
{
	GetOwner()->GetComponent<CollisionComponent>()->RemoveCollisionBox();
	GetOwner()->m_MarkedForDestroy = true;
}
