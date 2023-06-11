#pragma once
#include "GameObject.h"
class Observer
{
public:
	enum class Event
	{
		SCORE_CHANGE,
		LIVE_CHANGE,
		BOMB_EXPLODED,
		REMOTE,
		ENEMY_DIES,
		END_OF_LEVEL,
		RELOAD_LEVEL,
		START_GAME,
		SETUP_GRID_FOR_START,
		CHANGE_IN_PLAYER_STATS,
		PLAYER_DIES,
		PLAYER_RESET_LIVES,
		GAME_OVER,
		END_OF_GAME
	};

	Observer() = default;
	virtual ~Observer() = default;
	Observer(const Observer& other) = delete;
	Observer(Observer&& other) = delete;
	Observer& operator=(const Observer& other) = delete;
	Observer& operator=(Observer&& other) = delete;

	virtual void Notify(Event event, dae::GameObject* notifyer) = 0;
};

