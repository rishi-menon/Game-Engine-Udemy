#pragma once
#include "Rect.h"
#include <glm/glm.hpp>

class BoxColliderComponent;
class EntityManager;

namespace Engine::CollisionHelper
{
   extern bool CheckCollisionRectPoint(const Engine::Rect& rect, float x, float y);
   extern bool CheckCollisionRectPoint(const Engine::Rect& rect, const glm::vec2& point);

   extern bool CheckCollisionRectRect(const Engine::Rect& rectA, const Engine::Rect& rectB);

   extern void CheckAllCollisionBoxCollider(const BoxColliderComponent& collider, const EntityManager& manager, std::list<BoxColliderComponent*>& outListColliders);
}