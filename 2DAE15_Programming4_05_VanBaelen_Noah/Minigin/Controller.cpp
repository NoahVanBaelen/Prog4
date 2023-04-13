#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <XInput.h>
#include <iostream>
#include <thread>
#pragma comment(lib, "xinput.lib")

#include "Controller.h"


class Controller::ControllerImpl
{
	XINPUT_STATE previousState{};
	XINPUT_STATE currentState{};

	WORD buttonsPressedThisFrame;
	WORD buttonsReleasedThisFrame;

	int _controllerIndex{};
public:
	ControllerImpl(unsigned int controllerIndex)
	{
		ZeroMemory(&previousState, sizeof(_XINPUT_STATE));
		ZeroMemory(&currentState, sizeof(_XINPUT_STATE));
		_controllerIndex = controllerIndex;
	}

	void Update()
	{
		CopyMemory(&previousState, &currentState, sizeof(XINPUT_STATE));
		ZeroMemory(&currentState, sizeof(XINPUT_STATE));
		XInputGetState(_controllerIndex, &currentState);

		auto buttonChanges = currentState.Gamepad.wButtons ^ previousState.Gamepad.wButtons;
		buttonsPressedThisFrame = buttonChanges & currentState.Gamepad.wButtons;
		buttonsReleasedThisFrame = buttonChanges & (~currentState.Gamepad.wButtons);
	}

	bool IsDownThisFrame(unsigned int button) const { return buttonsPressedThisFrame & button; }
	bool IsUpThisFrame(unsigned int button) const { return buttonsReleasedThisFrame & button; }
	bool IsPressed(unsigned int button) const { return currentState.Gamepad.wButtons & button; }

	void SetControllerIndex(int controllerIndex) { _controllerIndex = controllerIndex; }
};

Controller::Controller(unsigned int controllerIndex)
{
	m_pImpl = std::make_unique<ControllerImpl>(controllerIndex);
}

Controller::~Controller()
{}

void Controller::Update()
{
	m_pImpl->Update();
}

bool Controller::IsDown(ControllerButton button) const
{
	return m_pImpl->IsDownThisFrame(static_cast<unsigned int>(button));
}

bool Controller::IsUp(ControllerButton button) const
{
	return m_pImpl->IsUpThisFrame(static_cast<unsigned int>(button));
}

bool Controller::IsPressed(ControllerButton button) const
{
	return m_pImpl->IsPressed(static_cast<unsigned int>(button));
}
