#include "TransformComponent.h"

TransformComponent::TransformComponent(dae::GameObject* pOwner)
    :BaseComponent(pOwner)
{
    m_localPosition.SetPosition(0.f, 0.f, 0.f);
    m_worldPosition.SetPosition(0.f, 0.f, 0.f);
}

const glm::vec3& TransformComponent::GetWorldPosition()
{
    if (m_PositionIsDirty)
    {
        UpdateWorldPosition();
    }
    return m_worldPosition.GetPosition();
}

void TransformComponent::SetLocalPosition(const glm::vec3& pos)
{
    m_localPosition.SetPosition(pos.x,pos.y,pos.z);
    SetPositionDirty();
}

const glm::vec3& TransformComponent::GetLocalPosition() const
{
    return m_localPosition.GetPosition();
}

void TransformComponent::SetPositionDirty() //children not dirty children
{
    m_PositionIsDirty = true;

    for (unsigned int i = 0; i < static_cast<unsigned int>(GetOwner()->GetChildCount()); i++)
    {
        GetOwner()->GetChildAt(i)->GetComponent<TransformComponent>()->SetPositionDirty();
    }
}

void TransformComponent::UpdateWorldPosition()
{
    if (m_PositionIsDirty)
    {
        if (GetOwner()->GetParent() == nullptr)
        {
            m_worldPosition = m_localPosition;
        }
        else
        {
            auto& posWorld = GetOwner()->GetParent()->GetWorldPosition();
            auto& posLocal = m_localPosition.GetPosition();
            m_worldPosition.SetPosition(posWorld.x + posLocal.x, posWorld.y + posLocal.y, posWorld.z + posLocal.z);
        }
    }
    m_PositionIsDirty = false;
}
