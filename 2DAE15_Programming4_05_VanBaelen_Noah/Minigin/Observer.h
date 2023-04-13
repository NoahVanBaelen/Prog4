#pragma once
#include "GameObject.h"
class Observer
{
public:
	enum class Event
	{
		SCORE_CHANGE,
		LIVE_CHANGE
	};

	Observer() = default;
	virtual ~Observer() = default;
	Observer(const Observer& other) = delete;
	Observer(Observer&& other) = delete;
	Observer& operator=(const Observer& other) = delete;
	Observer& operator=(Observer&& other) = delete;

	virtual void Notify(Event event, dae::GameObject* notifyer) = 0;
};

