#include "pch.h"
#include "Component/BoxColliderComponent.h"
#include "Entity/Entity.h"
#include "CollisionHelper.h"
#include "CollisionInfo.h"


static std::unordered_map<BoxColliderComponent*, bool> umapCollidersToCheck(1000);   //reserve place for 1000 colliders
static CollisionInfoManager collisionsManager;

static std::unordered_set<BoxColliderComponent*> usetDeletedColldiers;  //Stores the list of entities that were deleted

//////////////////////////////////////////////////////////////
//                   Public stuff                           //
//////////////////////////////////////////////////////////////
namespace Engine::CollisionManager
{
   //Add to list
   extern void AddToCollisionList(BoxColliderComponent* pBoxCollider)
   {
      std::unordered_map<BoxColliderComponent*, bool>::iterator it = umapCollidersToCheck.find(pBoxCollider);
      if (it == umapCollidersToCheck.end())
      {
         umapCollidersToCheck.emplace(pBoxCollider, true);
      }
   }

   extern void CheckCollisionsList(const std::vector<EntityManager*>& vEntityManagers)
   {
      //Update the previous collisions so that the collisionInfo for collisions that happened in the last frame get updated (the bCollisionLastframe in CollisionInfo gets set to the value of bCollisionCurrentFrame).... 
      //go through the list
      //if a collision took place then record it in the collisions map (both ways)
      //If the collision was a new one then call OnCollisionStart
      //if the collision was existing earleir then call OnCollision
      //Once the collision has ended call OnCollisionEnd

      collisionsManager.UpdateAllCollisionsInfo();

      for (auto& pair : umapCollidersToCheck)
      {
         if (!pair.second)
         {
            //pair.second is the bool
            continue;
         }
         BoxColliderComponent* pColliderA = pair.first;
         ASSERT(pColliderA);

         std::list<BoxColliderComponent*> listColliders;
         
         //You might have different entity managers... (Almost like different layers...) check for all collisions across all the layers
         for (EntityManager* pManager : vEntityManagers)
         {
            ASSERT(pManager);
            if (pManager)
            {
               Engine::CollisionHelper::CheckAllCollisionBoxCollider(*pColliderA, *pManager, listColliders);
            }
         }

         for (BoxColliderComponent* pColliderB : listColliders)
         { 
            CollisionInfo* pInfo = collisionsManager.GetCollisionInfo(pColliderA, pColliderB);
            if (!pInfo)
            {
               //Its a new collision
               pInfo = collisionsManager.AddCollision(pColliderA, pColliderB);
            }
            pInfo->bCollisionCurrFrame = true;
            
         }
      }
      umapCollidersToCheck.clear();

      collisionsManager.SendOnCollisionEvents();

      collisionsManager.CheckAndDoRemap();   //this will work only if UpdateAllCollisionsInfo is called because that function calculates the number of "misses" which this function uses
   }


   extern void DeleteFromCollisionList(BoxColliderComponent* pComp)
   {
      usetDeletedColldiers.emplace(pComp);
   }
   extern void FreeDeletedEntitiesInMap()
   {
      if (!usetDeletedColldiers.size())    return;     //No entities were deleted so no need to recalculate

      std::unordered_map<BoxColliderComponent*, std::unordered_map<BoxColliderComponent*, CollisionInfo>> mapCopy;
      std::unordered_map<BoxColliderComponent*, std::unordered_map<BoxColliderComponent*, CollisionInfo>>& mapMain = collisionsManager.GetCollisionsMap();

      for (auto& pairMap : mapMain)
      {
         BoxColliderComponent* pColliderA = pairMap.first;
         ASSERT(pColliderA);

         for (auto& pair : pairMap.second)
         {
            BoxColliderComponent* pColliderB = pair.first;
            ASSERT(pColliderB);
            if (usetDeletedColldiers.find(pColliderB) != usetDeletedColldiers.end() ||
                usetDeletedColldiers.find(pColliderA) != usetDeletedColldiers.end())
            {
               //this component is about to be destroyed... Call OnCollisionExit on both to inform them... Also, this is a dangling pointer so remove it from the map
               ASSERT(pColliderA->GetEntityOwner() && pColliderB->GetEntityOwner());
               pColliderA->GetEntityOwner()->OnCollisionExit(pColliderB);
               pColliderB->GetEntityOwner()->OnCollisionExit(pColliderA);
               continue;
            }

            BoxColliderComponent* pFirst = CollisionInfoManager::GetFirst(pColliderA, pColliderB);
            BoxColliderComponent* pSecond = CollisionInfoManager::GetSecond(pColliderA, pColliderB);

            std::unordered_map<BoxColliderComponent*, CollisionInfo> mapTemp;
            mapTemp.emplace(pSecond, pair.second);
            //This entity was not deleted so add it to the map
            mapCopy.emplace(pFirst, mapTemp);
         }
      }

      mapMain = std::move(mapCopy);
      usetDeletedColldiers.clear();
   }
}
