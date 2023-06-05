#pragma once
#include "GameObject.h"
class Observer
{
public:
	enum class Event
	{
		SCORE_CHANGE,
		LIVE_CHANGE,
		MOVE_LEFT,
		MOVE_RIGHT,
		MOVE_UP,
		MOVE_DOWN,
		MOVE_STANDSTILL
	};

	Observer() = default;
	virtual ~Observer() = default;
	Observer(const Observer& other) = delete;
	Observer(Observer&& other) = delete;
	Observer& operator=(const Observer& other) = delete;
	Observer& operator=(Observer&& other) = delete;

	virtual void Notify(Event event, dae::GameObject* notifyer) = 0;
};

