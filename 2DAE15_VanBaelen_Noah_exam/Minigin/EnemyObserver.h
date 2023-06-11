#pragma once
#include "Observer.h"
class EnemyObserver final : public Observer
{
public:
	EnemyObserver(dae::GameObject* observer);
	void Notify(Event event, dae::GameObject* notifyer) override;
private:
	dae::GameObject* m_Observer;
};

