#pragma once
#include "BaseComponent.h"

class PlayerUIComponent final : public BaseComponent
{
public:
	PlayerUIComponent(dae::GameObject* pOwner);

	PlayerUIComponent(const PlayerUIComponent& other) = delete;
	PlayerUIComponent(PlayerUIComponent&& other) = delete;
	PlayerUIComponent& operator=(const PlayerUIComponent& other) = delete;
	PlayerUIComponent& operator=(PlayerUIComponent&& other) = delete;

	void SetCounters(int countBomb, int countFire, int countSpeed, bool hasRemote);
	void AttachTheCounters(std::shared_ptr<dae::GameObject> bombCount, std::shared_ptr<dae::GameObject> fireCount, std::shared_ptr<dae::GameObject> speedCount, std::shared_ptr<dae::GameObject> remoteCount);

private:
	std::shared_ptr<dae::GameObject> m_pBombItemCount;
	std::shared_ptr<dae::GameObject> m_pFireItemCount;
	std::shared_ptr<dae::GameObject> m_pSpeedItemCount;
	std::shared_ptr<dae::GameObject> m_pRemoteItemCount;


};

