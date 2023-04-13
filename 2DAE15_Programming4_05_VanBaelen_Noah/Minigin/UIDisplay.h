#pragma once
#include "Observer.h"
class UIDisplay final : public Observer
{
public:
	UIDisplay(dae::GameObject* UIElement);
	void Notify(Event event, dae::GameObject* notifyer) override;
private:
	dae::GameObject* m_UIElement;
};

