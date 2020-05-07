#pragma once

#include  <vector>
class BoxColliderComponent;
class EntityManager;

namespace Engine::CollisionManager
{
   //This function adds the box collider to a list of gameobjects... At the end of every frame (not yet decided when but most probably at the end), all the gameobjects that were added to the list are evaluated and checked to see if it collides with anything. (Instead of checking it right away when it moves).
   extern void AddToCollisionList(BoxColliderComponent* pBoxCollider);

   extern void CheckCollisionsList(const std::vector<EntityManager*>& vEntityManagers);

   extern void DeleteFromCollisionList(BoxColliderComponent* pComp);

   extern void FreeDeletedEntitiesInMap();   //recalculates the map components and removes the dangling pointer BoxCollider components that were deleted

}