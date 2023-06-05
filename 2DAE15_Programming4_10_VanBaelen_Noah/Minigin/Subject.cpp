#include "Subject.h"

void Subject::AddObserver(Observer* observer)
{
	m_Observers.emplace_back(observer);
}

void Subject::RemoveObserver(Observer* observerToRemove)
{

	for (size_t i = 0; i < m_Observers.size(); i++)
	{
		if (observerToRemove == m_Observers[i].get())
		{
			m_Observers.erase(m_Observers.begin() + i);
		}
	}
}

void Subject::NotifyObservers(Observer::Event event, dae::GameObject* notifyer)
{
	for (std::shared_ptr<Observer> observer : m_Observers)
	{
		observer->Notify(event, notifyer);
	}
}
