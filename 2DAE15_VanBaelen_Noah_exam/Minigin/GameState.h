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
		MAIN_MENU = 0,
		SINGLE_PLAYER = 1,
		COOP = 2,
		VERSUS = 3,
		SCORELIST = 4
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
	virtual CurrentMode GetCurrentMode() = 0;
};

class MainMenuState : public GameState
{
public:
	MainMenuState(dae::Scene* scene);
	void LateUpdate(float deltaTime) override;
	void FixedUpdate(float fixedTimeStep) override;
	void Update(float deltaTime) override;
	void Render() override;
	CurrentMode GetCurrentMode() override;
private:
	dae::Scene* m_pScene;
};

class SinglePlayerState : public GameState
{
public:
	SinglePlayerState(dae::Scene* scene);
	void LateUpdate(float deltaTime) override;
	void FixedUpdate(float fixedTimeStep) override;
	void Update(float deltaTime) override;
	void Render() override;
	CurrentMode GetCurrentMode() override;
private:
	dae::Scene* m_pScene;
};

class CoopState : public GameState
{
public:
	CoopState(dae::Scene* scene);
	void LateUpdate(float deltaTime) override;
	void FixedUpdate(float fixedTimeStep) override;
	void Update(float deltaTime) override;
	void Render() override;
	CurrentMode GetCurrentMode() override;
private:
	dae::Scene* m_pScene;
};

class VersusState : public GameState
{
public:
	VersusState(dae::Scene* scene);
	void LateUpdate(float deltaTime) override;
	void FixedUpdate(float fixedTimeStep) override;
	void Update(float deltaTime) override;
	void Render() override;
	CurrentMode GetCurrentMode() override;
private:
	dae::Scene* m_pScene;
};

class ScoreScreenState : public GameState
{
public:
	ScoreScreenState(dae::Scene* scene);
	void LateUpdate(float deltaTime) override;
	void FixedUpdate(float fixedTimeStep) override;
	void Update(float deltaTime) override;
	void Render() override;
	CurrentMode GetCurrentMode() override;
private:
	dae::Scene* m_pScene;
};