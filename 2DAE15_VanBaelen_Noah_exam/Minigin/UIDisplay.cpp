#include "UIDisplay.h"
#include "TextComponent.h"
#include "ScoreComponent.h"
#include "LiveComponent.h"

UIDisplay::UIDisplay(dae::GameObject* UIElement)
	:m_UIElement{UIElement}
{}

void UIDisplay::Notify(Event event, dae::GameObject* notifyer)
{
	switch (event)
	{
	case Observer::Event::SCORE_CHANGE:
		m_UIElement->GetComponent<TextComponent>()->SetText("Points: " + std::to_string(notifyer->GetComponent<ScoreComponent>()->GetScore()));
		break;
	case Observer::Event::LIVE_CHANGE:
		m_UIElement->GetComponent<TextComponent>()->SetText("Lives: " + std::to_string(notifyer->GetComponent<LiveComponent>()->GetLives()));
		break;
	default:
		break;
	}
}
