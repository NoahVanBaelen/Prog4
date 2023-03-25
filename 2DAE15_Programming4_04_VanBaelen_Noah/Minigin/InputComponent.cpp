#include "InputComponent.h"

InputComponent::InputComponent(dae::GameObject* pOwner)
 :BaseComponent(pOwner)
{
	m_numController = m_Input.AddController();
}

void InputComponent::Update(float deltaTime)
{
	m_Input.HandleInput(deltaTime, m_numController);
}

void InputComponent::SetCommand(Controller::ControllerButton button, Input::ButtonLogic buttonLogic, Command* command)
{
	m_Input.AddCommand(m_numController, button, buttonLogic, command);
}
