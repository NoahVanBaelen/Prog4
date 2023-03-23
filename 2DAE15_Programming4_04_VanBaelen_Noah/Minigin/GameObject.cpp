#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"
#include "TransformComponent.h"
#include <algorithm>

dae::GameObject::GameObject()
{
	m_componentVector.emplace_back(std::make_shared<TransformComponent>(this));
	m_pTransforComponent = std::static_pointer_cast<TransformComponent>(m_componentVector[0]);
}

dae::GameObject::~GameObject() = default;

void dae::GameObject::FixedUpdate(float fixedTimeStep) //Update children
{
	for (unsigned int i = 0; i < static_cast<unsigned int>(m_componentVector.size()); i++)
	{
		m_componentVector[i]->FixedUpdate(fixedTimeStep);
	}

	for (unsigned int i = 0; i < static_cast<unsigned int>(m_children.size()); i++)
	{
		GetChildAt(i)->FixedUpdate(fixedTimeStep);
	}
}

void dae::GameObject::Update(float deltaTime) //Update children
{
	for (unsigned int i = 0; i < static_cast<unsigned int>(m_componentVector.size()); i++)
	{
		m_componentVector[i]->Update(deltaTime);
	}

	for (unsigned int i = 0; i < static_cast<unsigned int>(m_children.size()); i++)
	{
		GetChildAt(i)->Update(deltaTime);
	}
}

void dae::GameObject::Render() const //Update children
{
	for (unsigned int i = 0; i < static_cast<unsigned int>(m_componentVector.size()); i++)
	{
		m_componentVector[i]->Render();
	}

	for (unsigned int i = 0; i < static_cast<unsigned int>(m_children.size()); i++)
	{
		GetChildAt(i)->Render();
	}
}

dae::GameObject* dae::GameObject::GetParent() const
{
	return m_parent;
}

void dae::GameObject::SetParent(dae::GameObject* parent, bool keepWorldPosition)
{
	if (!CheckIfNewParentIsOurChild(parent))//Check if the new parent is one of your children/grandchildren our if our new parent this gameobject is
	{
		if (m_parent != nullptr)
		{
			m_parent->RemoveChild(this);

			m_parent = parent;
			m_parent->AddChild(this);
			m_pTransforComponent->SetPositionDirty();

			if (keepWorldPosition)
			{
				m_pTransforComponent->SetLocalPosition(m_pTransforComponent->GetLocalPosition() - m_parent->GetWorldPosition());
			}
		}
		else
		{
			m_parent = parent;
			m_parent->AddChild(this);
			m_pTransforComponent->SetPositionDirty();
		}
	}
}

int dae::GameObject::GetChildCount() const
{
	return static_cast<int>(m_children.size());
}

dae::GameObject* dae::GameObject::GetChildAt(int index) const
{
	if (index < GetChildCount())
	{
		return m_children[index];
	}
	return nullptr;
}

void dae::GameObject::AddChild(dae::GameObject* child)
{
	m_children.push_back(child);
}

void dae::GameObject::RemoveChild(dae::GameObject* child) //Memory leak
{
	m_children.erase(std::find(m_children.begin(), m_children.end(), child));
	child->SetParent(nullptr,false);
}

bool dae::GameObject::CheckIfNewParentIsOurChild(GameObject* currentParent) // recursieve keep checking our new parent his parents til we find ourself our a nullptr
{
	if (this == currentParent)
	{
		return true;
	}
	else if(currentParent == nullptr)
	{
		return false;
	}
	else
	{
		return CheckIfNewParentIsOurChild(currentParent->GetParent());
	}
}

const glm::vec3& dae::GameObject::GetWorldPosition() const
{
	return m_pTransforComponent->GetWorldPosition();
}
