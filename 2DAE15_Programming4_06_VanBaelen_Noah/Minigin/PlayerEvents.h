#pragma once
#include "Observer.h"
class PlayerEvents final : public Observer
{
public:
	PlayerEvents(dae::GameObject* player);
	void Notify(Event event, dae::GameObject* notifyer) override;
private:
	dae::GameObject* m_Player;
};

