#include "Input.h"
#include <iostream>

void Input::HandleInput(float deltaTime)
{
	for (unsigned int controllerIndex = 0; controllerIndex < m_Controllers.size(); controllerIndex++)
	{
		m_Controllers[controllerIndex]->Update();
		for (Controller::ControllerButton button : m_Buttons)//check every button that has been bounded to a command
		{
			ControllerKey controllerKey{ controllerIndex,button };
			if (m_ControllerCommands.find(controllerKey) != m_ControllerCommands.end()) //check if key is found
			{

				switch (m_ControllerLogics.at(controllerKey)) //check whether button has to be up down or pressed to execute the command
				{
				case ButtonLogic::Down:
					if (m_Controllers[controllerIndex]->IsDown(button))
					{
						m_ControllerCommands.at(controllerKey)->Execute(deltaTime);
					}
					break;
				case ButtonLogic::Up:
					if (m_Controllers[controllerIndex]->IsUp(button))
					{
						m_ControllerCommands.at(controllerKey)->Execute(deltaTime);
					}
					break;
				case ButtonLogic::Pressed:
					if (m_Controllers[controllerIndex]->IsPressed(button))
					{
						m_ControllerCommands.at(controllerKey)->Execute(deltaTime);
					}
					break;
				}
			}
		}
	}

	const Uint8* state = SDL_GetKeyboardState(NULL);
	for (SDL_Scancode keyCode : m_Keys)
	{
		switch (m_KeyLogics.at(keyCode))
		{
		case ButtonLogic::Down:
			if (!m_KeyStateLastFrame.at(keyCode) && state[keyCode])
			{
				m_KeyCommands.at(keyCode)->Execute(deltaTime);
			}
			break;
		case ButtonLogic::Up:
			if (m_KeyStateLastFrame.at(keyCode) && !state[keyCode])
			{
				m_KeyCommands.at(keyCode)->Execute(deltaTime);
			}
			break;
		case ButtonLogic::Pressed:
			if (m_KeyStateLastFrame.at(keyCode) && state[keyCode])
			{
				m_KeyCommands.at(keyCode)->Execute(deltaTime);
			}
			break;
		default:
			break;
		}
		m_KeyStateLastFrame.at(keyCode) = state[keyCode];
	/*	if (state[keyCode])
		{
			m_KeyCommands.at(keyCode)->Execute(deltaTime);
		}*/
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

void Input::AddCommand(unsigned int controllerIndex, Controller::ControllerButton button, ButtonLogic buttonLogic, Command* command)
{
	ControllerKey newControllerKey = std::pair<unsigned int, Controller::ControllerButton>(controllerIndex, button);
	m_ControllerCommands.emplace(newControllerKey, command);
	m_ControllerLogics.emplace(newControllerKey, buttonLogic);

	m_Buttons.insert(button);
}

void Input::AddCommand(SDL_Scancode key, ButtonLogic buttonLogic,Command* command)
{
	m_KeyCommands.emplace(key, command);
	m_KeyLogics.emplace(key, buttonLogic);
	m_KeyStateLastFrame.emplace(key, false);

	m_Keys.insert(key);
}

void Input::RemoveAllCommands()
{
	m_ControllerCommands.clear();
	m_ControllerLogics.clear();
	m_KeyCommands.clear();
	m_Keys.clear();
}
