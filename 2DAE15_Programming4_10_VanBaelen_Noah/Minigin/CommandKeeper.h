#pragma once
#include "Input.h"
#include "Controller.h"

class Command;
class CommandKeeper
{
public:
	CommandKeeper(Command* command, Input::ButtonLogic logic, Controller::ControllerButton button,int indexController);
	CommandKeeper(Command* command, Input::ButtonLogic logic, SDL_Scancode key, int indexController);
	bool UsesKey();
	
	Command* GetCommand() const;
	Input::ButtonLogic GetLogic() const;
	Controller::ControllerButton GetButton() const;
	SDL_Scancode GetKey() const;
	int GetControllerIndex() const;
private:
	int m_ControllerIndex{ -1 };
	Command* m_Command;
	Input::ButtonLogic m_ButtonLogic;
	Controller::ControllerButton m_ControllerButton;
	SDL_Scancode m_Key;
	bool m_UsesKey{ false };
};

