#include "BombComponent.h"
#include "RenderComponent.h"
#include "PlayerStatsComponent.h"
#include "FireComponent.h"
#include "GridComponent.h"
#include "TriggerComponent.h"

#include "Servicelocator.h"

BombComponent::BombComponent(dae::GameObject* pOwner)
	:BaseComponent(pOwner)
	,m_TimeToExplode(25.f)
{
}

void BombComponent::Update(float deltaTime)
{
	m_TimeToExplode -= deltaTime * 0.01f;
	if (m_TimeToExplode <= 0)
	{
		Explode();
		m_Subjects->NotifyObservers(Observer::Event::BOMB_EXPLODED, GetOwner());
		auto& ss = Servicelocator::get_sound_system();
		ss.play(static_cast<sound_id>(m_SoundID), 30);
		GetOwner()->MarkForDestroy();
	}
}

void BombComponent::SetFireOffset(int wideOffset, int heightOffset)
{
	m_WideOffset = wideOffset;
	m_HeightOffset = heightOffset;
}

void BombComponent::SetFirePower(int firePower)
{
	m_FirePower = firePower;
}

void BombComponent::SetSoundID(int soundID)
{
	m_SoundID = soundID;
}

void BombComponent::EarlyDetonation()
{
	m_TimeToExplode = 0;
}

void BombComponent::AddObserver(Observer* observer)
{
	m_Subjects->AddObserver(observer);
}

void BombComponent::Explode()
{
	std::vector<int>IDsCollisionGroups {1, 3, 4};
	glm::vec3 pos{ GetOwner()->GetWorldPosition() };
	auto go_FireCenter = std::make_shared<dae::GameObject>();
	go_FireCenter->AddComponent<RenderComponent>();
	go_FireCenter->AddComponent<FireComponent>();
	go_FireCenter->GetComponent<RenderComponent>()->SetTexture("Resources/FireCenter.png");
	go_FireCenter->GetComponent<RenderComponent>()->ScaleTexture(1.3f);

	float flameHeight{ go_FireCenter->GetComponent<RenderComponent>()->GetTextureHeight() * 1.3f };
	float flameWidth{ go_FireCenter->GetComponent<RenderComponent>()->GetTextureWidth() * 1.3f };

	go_FireCenter->AddComponent<TriggerComponent>()->SetUpCollisionBox(static_cast<int>(flameWidth), static_cast<int>(flameHeight), IDsCollisionGroups);
	go_FireCenter->GetComponent<TransformComponent>()->SetLocalPosition(pos);
	go_FireCenter->SetParent(GetOwner()->GetParent(), true);

	bool canDrawUp{ true };
	bool canDrawDown{ true };
	bool canDrawRight{ true };
	bool canDrawLeft{ true };

	for (int i = 1; i <= m_FirePower; i++)
	{
		if (GetOwner()->GetParent()->GetComponent<GridComponent>()->IsAnUnBreakableTile(pos.x, pos.y - m_HeightOffset * i))
		{
			canDrawUp = false;
		}
		if (GetOwner()->GetParent()->GetComponent<GridComponent>()->IsAnUnBreakableTile(pos.x, pos.y + m_HeightOffset * i))
		{
			canDrawDown = false;
		}
		if (GetOwner()->GetParent()->GetComponent<GridComponent>()->IsAnUnBreakableTile(pos.x + m_WideOffset * i, pos.y))
		{
			canDrawRight = false;
		}
		if (GetOwner()->GetParent()->GetComponent<GridComponent>()->IsAnUnBreakableTile(pos.x - m_WideOffset * i, pos.y))
		{
			canDrawLeft = false;
		}

		if ((i == m_FirePower || GetOwner()->GetParent()->GetComponent<GridComponent>()->IsAnUnBreakableTile(pos.x, pos.y - m_HeightOffset * (i + 1))) && canDrawUp)
		{
			auto go_FireUp = std::make_shared<dae::GameObject>();
			go_FireUp->AddComponent<RenderComponent>();
			go_FireUp->AddComponent<FireComponent>();
			go_FireUp->GetComponent<RenderComponent>()->SetTexture("Resources/FireEnd.png");
			go_FireUp->GetComponent<RenderComponent>()->ScaleTexture(1.3f);
			go_FireUp->GetComponent<TransformComponent>()->SetLocalPosition(glm::vec3{ pos.x,pos.y - m_HeightOffset * i,pos.z });
			go_FireUp->AddComponent<TriggerComponent>()->SetUpCollisionBox(static_cast<int>(flameWidth), static_cast<int>(flameHeight), IDsCollisionGroups);
			go_FireUp->SetParent(GetOwner()->GetParent(), true);;
		}
		else if(canDrawUp)
		{
			auto go_FireUp = std::make_shared<dae::GameObject>();
			go_FireUp->AddComponent<RenderComponent>();
			go_FireUp->AddComponent<FireComponent>();
			go_FireUp->GetComponent<RenderComponent>()->SetTexture("Resources/Fire.png");
			go_FireCenter->GetComponent<RenderComponent>()->ScaleTexture(1.3f);
			go_FireUp->GetComponent<TransformComponent>()->SetLocalPosition(glm::vec3{ pos.x,pos.y - m_HeightOffset * i,pos.z });
			go_FireUp->AddComponent<TriggerComponent>()->SetUpCollisionBox(static_cast<int>(flameWidth), static_cast<int>(flameHeight), IDsCollisionGroups);
			go_FireUp->SetParent(GetOwner()->GetParent(), true);
		}

		if ((i == m_FirePower || GetOwner()->GetParent()->GetComponent<GridComponent>()->IsAnUnBreakableTile(pos.x, pos.y + m_HeightOffset * (i + 1))) && canDrawDown)
		{
			auto go_FireDown = std::make_shared<dae::GameObject>();
			go_FireDown->AddComponent<RenderComponent>();
			go_FireDown->AddComponent<FireComponent>();
			go_FireDown->GetComponent<RenderComponent>()->SetTexture("Resources/FireEnd.png");
			go_FireDown->GetComponent<RenderComponent>()->ScaleTexture(1.3f);
			go_FireDown->GetComponent<TransformComponent>()->SetLocalPosition(glm::vec3{ pos.x,pos.y + m_HeightOffset * i,pos.z });
			go_FireDown->AddComponent<TriggerComponent>()->SetUpCollisionBox(static_cast<int>(flameWidth), static_cast<int>(flameHeight), IDsCollisionGroups);
			go_FireDown->SetParent(GetOwner()->GetParent(), true);
		}
		else if (canDrawDown)
		{
			auto go_FireDown = std::make_shared<dae::GameObject>();
			go_FireDown->AddComponent<RenderComponent>();
			go_FireDown->AddComponent<FireComponent>();
			go_FireDown->GetComponent<RenderComponent>()->SetTexture("Resources/Fire.png");
			go_FireDown->GetComponent<RenderComponent>()->ScaleTexture(1.3f);
			go_FireDown->GetComponent<TransformComponent>()->SetLocalPosition(glm::vec3{ pos.x,pos.y + m_HeightOffset * i,pos.z });
			go_FireDown->AddComponent<TriggerComponent>()->SetUpCollisionBox(static_cast<int>(flameWidth), static_cast<int>(flameHeight), IDsCollisionGroups);
			go_FireDown->SetParent(GetOwner()->GetParent(), true);
		}

		if ((i == m_FirePower || GetOwner()->GetParent()->GetComponent<GridComponent>()->IsAnUnBreakableTile(pos.x + m_WideOffset * (i + 1),pos.y)) && canDrawRight)
		{
			auto go_FireRight = std::make_shared<dae::GameObject>();
			go_FireRight->AddComponent<RenderComponent>();
			go_FireRight->AddComponent<FireComponent>();
			go_FireRight->GetComponent<RenderComponent>()->SetTexture("Resources/FireEnd.png");
			go_FireRight->GetComponent<RenderComponent>()->ScaleTexture(1.3f);
			go_FireRight->GetComponent<TransformComponent>()->SetLocalPosition(glm::vec3{ pos.x + m_WideOffset * i,pos.y,pos.z });
			go_FireRight->AddComponent<TriggerComponent>()->SetUpCollisionBox(static_cast<int>(flameWidth), static_cast<int>(flameHeight), IDsCollisionGroups);
			go_FireRight->SetParent(GetOwner()->GetParent(), true);
		}
		else if (canDrawRight)
		{
			auto go_FireRight = std::make_shared<dae::GameObject>();
			go_FireRight->AddComponent<RenderComponent>();
			go_FireRight->AddComponent<FireComponent>();
			go_FireRight->GetComponent<RenderComponent>()->SetTexture("Resources/Fire.png");
			go_FireRight->GetComponent<RenderComponent>()->ScaleTexture(1.3f);
			go_FireRight->GetComponent<TransformComponent>()->SetLocalPosition(glm::vec3{ pos.x + m_WideOffset * i,pos.y,pos.z });
			go_FireRight->AddComponent<TriggerComponent>()->SetUpCollisionBox(static_cast<int>(flameWidth), static_cast<int>(flameHeight), IDsCollisionGroups);
			go_FireRight->SetParent(GetOwner()->GetParent(), true);
		}

		if ((i == m_FirePower || GetOwner()->GetParent()->GetComponent<GridComponent>()->IsAnUnBreakableTile(pos.x - m_WideOffset * (i + 1), pos.y)) && canDrawLeft)
		{
			auto go_FireLeft = std::make_shared<dae::GameObject>();
			go_FireLeft->AddComponent<RenderComponent>();
			go_FireLeft->AddComponent<FireComponent>();
			go_FireLeft->GetComponent<RenderComponent>()->SetTexture("Resources/FireEnd.png");
			go_FireLeft->GetComponent<RenderComponent>()->ScaleTexture(1.3f);
			go_FireLeft->GetComponent<TransformComponent>()->SetLocalPosition(glm::vec3{ pos.x - m_WideOffset * i,pos.y,pos.z });
			go_FireLeft->AddComponent<TriggerComponent>()->SetUpCollisionBox(static_cast<int>(flameWidth), static_cast<int>(flameHeight), IDsCollisionGroups);
			go_FireLeft->SetParent(GetOwner()->GetParent(), true);
		}
		else if (canDrawLeft)
		{
			auto go_FireLeft = std::make_shared<dae::GameObject>();
			go_FireLeft->AddComponent<RenderComponent>();
			go_FireLeft->AddComponent<FireComponent>();
			go_FireLeft->GetComponent<RenderComponent>()->SetTexture("Resources/Fire.png");
			go_FireLeft->GetComponent<RenderComponent>()->ScaleTexture(1.3f);
			go_FireLeft->GetComponent<TransformComponent>()->SetLocalPosition(glm::vec3{ pos.x - m_WideOffset * i,pos.y,pos.z });
			go_FireLeft->AddComponent<TriggerComponent>()->SetUpCollisionBox(static_cast<int>(flameWidth), static_cast<int>(flameHeight), IDsCollisionGroups);
			go_FireLeft->SetParent(GetOwner()->GetParent(), true);
		}
	}
}
