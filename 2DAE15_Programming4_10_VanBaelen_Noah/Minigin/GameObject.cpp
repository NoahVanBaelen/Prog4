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
	m_children = std::vector<std::shared_ptr<GameObject>>{};
}

dae::GameObject::~GameObject()
{}

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

void dae::GameObject::LateUpdate(float deltaTime)
{
	for (unsigned int i = 0; i < static_cast<unsigned int>(m_children.size()); i++)
	{
		GetChildAt(i)->LateUpdate(deltaTime);

		if (GetChildAt(i)->m_MarkedForDestroy)
		{
			RemoveChild(GetChildAt(i));
		}
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

std::shared_ptr<dae::GameObject> dae::GameObject::GetParent() const
{
	return m_parent;
}

void dae::GameObject::SetParent(std::shared_ptr<GameObject> parent, bool keepWorldPosition)
{
	if (m_parent != nullptr)
	{
		m_parent = parent;
		m_pTransforComponent->SetPositionDirty();

		if (keepWorldPosition)
		{
			m_pTransforComponent->SetLocalPosition(m_pTransforComponent->GetLocalPosition() - m_parent->GetWorldPosition());
		}
	}
	else
	{
		m_parent = parent;
		m_pTransforComponent->SetPositionDirty();

		if (keepWorldPosition)
		{
			m_pTransforComponent->SetLocalPosition(m_pTransforComponent->GetLocalPosition() - m_parent->GetWorldPosition());
		}
	}
}

int dae::GameObject::GetChildCount() const
{
	return static_cast<int>(m_children.size());
}

std::shared_ptr<dae::GameObject> dae::GameObject::GetChildAt(int index) const
{
	if (index < GetChildCount())
	{
		return m_children[index];
	}
	return nullptr;
}

void dae::GameObject::AddChild(std::shared_ptr<dae::GameObject> child, bool keepWorldPosition)
{
	if (!child->CheckIfNewParentIsOurChild(this))//Check if the new parent is one of your children/grandchildren our if our new parent this gameobject is
	{
		if (child->GetParent() != nullptr)
		{
			child->GetParent()->RemoveChild(child);
		}

		child->SetParent(std::make_shared<dae::GameObject>(*this), keepWorldPosition);
		m_children.emplace_back(std::move(child));
	}
}

//void dae::GameObject::AddChild(std::shared_ptr<dae::GameObject> child)
//{
//	m_children.emplace_back(std::move(child));
//}

void dae::GameObject::RemoveChild(std::shared_ptr<dae::GameObject> child)
{
	m_children.erase(std::remove(m_children.begin(), m_children.end(), child), m_children.end());
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
		return CheckIfNewParentIsOurChild(currentParent->GetParent().get());
	}
}

const glm::vec3& dae::GameObject::GetWorldPosition() const
{
	return m_pTransforComponent->GetWorldPosition();
}
