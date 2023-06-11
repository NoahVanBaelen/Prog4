#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"

class GameState;
namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);

		void LateUpdate(float deltaTime);
		void FixedUpdate(float fixedTimeStep);
		void Update(float deltaTime);
		void Render();
		std::shared_ptr<Scene> GetSceneByName(std::string name) const;
		void SetState(std::shared_ptr<GameState> newState);
		std::shared_ptr<GameState> GetState() const;

	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_scenes;
		std::shared_ptr<GameState> m_pCurrentState;
	};
}
