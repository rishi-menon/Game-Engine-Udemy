#include "pch.h"
#include "CollisionHelper.h"
#include "Component/BoxColliderComponent.h"
#include "Entity/EntityManager.h"

namespace Engine::CollisionHelper
{
   //////////////////////////////////////////////////////////////////////////
   //                         Rect and Point                               //
   //////////////////////////////////////////////////////////////////////////
   extern bool CheckCollisionRectPoint(const Engine::Rect& rect, float x, float y)
   {
      //To do: currently does not support rotated quads.
      return x >= rect.GetLeft() && x <= rect.GetRight() &&
             y >= rect.GetBottom() && y <= rect.GetTop();   //down is negative y axis and hence >= GetBottom
   }
   extern bool CheckCollisionRectPoint(const Engine::Rect& rect, const glm::vec2& point)
   {
      return CheckCollisionRectPoint(rect, point.x, point.y);
   }

   extern bool CheckCollisionRectRect(const Engine::Rect& rectA, const Engine::Rect& rectB)
   {
      return  !(rectA.GetRight() < rectB.GetLeft() ||
               rectB.GetRight() < rectA.GetLeft() ||
               rectA.GetTop() < rectB.GetBottom() ||
               rectB.GetTop() < rectA.GetBottom());
              
   }

   extern void CheckAllCollisionBoxCollider(const BoxColliderComponent& collider, const EntityManager& manager, std::list<BoxColliderComponent*>& outListColliders)
   {
      ASSERT(&collider);
      Engine::Rect rectCollider;
      collider.GetRect(rectCollider);

      const std::vector<Entity*>& vEntities = manager.GetEntitiesVector();
      for (Entity* entity : vEntities)
      {
         BoxColliderComponent* pColliderB = entity->GetComponent<BoxColliderComponent>();
         if (pColliderB && pColliderB != &collider)
         {
            if (CheckCollisionRectRect(rectCollider, pColliderB->GetRect()))
            {
               //Collision took place
               outListColliders.push_back(pColliderB);
            }
         }
      }
   }

}