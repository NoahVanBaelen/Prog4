#include "Logging_Collision_System.h"

void Logging_Collision_System::AddCollisionBox(CollisionComponent* collisionBox)
{
    _real_cs->AddCollisionBox(collisionBox);
    std::cout << "Added colission on object";
}

std::pair<int, int> Logging_Collision_System::HasCollision(CollisionComponent* ourCollisionBox)
{
    std::cout << "See if it collide with something";
    return  _real_cs->HasCollision(ourCollisionBox);
}

std::pair<bool, dae::GameObject*> Logging_Collision_System::HasTrigger(const CollisionBox& ourCollisionBox)
{
    std::cout << "See if it triggers something";
    return _real_cs->HasTrigger(ourCollisionBox);
}

void Logging_Collision_System::RemoveCollisionBox(CollisionComponent* collisionBox)
{
    _real_cs->RemoveCollisionBox(collisionBox);
    std::cout << "Removed colission on object";
}

void Logging_Collision_System::SetUpComleteMessage()
{
    _real_cs->SetUpComleteMessage();
}

std::pair<bool, dae::GameObject*> Logging_Collision_System::RayCast(glm::vec2 rayStart, glm::vec2 rayEnd, std::vector<int> groupIDsToCollideWith)
{
    return _real_cs->RayCast(rayStart,rayEnd, groupIDsToCollideWith);
}
