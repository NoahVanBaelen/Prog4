#include "CollisionComponent.h"
#include "Transform.h"
#include "CollisionServicelocator.h"
#include "TransformComponent.h"

CollisionComponent::CollisionComponent(dae::GameObject* pOwner)
    :BaseComponent(pOwner)
{}

void CollisionComponent::Update(float /*deltaTime*/)
{
    if (!m_IsStatic)//dont do anything when static
    {
        glm::vec3 position = GetOwner()->GetWorldPosition();
        m_CollisionBox.centerPosition = glm::vec2{ position.x,position.y };

        if (m_CollisionBox.pOwner)//check if we setted the CollisionBox
        {
            auto& collisionSystem = CollisionServicelocator::get_collision_system();

            //See for collision -> if we collide with something we get the offset to move ourself
            std::pair<int, int>offset{ collisionSystem.HasCollision(this) };
            position.x += offset.second;
            position.y += offset.first;
            GetOwner()->GetComponent<TransformComponent>()->SetLocalPosition(position);
        }
    }
}

void CollisionComponent::LateUpdate(float)
{
    if (GetOwner()->GetIsMarkedForDestroy()) {RemoveCollisionBox();}
}

void CollisionComponent::SetUpCollisionBox(const int width, const int height, const int collisionGroupID, const std::vector<int> collisionGroupsToCollideWithIDs)
{
    glm::vec3 position = GetOwner()->GetWorldPosition();
    m_CollisionBox.centerPosition = glm::vec2{ position.x,position.y };
    m_CollisionBox.widthBox = width;
    m_CollisionBox.heightBox = height;
    m_CollisionBox.collisionGroupID = collisionGroupID;
    m_CollisionBox.groupIdToCollideWith = collisionGroupsToCollideWithIDs;

    m_CollisionBox.pOwner = GetOwner();

    auto& collisionSystem = CollisionServicelocator::get_collision_system();
    collisionSystem.AddCollisionBox(this);
}

void CollisionComponent::SetIsStatic(bool isStatic)
{
    m_IsStatic = isStatic;
    m_CollisionBox.isStatic = isStatic;
    if (isStatic)
    {
        m_CollisionBox.left = static_cast<int>(m_CollisionBox.centerPosition.x) - m_CollisionBox.widthBox / 2;
        m_CollisionBox.right = static_cast<int>(m_CollisionBox.centerPosition.x) + m_CollisionBox.widthBox / 2;
        m_CollisionBox.bottom = static_cast<int>(m_CollisionBox.centerPosition.y) + m_CollisionBox.heightBox / 2;
        m_CollisionBox.top = static_cast<int>(m_CollisionBox.centerPosition.y) - m_CollisionBox.heightBox / 2;;
    }
}

void CollisionComponent::RemoveCollisionBox()
{
    auto& collisionSystem = CollisionServicelocator::get_collision_system();
    collisionSystem.RemoveCollisionBox(this);
}

CollisionBox CollisionComponent::GetCollisionBox()
{
    return m_CollisionBox;
}
