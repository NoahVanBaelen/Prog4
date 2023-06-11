#include "GameState.h"
#include "Scene.h"
#include "Command.h"
#include "CommandKeeper.h"
#include "Input.h"

MainMenuState::MainMenuState(dae::Scene* scene, std::vector<std::pair<int, std::shared_ptr<CommandKeeper>>> commandVector)
	:m_pScene{ scene }
{
	m_pCommandVector = commandVector;
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

void MainMenuState::OnEnter()
{
	for (int i = 0; i < m_pCommandVector.size(); i++)
	{
		if (m_pCommandVector[i].first == 0)
		{
			auto& input = Input::GetInstance();
			std::shared_ptr<CommandKeeper> keeper = m_pCommandVector[i].second;
			if (keeper->UsesKey())
			{
				input.AddCommand(keeper->GetKey(), keeper->GetLogic(), keeper->GetCommand());
			}
			else
			{
				input.AddCommand(keeper->GetControllerIndex(), keeper->GetButton(), keeper->GetLogic(), keeper->GetCommand());
			}
		}
	}
}

void MainMenuState::OnExit()
{
	Input::GetInstance().RemoveAllCommands();
}

GameState::CurrentMode MainMenuState::GetCurrentMode()
{
	return CurrentMode::MAIN_MENU;
}



SinglePlayerState::SinglePlayerState(dae::Scene* scene, std::vector<std::pair<int, std::shared_ptr<CommandKeeper>>> commandVector)
	:m_pScene{ scene }
{
	m_pCommandVector = commandVector;
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

void SinglePlayerState::OnEnter()
{
	for (int i = 0; i < m_pCommandVector.size(); i++)
	{
		if (m_pCommandVector[i].first == 1)
		{
			auto& input = Input::GetInstance();
			std::shared_ptr<CommandKeeper> keeper = m_pCommandVector[i].second;
			if (keeper->UsesKey())
			{
				input.AddCommand(keeper->GetKey(), keeper->GetLogic(), keeper->GetCommand());
			}
			else
			{
				input.AddCommand(keeper->GetControllerIndex(), keeper->GetButton(), keeper->GetLogic(), keeper->GetCommand());
			}
		}
	}
}

void SinglePlayerState::OnExit()
{
	Input::GetInstance().RemoveAllCommands();
}

GameState::CurrentMode SinglePlayerState::GetCurrentMode()
{
	return CurrentMode::SINGLE_PLAYER;
}

CoopState::CoopState(dae::Scene* scene, std::vector<std::pair<int, std::shared_ptr<CommandKeeper>>> commandVector)
	:m_pScene{ scene }
{
	m_pCommandVector = commandVector;
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

void CoopState::OnEnter()
{
}

void CoopState::OnExit()
{
}

GameState::CurrentMode CoopState::GetCurrentMode()
{
	return CurrentMode::COOP;
}

VersusState::VersusState(dae::Scene* scene, std::vector<std::pair<int, std::shared_ptr<CommandKeeper>>> commandVector)
	:m_pScene{ scene }
{
	m_pCommandVector = commandVector;
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

void VersusState::OnEnter()
{
}

void VersusState::OnExit()
{
}

GameState::CurrentMode VersusState::GetCurrentMode()
{
	return CurrentMode::VERSUS;
}

std::vector<std::pair<int, std::shared_ptr<CommandKeeper>>> GameState::GetCommandVector()
{
	return m_pCommandVector;
}
