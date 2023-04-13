#pragma once
#include "Observer.h"
#include "CSteamAchievements.h"
class Achievements final : public Observer
{
public:
	Achievements(CSteamAchievements* SteamAchievements);
	void Notify(Event event, dae::GameObject* notifyer) override;
private:
	CSteamAchievements* m_SteamAchievements;
};

