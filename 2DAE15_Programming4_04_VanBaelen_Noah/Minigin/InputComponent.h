#pragma once
#include "BaseComponent.h"
#include "Input.h"

class InputComponent final : public BaseComponent
{
public:
	InputComponent(dae::GameObject* pOwner);

	InputComponent(const InputComponent& other) = delete;
	InputComponent(InputComponent&& other) = delete;
	InputComponent& operator=(const InputComponent& other) = delete;
	InputComponent& operator=(InputComponent&& other) = delete;

	void Update(float deltaTime) override;
	void SetCommand(Controller::ControllerButton button, Input::ButtonLogic buttonLogic, Command command);

private:

	int m_numController;
	Input m_Input;
};

