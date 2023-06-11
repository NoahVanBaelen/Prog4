#include "NVB_Collision_System.h"
#include "CollisionComponent.h"
#include <algorithm>

void NVB_Collision_System::AddCollisionBox(CollisionComponent* collisionBox)
{
    m_pAllCollisionBoxes.push_back(collisionBox);
}

std::pair<int,int> NVB_Collision_System::HasCollision(CollisionComponent* collisionBox)
{
    CollisionBox ourCollisionBox = collisionBox->GetCollisionBox();
    std::vector<CollisionBox> validBoxes{};
    for (CollisionComponent* component : m_pAllCollisionBoxes)
    {
        CollisionBox box = component->GetCollisionBox();
        if (box.pOwner != ourCollisionBox.pOwner)//make sure we dont add Collisionboxes that are owned by the same gameobject
        {
            for (int i = 0; i < static_cast<int>(ourCollisionBox.groupIdToCollideWith.size()); i++) //go through all boxes and add the only ones we can collide with
            {
                if (box.collisionGroupID == ourCollisionBox.groupIdToCollideWith[i])
                {
                    validBoxes.push_back(box);
                }
            }
        }
    }

    for (CollisionBox box : validBoxes)
    {
        if (AreBoxesOverlapping(ourCollisionBox,box))
        {
            return CalculateOffset(ourCollisionBox, box);
        }
    }

    std::pair<int, int> offset{ 0,0 };
    return offset;
}

std::pair<bool, dae::GameObject*> NVB_Collision_System::HasTrigger(const CollisionBox& ourCollisionBox)
{
    std::vector<CollisionBox> validBoxes{};

    for (CollisionComponent* component : m_pAllCollisionBoxes)
    {
        CollisionBox box = component->GetCollisionBox();
        for (int j = 0; j < static_cast<int>(ourCollisionBox.groupIdToCollideWith.size()); j++) //go through all boxes and add the only ones we can trigger with
        {
            if (box.collisionGroupID == ourCollisionBox.groupIdToCollideWith[j])
            {
                validBoxes.push_back(box);
            }
        }
    }

    std::pair<bool, dae::GameObject*> returnValue{false,nullptr};
    for (CollisionBox box : validBoxes)
    {
        if (AreBoxesOverlapping(ourCollisionBox, box))
        {
            returnValue.first = true;
            returnValue.second = box.pOwner;
            return returnValue;
        }
    }

    return returnValue;
}

std::pair<bool, dae::GameObject*> NVB_Collision_System::RayCast(glm::vec2 rayStart, glm::vec2 rayEnd, std::vector<int> groupIDsToCollideWith)
{
    std::vector<CollisionBox> validBoxes{};
    for (CollisionComponent* component : m_pAllCollisionBoxes)
    {
        CollisionBox box = component->GetCollisionBox();
        for (int i = 0; i < static_cast<int>(groupIDsToCollideWith.size()); i++) //go through all boxes and add the only ones we can trigger with
        {
            if (box.collisionGroupID == groupIDsToCollideWith[i])
            {
                validBoxes.push_back(box);
            }
        }
    }

    std::sort(validBoxes.begin(), validBoxes.end(), [&](const CollisionBox& box1, const CollisionBox& box2) {
        return CompareBoxesByDistance(box1, box2, rayStart);
        });

    std::pair<bool, dae::GameObject*> returnValue{ false,nullptr };
    for (CollisionBox box : validBoxes)
    {
        if (IsLineAndBoxOverlapping(rayStart, rayEnd, box))
        {
            returnValue.first = true;
            returnValue.second = box.pOwner;
            return returnValue;
        }
    }

    return returnValue;
}

bool NVB_Collision_System::AreBoxesOverlapping(const CollisionBox& box1, const CollisionBox& box2)
{
    int left1 = static_cast<int>(box1.centerPosition.x) - box1.widthBox / 2;
    int right1 = static_cast<int>(box1.centerPosition.x) + box1.widthBox / 2;
    int top1 = static_cast<int>(box1.centerPosition.y) - box1.heightBox / 2;
    int bottom1 = static_cast<int>(box1.centerPosition.y) + box1.heightBox / 2;

    int left2{};
    int right2{};
    int top2{};
    int bottom2{};
    if (box2.isStatic)
    {
        left2 = box2.left;
        right2 = box2.right;
        top2 = box2.top;
        bottom2 = box2.bottom;
    }
    else
    {
        left2 = static_cast<int>(box2.centerPosition.x) - box2.widthBox / 2;
        right2 = static_cast<int>(box2.centerPosition.x) + box2.widthBox / 2;
        top2 = static_cast<int>(box2.centerPosition.y) - box2.heightBox / 2;
        bottom2 = static_cast<int>(box2.centerPosition.y) + box2.heightBox / 2;
    }

    if (left1 <= right2 && right1 >= left2 && top1 <= bottom2 && bottom1 >= top2) 
    {
        return true;
    }

    return false;
}

bool NVB_Collision_System::IsLineAndBoxOverlapping(const glm::vec2& start, const glm::vec2& end, const CollisionBox& box)
{
    int minX{};
    int maxX{};
    int minY{};
    int maxY{};

    if (box.isStatic)
    {
        minX = box.left;
        maxX = box.right;
        minY = box.bottom;
        maxY = box.top;
    }
    else
    {
        minX = static_cast<int>(box.centerPosition.x - (box.widthBox / 2.0f));
        maxX = static_cast<int>(box.centerPosition.x + (box.widthBox / 2.0f));
        minY = static_cast<int>(box.centerPosition.y - (box.heightBox / 2.0f));
        maxY = static_cast<int>(box.centerPosition.y + (box.heightBox / 2.0f));
    }

    glm::vec2 leftBottomPoint{ minX,maxY };
    glm::vec2 leftTopPoint{ minX,minY };
    glm::vec2 rightBottomPoint{ maxX,maxY };
    glm::vec2 rightTopPoint{ maxX,minY };

    if ((start.x > maxX && end.x > maxX) || (start.x < minX && end.x < minX) ||
        (start.y < maxY && end.y < maxY) || (start.y > minY && end.y > minY))
    {
        return false;
    }
   
    if ((start.x > maxX || end.x > maxX) || (start.x < minX || end.x < minX) ||
        (start.y < maxY || end.y < maxY) || (start.y > minY || end.y > minY))
    {
        return true;
    }

    return false;
}

std::pair<int, int> NVB_Collision_System::CalculateOffset(const CollisionBox& box1, const CollisionBox& box2)
{
    std::pair<int, int>offset{};

    int left1 = static_cast<int>(box1.centerPosition.x) - box1.widthBox / 2;
    int right1 = static_cast<int>(box1.centerPosition.x) + box1.widthBox / 2;
    int top1 = static_cast<int>(box1.centerPosition.y) - box1.heightBox / 2;
    int bottom1 = static_cast<int>(box1.centerPosition.y) + box1.heightBox / 2;

    int left2{};
    int right2{};
    int top2{};
    int bottom2{};
    if (box2.isStatic)
    {
        left2 = box2.left;
        right2 = box2.right;
        top2 = box2.top;
        bottom2 = box2.bottom;
    }
    else
    {
        left2 = static_cast<int>(box2.centerPosition.x) - box2.widthBox / 2;
        right2 = static_cast<int>(box2.centerPosition.x) + box2.widthBox / 2;
        top2 = static_cast<int>(box2.centerPosition.y) - box2.heightBox / 2;
        bottom2 = static_cast<int>(box2.centerPosition.y) + box2.heightBox / 2;
    }

    offset.first = std::min(right1, right2) - std::max(left1, left2);
    offset.second = std::min(bottom1, bottom2) - std::max(top1, top2);

    if (box1.centerPosition.x <= box2.centerPosition.x)
    {
        offset.second *= -1;
    }

    if (box1.centerPosition.y <= box2.centerPosition.y)
    {
        offset.first *= -1;
    }

    return offset;
}

bool NVB_Collision_System::CompareBoxesByDistance(const CollisionBox& box1, const CollisionBox& box2, const glm::vec2& rayStart)
{
    float distance1 = glm::distance(rayStart, box1.centerPosition);
    float distance2 = glm::distance(rayStart, box2.centerPosition);
    return distance1 < distance2;
}

void NVB_Collision_System::RemoveCollisionBox(CollisionComponent* collisionBox)
{
    m_pAllCollisionBoxes.erase(std::remove(m_pAllCollisionBoxes.begin(), m_pAllCollisionBoxes.end(), collisionBox), m_pAllCollisionBoxes.end());
}

void NVB_Collision_System::SetUpComleteMessage()
{
    std::cout << "Setup NVB_Collision_System Complete\n";
}
