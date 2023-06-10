#pragma once
#include "SceneManager.h"

namespace dae
{
	class GameObject;
	class Scene final
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(std::shared_ptr<GameObject> object);
		void Remove(std::shared_ptr<GameObject> object);
		void RemoveAll();

		void LateUpdate(float deltaTime);
		void FixedUpdate(float fixedTimeStep);
		void Update(float deltaTime);
		void Render() const;

		std::string GetName() const;
		void SetSceneActive(bool isActive);

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		explicit Scene(const std::string& name);

		std::string m_name;
		std::vector < std::shared_ptr<GameObject>> m_objects{};
		bool m_IsActive{false};

		static unsigned int m_idCounter; 
	};

}
