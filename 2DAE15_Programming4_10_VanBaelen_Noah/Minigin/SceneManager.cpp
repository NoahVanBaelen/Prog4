#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::LateUpdate(float deltaTime)
{
	for (auto& scene : m_scenes)
	{
		scene->LateUpdate(deltaTime);
	}
}

void dae::SceneManager::FixedUpdate(float fixedTimeStep)
{
	for (auto& scene : m_scenes)
	{
		scene->FixedUpdate(fixedTimeStep);
	}
}

void dae::SceneManager::Update(float deltaTime)
{
	for(auto& scene : m_scenes)
	{
		scene->Update(deltaTime);
	}
}

void dae::SceneManager::Render()
{
	for (const auto& scene : m_scenes)
	{
		scene->Render();
	}
}

void dae::SceneManager::SetActiveScene(const std::string& name)
{
	for (std::shared_ptr<Scene> scene : m_scenes)
	{
		scene->SetSceneActive(false);
		if (scene->GetName() == name)
		{
			scene->SetSceneActive(true);
		}
	}
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_scenes.push_back(scene);
	return *scene;
}
