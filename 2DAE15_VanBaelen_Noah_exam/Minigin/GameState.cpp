#include "GameState.h"
#include "Scene.h"
#include "Command.h"
#include "CommandKeeper.h"
#include "Input.h"

MainMenuState::MainMenuState(dae::Scene* scene)
	:m_pScene{ scene }
{
}

void MainMenuState::LateUpdate(float deltaTime)
{
	m_pScene->LateUpdate(deltaTime);
}

void MainMenuState::FixedUpdate(float fixedTimeStep)
{
	m_pScene->FixedUpdate(fixedTimeStep);
}

void MainMenuState::Update(float deltaTime)
{
	m_pScene->Update(deltaTime);
}

void MainMenuState::Render()
{
	m_pScene->Render();
}

GameState::CurrentMode MainMenuState::GetCurrentMode()
{
	return CurrentMode::MAIN_MENU;
}



SinglePlayerState::SinglePlayerState(dae::Scene* scene)
	:m_pScene{ scene }
{
}

void SinglePlayerState::LateUpdate(float deltaTime)
{
	m_pScene->LateUpdate(deltaTime);
}

void SinglePlayerState::FixedUpdate(float fixedTimeStep)
{
	m_pScene->FixedUpdate(fixedTimeStep);
}

void SinglePlayerState::Update(float deltaTime)
{
	m_pScene->Update(deltaTime);
}

void SinglePlayerState::Render()
{
	m_pScene->Render();
}

GameState::CurrentMode SinglePlayerState::GetCurrentMode()
{
	return CurrentMode::SINGLE_PLAYER;
}

CoopState::CoopState(dae::Scene* scene)
	:m_pScene{ scene }
{
}

void CoopState::LateUpdate(float deltaTime)
{
	m_pScene->LateUpdate(deltaTime);
}

void CoopState::FixedUpdate(float fixedTimeStep)
{
	m_pScene->FixedUpdate(fixedTimeStep);
}

void CoopState::Update(float deltaTime)
{
	m_pScene->Update(deltaTime);
}

void CoopState::Render()
{
	m_pScene->Render();
}

GameState::CurrentMode CoopState::GetCurrentMode()
{
	return CurrentMode::COOP;
}

VersusState::VersusState(dae::Scene* scene)
	:m_pScene{ scene }
{
}

void VersusState::LateUpdate(float deltaTime)
{
	m_pScene->LateUpdate(deltaTime);
}

void VersusState::FixedUpdate(float fixedTimeStep)
{
	m_pScene->FixedUpdate(fixedTimeStep);
}

void VersusState::Update(float deltaTime)
{
	m_pScene->Update(deltaTime);
}

void VersusState::Render()
{
	m_pScene->Render();
}

GameState::CurrentMode VersusState::GetCurrentMode()
{
	return CurrentMode::VERSUS;
}

ScoreScreenState::ScoreScreenState(dae::Scene* scene)
	:m_pScene{ scene }
{
}

void ScoreScreenState::LateUpdate(float deltaTime)
{
	m_pScene->LateUpdate(deltaTime);
}

void ScoreScreenState::FixedUpdate(float fixedTimeStep)
{
	m_pScene->FixedUpdate(fixedTimeStep);
}

void ScoreScreenState::Update(float deltaTime)
{
	m_pScene->Update(deltaTime);
}

void ScoreScreenState::Render()
{
	m_pScene->Render();
}

GameState::CurrentMode ScoreScreenState::GetCurrentMode()
{
	return CurrentMode::SCORELIST;
}
