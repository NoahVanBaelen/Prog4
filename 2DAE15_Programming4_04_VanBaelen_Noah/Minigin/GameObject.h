#pragma once
#include <memory>
#include "Transform.h"
#include <vector>
#include <typeinfo>

class TransformComponent;
class BaseComponent;
namespace dae
{
	class Texture2D;

	// todo: this should become final.
	class GameObject final
	{
	public:

		GameObject();
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		virtual void FixedUpdate(float fixedTimeStep);
		virtual void Update(float deltaTime);
		virtual void Render() const;

		GameObject* GetParent() const;
		void SetParent(GameObject* parent, bool keepWorldPosition);
		int GetChildCount() const;
		GameObject* GetChildAt(int index) const;

		const glm::vec3& GetWorldPosition() const;

		template <typename T> std::shared_ptr<T> AddComponent()
		{
			if (std::is_base_of<BaseComponent, T>())
			{
				m_componentVector.emplace_back(std::make_shared<T>(this));
				return  std::static_pointer_cast<T>(m_componentVector.back());
			}
			return nullptr;
		}

		template <typename T> std::shared_ptr<T> GetComponent()
		{
			for (unsigned int i = 0; i < static_cast<unsigned int>(m_componentVector.size()); i++)
			{
				if (typeid(*m_componentVector[i].get()).name() == typeid(T).name())
				{
					return std::static_pointer_cast<T>(m_componentVector[i]);
				}
			}
			return nullptr;
		}

		template <typename T> void RemoveComponent() //Memroy leak
		{
			for (unsigned int i = 0; i < static_cast<unsigned int>(m_componentVector.size()); i++)
			{
				if (typeid(*m_componentVector[i].get()).name() == typeid(T).name())
				{
					m_componentVector.erase(m_componentVector.begin() + i);
					break;
				}
			}
		}

		template <typename T> bool HasComponent()
		{
			for (unsigned int i = 0; i < static_cast<unsigned int>(m_componentVector.size()); i++)
			{
				if (typeid(*m_componentVector[i].get()).name() == typeid(T).name())
				{
					return true;
				}
			}

			return false;
		}

	private:
		void AddChild(GameObject* child);
		void RemoveChild(GameObject* child);
		bool CheckIfNewParentIsOurChild(GameObject* currentParent);

		std::vector<std::shared_ptr<BaseComponent>> m_componentVector;
		std::shared_ptr<TransformComponent> m_pTransforComponent;

		GameObject* m_parent{nullptr};
		std::vector<GameObject*> m_children;
	};
};
