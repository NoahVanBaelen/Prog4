#pragma once
#include <memory>
#include <vector>
#include "Observer.h"
class Subject final
{
public:
    Subject() = default;
    ~Subject() = default;
    void AddObserver(Observer* observer);
    void RemoveObserver(Observer* observerToRemove);
    void NotifyObservers(Observer::Event event, dae::GameObject* notifyer);
private:
    std::vector<std::shared_ptr<Observer>> m_Observers;
};

