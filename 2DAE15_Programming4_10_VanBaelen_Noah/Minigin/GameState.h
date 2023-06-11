#pragma once
#include <Vector>
#include <utility>
#include <Memory>
class SceneManager;
class CommandKeeper;

namespace dae {
	class Scene;
	class GameObject;
};

class GameState
{
public: 
	enum class CurrentMode
	{
		MAIN_MENU,
		SINGLE_PLAYER,
		COOP,
		VERSUS
	};

	GameState() = default;
	virtual ~GameState() = default;
	GameState(const GameState& other) = delete;
	GameState(GameState&& other) = delete;
	GameState& operator=(const GameState& other) = delete;
	GameState& operator=(GameState&& other) = delete;

	virtual void LateUpdate(float) = 0;
	virtual void FixedUpdate(float) = 0;
	virtual void Update(float) = 0;
	virtual void Render() = 0;
	virtual void OnEnter() = 0;
	virtual void OnExit() = 0;
	virtual CurrentMode GetCurrentMode() = 0;
	virtual std::vector<std::pair<int, std::shared_ptr<CommandKeeper>>> GetCommandVector();
protected:
	std::vector<std::pair<int, std::shared_ptr<CommandKeeper>>> m_pCommandVector;
};

class MainMenuState : public GameState
{
public:
	MainMenuState(dae::Scene* scene, std::vector<std::pair<int, std::shared_ptr<CommandKeeper>>> commandVector);
	void LateUpdate(float deltaTime) override;
	void FixedUpdate(float fixedTimeStep) override;
	void Update(float deltaTime) override;
	void Render() override;
	void OnEnter() override;
	void OnExit() override;
	CurrentMode GetCurrentMode() override;
private:
	dae::Scene* m_pScene;
};

class SinglePlayerState : public GameState
{
public:
	SinglePlayerState(dae::Scene* scene, std::vector<std::pair<int, std::shared_ptr<CommandKeeper>>> commandVector);
	void LateUpdate(float deltaTime) override;
	void FixedUpdate(float fixedTimeStep) override;
	void Update(float deltaTime) override;
	void Render() override;
	void OnEnter() override;
	void OnExit() override;
	CurrentMode GetCurrentMode() override;
private:
	dae::Scene* m_pScene;
};

class CoopState : public GameState
{
public:
	CoopState(dae::Scene* scene, std::vector<std::pair<int, std::shared_ptr<CommandKeeper>>> commandVector);
	void LateUpdate(float deltaTime) override;
	void FixedUpdate(float fixedTimeStep) override;
	void Update(float deltaTime) override;
	void Render() override;
	void OnEnter() override;
	void OnExit() override;
	CurrentMode GetCurrentMode() override;
private:
	dae::Scene* m_pScene;
};

class VersusState : public GameState
{
public:
	VersusState(dae::Scene* scene, std::vector<std::pair<int, std::shared_ptr<CommandKeeper>>> commandVector);
	void LateUpdate(float deltaTime) override;
	void FixedUpdate(float fixedTimeStep) override;
	void Update(float deltaTime) override;
	void Render() override;
	void OnEnter() override;
	void OnExit() override;
	CurrentMode GetCurrentMode() override;
private:
	dae::Scene* m_pScene;
};

