#include "SpawnComponent.h"
#include "TransformComponent.h"

SpawnComponent::SpawnComponent(dae::GameObject* pOwner)
	:BaseComponent(pOwner)
{
}

void SpawnComponent::Spawn(std::shared_ptr<dae::GameObject> parent)
{
	m_pObjectToSpawn->GetComponent<TransformComponent>()->SetLocalPosition(GetOwner()->GetWorldPosition());
	m_pObjectToSpawn->SetParent(parent, true);
}

void SpawnComponent::SetObjectToSpawn(std::shared_ptr<dae::GameObject> gameObject)
{
	m_pObjectToSpawn = gameObject;
}
