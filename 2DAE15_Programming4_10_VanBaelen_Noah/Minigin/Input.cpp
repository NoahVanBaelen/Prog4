#include "Input.h"
#include <iostream>
#include "SceneManager.h"
#include "GameState.h"

void Input::HandleInput(float deltaTime)
{
	unsigned int currentMode{ static_cast<unsigned int>(dae::SceneManager::GetInstance().GetState()->GetCurrentMode()) };
	for (unsigned int controllerIndex = 0; controllerIndex < m_Controllers.size(); controllerIndex++)
	{
		m_Controllers[controllerIndex]->Update();
		for (Controller::ControllerButton button : m_Buttons)//check every button that has been bounded to a command
		{
			ControllerKey controllerKey{ controllerIndex,button };
			ControllState controllerState{ controllerKey,currentMode };
			if (m_ControllerCommands.find(controllerState) != m_ControllerCommands.end()) //check if key is found
			{

				switch (m_ControllerLogics.at(controllerState)) //check whether button has to be up down or pressed to execute the command
				{
				case ButtonLogic::Down:
					if (m_Controllers[controllerIndex]->IsDown(button))
					{
						m_ControllerCommands.at(controllerState)->Execute(deltaTime);
					}
					break;
				case ButtonLogic::Up:
					if (m_Controllers[controllerIndex]->IsUp(button))
					{
						m_ControllerCommands.at(controllerState)->Execute(deltaTime);
					}
					break;
				case ButtonLogic::Pressed:
					if (m_Controllers[controllerIndex]->IsPressed(button))
					{
						m_ControllerCommands.at(controllerState)->Execute(deltaTime);
					}
					break;
				}
			}
		}
	}

	const Uint8* state = SDL_GetKeyboardState(NULL);
	for (SDL_Scancode keyCode : m_Keys)
	{
		KeyBoardState keyState{ keyCode,currentMode };
		if (m_KeyLogics.find(keyState) != m_KeyLogics.end())
		{
			switch (m_KeyLogics.at(keyState))
			{
			case ButtonLogic::Down:
				if (!m_KeyStateLastFrame.at(keyState) && state[keyCode])
				{
					m_KeyCommands.at(keyState)->Execute(deltaTime);
				}
				break;
			case ButtonLogic::Up:
				if (m_KeyStateLastFrame.at(keyState) && !state[keyCode])
				{
					m_KeyCommands.at(keyState)->Execute(deltaTime);
				}
				break;
			case ButtonLogic::Pressed:
				if (m_KeyStateLastFrame.at(keyState) && state[keyCode])
				{
					m_KeyCommands.at(keyState)->Execute(deltaTime);
				}
				break;
			default:
				break;
			}
			m_KeyStateLastFrame.at(keyState) = state[keyCode];
		}
	}
}

int Input::AddController()
{
	int newControllerIndex = static_cast<int>(m_Controllers.size());
	m_Controllers.push_back( std::make_unique<Controller>(newControllerIndex));
	return newControllerIndex;
}

void Input::RemoveAllControllers()
{
	m_Controllers.clear();
}

void Input::AddCommand(unsigned int stateIndex, unsigned int controllerIndex, Controller::ControllerButton button, ButtonLogic buttonLogic, Command* command)
{
	ControllerKey newControllerKey = std::pair<unsigned int, Controller::ControllerButton>(controllerIndex, button);
	ControllState newControllState = std::pair<ControllerKey, unsigned int>(newControllerKey, stateIndex);
	m_ControllerCommands.emplace(newControllState, command);
	m_ControllerLogics.emplace(newControllState, buttonLogic);

	m_Buttons.insert(button);
}

void Input::AddCommand(unsigned int stateIndex, SDL_Scancode key, ButtonLogic buttonLogic,Command* command)
{
	KeyBoardState newKeyState = std::pair<SDL_Scancode, unsigned int>(key, stateIndex);
	m_KeyCommands.emplace(newKeyState, command);
	m_KeyLogics.emplace(newKeyState, buttonLogic);
	m_KeyStateLastFrame.emplace(newKeyState, false);

	m_Keys.insert(key);
}

void Input::RemoveAllCommands()
{
	m_ControllerCommands.clear();
	m_ControllerLogics.clear();
	m_KeyCommands.clear();
	m_Keys.clear();
	m_KeyLogics.clear();
	m_KeyStateLastFrame.clear();
}
