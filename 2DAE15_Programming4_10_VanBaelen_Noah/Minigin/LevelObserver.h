#pragma once
#include "Observer.h"

class LevelObserver final : public Observer
{
public:
	LevelObserver(dae::GameObject* observer);
	void Notify(Event event, dae::GameObject* notifyer) override;
private:
	dae::GameObject* m_Observer;
};

