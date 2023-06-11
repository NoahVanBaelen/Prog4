#pragma once
#include "Observer.h"
class BombObserver final : public Observer
{
public:
	BombObserver(dae::GameObject* observer);
	void Notify(Event event, dae::GameObject* notifyer) override;
private:
	dae::GameObject* m_Observer;
};

