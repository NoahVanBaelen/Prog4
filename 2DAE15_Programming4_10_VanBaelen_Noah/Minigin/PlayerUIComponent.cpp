#include "PlayerUIComponent.h"
#include "TextComponent.h"

PlayerUIComponent::PlayerUIComponent(dae::GameObject* pOwner)
	:BaseComponent(pOwner)
{
}

void PlayerUIComponent::SetCounters(int countBomb, int countFire, int countSpeed, bool hasRemote)
{
	m_pBombItemCount->GetComponent<TextComponent>()->SetText(std::to_string(countBomb));
	m_pFireItemCount->GetComponent<TextComponent>()->SetText(std::to_string(countFire));
	m_pSpeedItemCount->GetComponent<TextComponent>()->SetText(std::to_string(countSpeed));
	m_pRemoteItemCount->GetComponent<TextComponent>()->SetText("0");
	if (hasRemote)
	{
		m_pRemoteItemCount->GetComponent<TextComponent>()->SetText("1");
	}
}

void PlayerUIComponent::AttachTheCounters(std::shared_ptr<dae::GameObject> bombCount, std::shared_ptr<dae::GameObject> fireCount, std::shared_ptr<dae::GameObject> speedCount, std::shared_ptr<dae::GameObject> remoteCount)
{
	int bombStartValue{ 1 };
	int fireStartValue{ 1 };
	int speedStartValue{};
	int remoteStartValue{};

	m_pBombItemCount = bombCount;
	m_pFireItemCount = fireCount;
	m_pSpeedItemCount = speedCount;
	m_pRemoteItemCount = remoteCount;

	m_pBombItemCount->GetComponent<TextComponent>()->SetText(std::to_string(bombStartValue));
	m_pFireItemCount->GetComponent<TextComponent>()->SetText(std::to_string(fireStartValue));
	m_pSpeedItemCount->GetComponent<TextComponent>()->SetText(std::to_string(speedStartValue));
	m_pRemoteItemCount->GetComponent<TextComponent>()->SetText(std::to_string(remoteStartValue));
}
