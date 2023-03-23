#include "Input.h"

void Input::HandleInput(float deltaTime, unsigned controllerIndex)
{
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

int Input::AddController()
{
	int newControllerIndex = m_Controllers.size();
	m_Controllers.push_back(std::make_unique<Controller>(new Controller{ newControllerIndex }));
	return newControllerIndex;
}

void Input::AddCommand(unsigned controllerIndex, Controller::ControllerButton button, ButtonLogic buttonLogic, Command* command)
{
	ControllerKey newControllerKey = std::pair<unsigned, Controller::ControllerButton>(controllerIndex, button);
	m_ControllerCommands.emplace(newControllerKey, std::make_unique<Command>(command));
	m_ControllerLogics.emplace(newControllerKey, buttonLogic);

	m_Buttons.insert(button);
}
