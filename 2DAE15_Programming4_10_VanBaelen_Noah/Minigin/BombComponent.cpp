#include "BombComponent.h"
#include "RenderComponent.h"
#include "PlayerStatsComponent.h"
#include "FireComponent.h"
#include "GridComponent.h"

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
		if (!m_Exploded)
		{
			Explode();
			auto& ss = Servicelocator::get_sound_system();
			ss.play(static_cast<sound_id>(m_SoundID), 30);
			m_Exploded = true;
		}
		else if (m_Exploded && GetOwner()->GetChildCount() == 0)
		{
			GetOwner()->m_MarkedForDestroy = true;
		}
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

void BombComponent::Explode()
{
	glm::vec3 pos{ GetOwner()->GetWorldPosition() };
	auto go_FireCenter = std::make_shared<dae::GameObject>();
	go_FireCenter->AddComponent<RenderComponent>();
	go_FireCenter->AddComponent<FireComponent>();
	go_FireCenter->GetComponent<RenderComponent>()->SetTexture("Resources/FireCenter.png");
	go_FireCenter->GetComponent<RenderComponent>()->ScaleTexture(1.3f);
	go_FireCenter->GetComponent<TransformComponent>()->SetLocalPosition(pos);
	GetOwner()->AddChild(go_FireCenter,true);

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
			GetOwner()->AddChild(go_FireUp, true);
		}
		else if(canDrawUp)
		{
			auto go_FireUp = std::make_shared<dae::GameObject>();
			go_FireUp->AddComponent<RenderComponent>();
			go_FireUp->AddComponent<FireComponent>();
			go_FireUp->GetComponent<RenderComponent>()->SetTexture("Resources/Fire.png");
			go_FireCenter->GetComponent<RenderComponent>()->ScaleTexture(1.3f);
			go_FireUp->GetComponent<TransformComponent>()->SetLocalPosition(glm::vec3{ pos.x,pos.y - m_HeightOffset * i,pos.z });
			GetOwner()->AddChild(go_FireUp, true);
		}

		if ((i == m_FirePower || GetOwner()->GetParent()->GetComponent<GridComponent>()->IsAnUnBreakableTile(pos.x, pos.y + m_HeightOffset * (i + 1))) && canDrawDown)
		{
			auto go_FireDown = std::make_shared<dae::GameObject>();
			go_FireDown->AddComponent<RenderComponent>();
			go_FireDown->AddComponent<FireComponent>();
			go_FireDown->GetComponent<RenderComponent>()->SetTexture("Resources/FireEnd.png");
			go_FireDown->GetComponent<RenderComponent>()->ScaleTexture(1.3f);
			go_FireDown->GetComponent<TransformComponent>()->SetLocalPosition(glm::vec3{ pos.x,pos.y + m_HeightOffset * i,pos.z });
			GetOwner()->AddChild(go_FireDown, true);
		}
		else if (canDrawDown)
		{
			auto go_FireDown = std::make_shared<dae::GameObject>();
			go_FireDown->AddComponent<RenderComponent>();
			go_FireDown->AddComponent<FireComponent>();
			go_FireDown->GetComponent<RenderComponent>()->SetTexture("Resources/Fire.png");
			go_FireDown->GetComponent<RenderComponent>()->ScaleTexture(1.3f);
			go_FireDown->GetComponent<TransformComponent>()->SetLocalPosition(glm::vec3{ pos.x,pos.y + m_HeightOffset * i,pos.z });
			GetOwner()->AddChild(go_FireDown, true);
		}

		if ((i == m_FirePower || GetOwner()->GetParent()->GetComponent<GridComponent>()->IsAnUnBreakableTile(pos.x + m_WideOffset * (i + 1),pos.y)) && canDrawRight)
		{
			auto go_FireRight = std::make_shared<dae::GameObject>();
			go_FireRight->AddComponent<RenderComponent>();
			go_FireRight->AddComponent<FireComponent>();
			go_FireRight->GetComponent<RenderComponent>()->SetTexture("Resources/FireEnd.png");
			go_FireRight->GetComponent<RenderComponent>()->ScaleTexture(1.3f);
			go_FireRight->GetComponent<TransformComponent>()->SetLocalPosition(glm::vec3{ pos.x + m_WideOffset * i,pos.y,pos.z });
			GetOwner()->AddChild(go_FireRight, true);
		}
		else if (canDrawRight)
		{
			auto go_FireRight = std::make_shared<dae::GameObject>();
			go_FireRight->AddComponent<RenderComponent>();
			go_FireRight->AddComponent<FireComponent>();
			go_FireRight->GetComponent<RenderComponent>()->SetTexture("Resources/Fire.png");
			go_FireRight->GetComponent<RenderComponent>()->ScaleTexture(1.3f);
			go_FireRight->GetComponent<TransformComponent>()->SetLocalPosition(glm::vec3{ pos.x + m_WideOffset * i,pos.y,pos.z });
			GetOwner()->AddChild(go_FireRight, true);
		}

		if ((i == m_FirePower || GetOwner()->GetParent()->GetComponent<GridComponent>()->IsAnUnBreakableTile(pos.x - m_WideOffset * (i + 1), pos.y)) && canDrawLeft)
		{
			auto go_FireLeft = std::make_shared<dae::GameObject>();
			go_FireLeft->AddComponent<RenderComponent>();
			go_FireLeft->AddComponent<FireComponent>();
			go_FireLeft->GetComponent<RenderComponent>()->SetTexture("Resources/FireEnd.png");
			go_FireLeft->GetComponent<RenderComponent>()->ScaleTexture(1.3f);
			go_FireLeft->GetComponent<TransformComponent>()->SetLocalPosition(glm::vec3{ pos.x - m_WideOffset * i,pos.y,pos.z });
			GetOwner()->AddChild(go_FireLeft, true);
		}
		else if (canDrawLeft)
		{
			auto go_FireLeft = std::make_shared<dae::GameObject>();
			go_FireLeft->AddComponent<RenderComponent>();
			go_FireLeft->AddComponent<FireComponent>();
			go_FireLeft->GetComponent<RenderComponent>()->SetTexture("Resources/Fire.png");
			go_FireLeft->GetComponent<RenderComponent>()->ScaleTexture(1.3f);
			go_FireLeft->GetComponent<TransformComponent>()->SetLocalPosition(glm::vec3{ pos.x - m_WideOffset * i,pos.y,pos.z });
			GetOwner()->AddChild(go_FireLeft, true);
		}
	}
}
