#pragma once
#include "Observer.h"
class PlayerObserver final : public Observer
{
public:
	PlayerObserver(dae::GameObject* observer);
	void Notify(Event event, dae::GameObject* notifyer) override;
private:
	dae::GameObject* m_Observer;
	int m_MaxPlayer{ 2 };
};

