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

	class GameObject final : public std::enable_shared_from_this<GameObject>
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
		virtual void LateUpdate(float);
		virtual void Render() const;

		std::shared_ptr<GameObject> GetParent() const;
		void MakeParentNull();
		int GetChildCount() const;
		std::shared_ptr<GameObject> GetChildAt(int index) const;

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

		template <typename T> void RemoveComponent() //Memory leak
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

		bool m_MarkedForDestroy{ false };

		void SetParent(std::shared_ptr<GameObject> newParent, bool keepWorldPosition);
		void RemoveChild(std::shared_ptr<GameObject> child);

	private:
		void AddChild(std::shared_ptr<GameObject> child);
		bool CheckIfNewParentIsOurChild(GameObject* currentParent);

		std::vector<std::shared_ptr<BaseComponent>> m_componentVector;
		std::shared_ptr<TransformComponent> m_pTransforComponent;

		std::weak_ptr<GameObject> m_pParent;//weak pointer to prevent circular dependencies memory leaks
		std::vector<std::shared_ptr<GameObject>> m_pChildren{nullptr};
	};
};
