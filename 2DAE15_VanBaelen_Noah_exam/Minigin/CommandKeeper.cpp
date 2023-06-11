#include "CommandKeeper.h"

CommandKeeper::CommandKeeper(Command* command, Input::ButtonLogic logic, Controller::ControllerButton button, int indexController)
	:m_ButtonLogic{logic}
	,m_ControllerButton{ button }
	,m_Key{ SDL_SCANCODE_0 }
	,m_ControllerIndex{indexController}
{
	m_Command = command;
	m_UsesKey = false;
}

CommandKeeper::CommandKeeper(Command* command, Input::ButtonLogic logic, SDL_Scancode key, int indexController)
	:m_ButtonLogic{ logic }
	,m_ControllerButton{ Controller::ControllerButton::Start }
	,m_Key{ key }
	,m_ControllerIndex{ indexController }
{
	m_Command = command;
	m_UsesKey = true;
}

bool CommandKeeper::UsesKey()
{
	return m_UsesKey;
}

Command* CommandKeeper::GetCommand() const
{
	return m_Command;
}

Input::ButtonLogic CommandKeeper::GetLogic() const
{
	return m_ButtonLogic;
}

Controller::ControllerButton CommandKeeper::GetButton() const
{
	return m_ControllerButton;
}

SDL_Scancode CommandKeeper::GetKey() const
{
	return m_Key;
}

int CommandKeeper::GetControllerIndex() const
{
	return m_ControllerIndex;
}
