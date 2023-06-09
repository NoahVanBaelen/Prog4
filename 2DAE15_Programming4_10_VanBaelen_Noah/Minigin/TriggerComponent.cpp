#include "TriggerComponent.h"
#include "CollisionServicelocator.h"

TriggerComponent::TriggerComponent(dae::GameObject* pOwner)
    :BaseComponent(pOwner)
{}

void TriggerComponent::Update(float)
{
    glm::vec3 position = GetOwner()->GetWorldPosition();
    m_CollisionBox.centerPosition = glm::vec2{ position.x,position.y };

    m_IsTriggerdLastFrame = m_IsTriggerdThisFrame;
    m_pGameObjectCollidedLastFrame = m_pGameObjectCollidedThisFrame;

    auto& collisionSystem = CollisionServicelocator::get_collision_system();
    std::pair<bool, dae::GameObject*>trigger{ collisionSystem.HasTrigger(m_CollisionBox) };

    m_IsTriggerdThisFrame = trigger.first;
    m_pGameObjectCollidedThisFrame = trigger.second;
};

void TriggerComponent::SetUpCollisionBox(const int width, const int height, const std::vector<int> collisionGroupsToCollideWithIDs)
{
    glm::vec3 position = GetOwner()->GetWorldPosition();
    m_CollisionBox.centerPosition = glm::vec2{ position.x,position.y };
    m_CollisionBox.widthBox = width;
    m_CollisionBox.heightBox = height;
    m_CollisionBox.collisionGroupID = -1;
    m_CollisionBox.groupIdToCollideWith = collisionGroupsToCollideWithIDs;

    m_CollisionBox.pOwner = GetOwner();
}

std::pair<bool, dae::GameObject*> TriggerComponent::GetHasTriggerLastFrame()
{
    return std::pair<bool, dae::GameObject*>(m_IsTriggerdLastFrame,m_pGameObjectCollidedLastFrame);
}
