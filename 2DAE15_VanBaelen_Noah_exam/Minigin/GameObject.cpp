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
	m_pChildren = std::vector<std::shared_ptr<GameObject>>{};
}

dae::GameObject::~GameObject()
{

}

void dae::GameObject::FixedUpdate(float fixedTimeStep) //Update children
{
	for (unsigned int i = 0; i < static_cast<unsigned int>(m_componentVector.size()); i++)
	{
		m_componentVector[i]->FixedUpdate(fixedTimeStep);
	}

	for (unsigned int i = 0; i < static_cast<unsigned int>(m_pChildren.size()); i++)
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

	for (unsigned int i = 0; i < static_cast<unsigned int>(m_pChildren.size()); i++)
	{
		GetChildAt(i)->Update(deltaTime);
	}
}

void dae::GameObject::LateUpdate(float deltaTime)
{
	for (unsigned int i = 0; i < static_cast<unsigned int>(m_componentVector.size()); i++)
	{
		m_componentVector[i]->LateUpdate(deltaTime);
	}

	for (unsigned int i = 0; i < static_cast<unsigned int>(m_pChildren.size()); i++)
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

	for (unsigned int i = 0; i < static_cast<unsigned int>(m_pChildren.size()); i++)
	{
		GetChildAt(i)->Render();
	}
}

std::shared_ptr<dae::GameObject> dae::GameObject::GetParent() const
{
	return m_pParent.lock();
}

void dae::GameObject::MakeParentNull()
{
	m_pParent.reset();
}

int dae::GameObject::GetChildCount() const
{
	return static_cast<int>(m_pChildren.size());
}

std::shared_ptr<dae::GameObject> dae::GameObject::GetChildAt(int index) const
{
	if (index < GetChildCount())
	{
		return m_pChildren[index];
	}
	return nullptr;
}

void dae::GameObject::SetParent(std::shared_ptr<GameObject> newParent, bool keepWorldPosition)
{
	if (!CheckIfNewParentIsOurChild(newParent.get()))//makes sure that our new parent isnt a child of us
	{
		if (m_pParent.lock()) //Dettach itself from previous parent
		{
			m_pParent.lock()->RemoveChild(shared_from_this());
		}

		m_pParent = newParent;
		m_pTransforComponent->SetPositionDirty();

		if (keepWorldPosition)
		{
			m_pTransforComponent->SetLocalPosition(m_pTransforComponent->GetLocalPosition() - m_pParent.lock()->GetWorldPosition());
		}

		// Add itself as a child to the given parent
		if (m_pParent.lock())
		{
			m_pParent.lock()->AddChild(shared_from_this());
		}
	}
}

void dae::GameObject::AddChild(std::shared_ptr<GameObject> child)
{
	m_pChildren.push_back(child);
}

void dae::GameObject::RemoveChild(std::shared_ptr<GameObject> child)
{
	// Remove the given child from the children list
	m_pChildren.erase(std::remove(m_pChildren.begin(), m_pChildren.end(), child), m_pChildren.end());

	// Remove itself as a parent of the child
	child->MakeParentNull();

	child->GetComponent<TransformComponent>()->SetPositionDirty();
}

void dae::GameObject::DestroyAllChildren()
{
	for (std::shared_ptr<dae::GameObject> child : m_pChildren)
	{
		child->m_MarkedForDestroy = true;
	}
}

void dae::GameObject::MarkForDestroy()
{
	m_MarkedForDestroy = true;
}

bool dae::GameObject::GetIsMarkedForDestroy() const
{
	return m_MarkedForDestroy;
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
