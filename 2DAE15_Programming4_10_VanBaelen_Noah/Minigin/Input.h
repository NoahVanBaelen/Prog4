#pragma once
#include <SDL.h>
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

	void HandleInput(float deltaTime);
	int AddController();
	void RemoveAllControllers();
	void AddCommand(unsigned int controllerIndex, Controller::ControllerButton button, ButtonLogic buttonLogic, Command* command);
	void AddCommand(SDL_Scancode key, ButtonLogic buttonLogic,Command* command);
	void RemoveAllCommands();

private:
	using ControllerKey = std::pair<unsigned int, Controller::ControllerButton>; //Which controller and Button
	using ControllerLogic = std::pair<ControllerKey, ButtonLogic>; //whether the button has to be down, up or pressed this frame
	using ControllerCommandsMap = std::map<ControllerKey, std::unique_ptr<Command>>; //which command is binded to the button

	using ControllerLogicMap = std::map<ControllerKey, ButtonLogic>;
	using ControllerKeyMap = std::map<ControllerKey, Controller::ControllerButton>;
	ControllerCommandsMap m_ControllerCommands{};
	ControllerLogicMap m_ControllerLogics{};

	using KeyBoardKeyCommandsMap = std::map<SDL_Scancode, std::unique_ptr<Command>>;
	using KeyLogicMap = std::map<SDL_Scancode, ButtonLogic>;
	using KeyLastFrameState = std::map<SDL_Scancode, bool>;
	KeyBoardKeyCommandsMap m_KeyCommands{};
	KeyLogicMap m_KeyLogics{};
	KeyLastFrameState m_KeyStateLastFrame{};

	std::vector<std::unique_ptr<Controller>> m_Controllers;
	std::set<Controller::ControllerButton> m_Buttons;
	std::set<SDL_Scancode> m_Keys;
};

