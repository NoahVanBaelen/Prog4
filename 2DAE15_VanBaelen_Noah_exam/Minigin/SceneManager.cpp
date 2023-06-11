#include "SceneManager.h"
#include "Scene.h"
#include "GameState.h"

void dae::SceneManager::LateUpdate(float deltaTime)
{
	m_pCurrentState->LateUpdate(deltaTime);
}

void dae::SceneManager::FixedUpdate(float fixedTimeStep)
{
	m_pCurrentState->FixedUpdate(fixedTimeStep);
}

void dae::SceneManager::Update(float deltaTime)
{
	m_pCurrentState->Update(deltaTime);
}

void dae::SceneManager::Render()
{
	m_pCurrentState->Render();
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
	m_pCurrentState = newState;
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
