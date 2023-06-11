#include "SceneManager.h"
#include "Scene.h"
#include "GameState.h"

void dae::SceneManager::LateUpdate(float deltaTime)
{
	m_pCurrentState->LateUpdate(deltaTime);
	//for (auto& scene : m_scenes)
	//{
	//	scene->LateUpdate(deltaTime);
	//}
}

void dae::SceneManager::FixedUpdate(float fixedTimeStep)
{
	m_pCurrentState->FixedUpdate(fixedTimeStep);
	//for (auto& scene : m_scenes)
	//{
	//	scene->FixedUpdate(fixedTimeStep);
	//}
}

void dae::SceneManager::Update(float deltaTime)
{
	m_pCurrentState->Update(deltaTime);
	//for(auto& scene : m_scenes)
	//{
	//	scene->Update(deltaTime);
	//}
}

void dae::SceneManager::Render()
{
	m_pCurrentState->Render();
	/*for (const auto& scene : m_scenes)
	{
		scene->Render();
	}*/
}

std::shared_ptr<dae::Scene> dae::SceneManager::GetSceneByName(std::string name) const
{
	for (std::shared_ptr<dae::Scene> scene : m_scenes)
	{
		if (name == scene->GetName())
		{
			return scene;
		}
	}
	return nullptr;
}

void dae::SceneManager::SetState(std::shared_ptr<GameState> newState)
{
	if (m_pCurrentState)
	{
		m_pCurrentState->OnExit();
	}
	m_pCurrentState = newState;
	m_pCurrentState->OnEnter();
}

std::shared_ptr<GameState> dae::SceneManager::GetState() const
{
	return m_pCurrentState;
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_scenes.push_back(scene);
	return *scene;
}
