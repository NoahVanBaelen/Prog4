#pragma once
#include "Controller.h"
#include "Command.h"
#include "Singleton.h"
#include <vector>
#include <map>
#include <set>

class Input final : public dae::Singleton<Input>
{

public:

	enum class ButtonLogic
	{
		Down,
		Up,
		Pressed
	};

	void HandleInput(float deltaTime, unsigned controllerIndex);
	int AddController();
	void AddCommand(unsigned controllerIndex, Controller::ControllerButton button, ButtonLogic buttonLogic, Command* command);

private:
	using ControllerKey = std::pair<unsigned, Controller::ControllerButton>; //Which controller and Button
	using ControllerLogic = std::pair<ControllerKey, ButtonLogic>; //whether the button has to be down, up or pressed this frame
	using ControllerCommandsMap = std::map<ControllerKey, std::unique_ptr<Command>>; //which command is binded to the button

	using ControllerLogicMap = std::map<ControllerKey, ButtonLogic>;
	using ControllerKeyMap = std::map<ControllerKey, Controller::ControllerButton>;
	ControllerCommandsMap m_ControllerCommands{};
	ControllerLogicMap m_ControllerLogics{};

	std::vector<std::unique_ptr<Controller>> m_Controllers;
	std::set<Controller::ControllerButton> m_Buttons;
};

