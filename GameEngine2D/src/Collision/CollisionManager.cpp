#include "pch.h"
#include "Component/BoxColliderComponent.h"
#include "Entity/Entity.h"
#include "CollisionHelper.h"

//////////////////////////////////////////////////////////////
//                   Helper Classes                         //
//////////////////////////////////////////////////////////////
namespace
{

   struct CollisionInfo
   {
      bool bCollisionPrevFrame;//This is false initially
      bool bCollisionCurrFrame;

      CollisionInfo() : bCollisionCurrFrame(false), bCollisionPrevFrame(false) {}
      CollisionInfo(bool prevFrame, bool curFrame) : bCollisionPrevFrame(prevFrame), bCollisionCurrFrame(curFrame) {}

      void Update(bool bCollisionCur)
      {
         bCollisionPrevFrame = bCollisionCurrFrame;
         bCollisionCurrFrame = bCollisionCur;
      }
   };

   ///////////////////////////////////////////////////////////////
   //                Collision Info Manager                     //
   //This class internally stores all the collisions that took place
   class CollisionInfoManager
   {
      std::unordered_map<BoxColliderComponent*, std::unordered_map<BoxColliderComponent*, CollisionInfo>> m_mapCollisions;

      //m_size stores the number of collisionInfo that are "inactive" ie the collision took place more than 1 frame back (so it is essentially useless as OnCollisionStart or end will not be called)... If the misses are bigger than this number then recalculate the map and only store the useful ones instead of wasting memory
      std::size_t m_size;
      const std::size_t m_maxSize = 1000; 


      //The colliders are stored in a map of maps. Instead of having 2 entries in the map for the same collision (Eg obj A is the first key and obj B is the second key and vice versa), Use this function to get the First index and the second index regardless of order (And it is only stored once in the map of maps)
      inline BoxColliderComponent* GetFirst(BoxColliderComponent* pColliderA, BoxColliderComponent* pColliderB)  const { return (pColliderA < pColliderB) ? pColliderA : pColliderB; };
      inline BoxColliderComponent* GetSecond(BoxColliderComponent* pColliderA, BoxColliderComponent* pColliderB) const { return (pColliderA < pColliderB) ? pColliderB : pColliderA; };

      void Remap();

   public:
      CollisionInfo* AddCollision(BoxColliderComponent* pColliderA, BoxColliderComponent* pColliderB);
      CollisionInfo* GetCollisionInfo(BoxColliderComponent* pColliderA, BoxColliderComponent* pColliderB);
      void UpdateAllCollisionsInfo();
      void CheckAndDoRemap()
      {
         if (m_size > m_maxSize)
         {
            Remap();
         }
      }
      void SendOnCollisionEvents();
   };

   CollisionInfo* CollisionInfoManager::AddCollision(BoxColliderComponent* pColliderA, BoxColliderComponent* pColliderB)
   {
      std::unordered_map<BoxColliderComponent*, std::unordered_map<BoxColliderComponent*, CollisionInfo>>::iterator itOuter = m_mapCollisions.find(GetFirst(pColliderA, pColliderB));
      if (itOuter == m_mapCollisions.end())
      {
         //create the map
         std::unordered_map<BoxColliderComponent*, CollisionInfo> map;
         map.emplace(GetSecond(pColliderA, pColliderB), CollisionInfo{ false, false });
         
         const auto& pairInsert = m_mapCollisions.emplace(GetFirst(pColliderA, pColliderB), std::move(map));
         ASSERT(pairInsert.second);

         //.first returns an iterator to the inserted element and -> second returns the map
         auto itInsertedElement = pairInsert.first->second.find(GetSecond(pColliderA, pColliderB));
         ASSERT(itInsertedElement != pairInsert.first->second.end());

         return &(itInsertedElement->second); 
      }
      else
      {
         std::unordered_map<BoxColliderComponent*, CollisionInfo>& mapInner = itOuter->second;
         std::unordered_map<BoxColliderComponent*, CollisionInfo>::iterator itInner = mapInner.find(GetSecond(pColliderA, pColliderB));
         
         ASSERT(itInner == mapInner.end());  //If this fails then the collision type already exists and hence the Add function should not have been called (the way things are set up currently)
         if (itInner == mapInner.end())
         {
            const auto& pairInsert = mapInner.emplace(GetSecond(pColliderA, pColliderB), CollisionInfo{ false, false });
            ASSERT(pairInsert.second);
            return &(pairInsert.first->second); //.first returns an iterator to the inserted element and -> second returns the Collisioninfo in the iterator.
         }
      }
      return nullptr;
   }

   CollisionInfo* CollisionInfoManager::GetCollisionInfo(BoxColliderComponent* pColliderA, BoxColliderComponent* pColliderB)
   {
      std::unordered_map<BoxColliderComponent*, std::unordered_map<BoxColliderComponent*, CollisionInfo>>::iterator itOuter = m_mapCollisions.find(GetFirst(pColliderA, pColliderB));

      if (itOuter != m_mapCollisions.end())
      {
         std::unordered_map<BoxColliderComponent*, CollisionInfo>::iterator it = itOuter->second.find(GetSecond(pColliderA, pColliderB));
         if (it != itOuter->second.end())
         {
            return &(it->second);
         }
      }
      return nullptr;
   }

   void CollisionInfoManager::UpdateAllCollisionsInfo()
   {
      m_size = 0;
      for (auto& map : m_mapCollisions)
      {
         for (auto& collisionInfo : map.second)
         {
            //This check might not be necessary
            if (collisionInfo.second.bCollisionCurrFrame || collisionInfo.second.bCollisionPrevFrame)
            {
               collisionInfo.second.Update(false);
            }
            else
            {
               m_size++;
            }
         }
      }
   }

   void CollisionInfoManager::Remap()
   {
      std::unordered_map<BoxColliderComponent*, std::unordered_map<BoxColliderComponent*, CollisionInfo>> mapCopy;
      for (auto& map : m_mapCollisions)
      {
         for (auto& collisionInfo : map.second)
         {
            //This check might not be necessary
            if (collisionInfo.second.bCollisionCurrFrame || collisionInfo.second.bCollisionPrevFrame)
            {
               //This is a useful collisionInfo so store it in the copy map
               std::unordered_map<BoxColliderComponent*, CollisionInfo> mapInner;
               mapInner.emplace(collisionInfo.first, collisionInfo.second);
               mapCopy.emplace(map.first, std::move(mapInner));
               int deleteLater = 1;
            }
         }
      }

      m_mapCollisions = std::move(mapCopy);
   }

   void CollisionInfoManager::SendOnCollisionEvents()
   {
      for (auto& pairMap : m_mapCollisions)
      {
         BoxColliderComponent* colliderA = pairMap.first;
         ASSERT(colliderA);
         for (auto& pairInfo : pairMap.second)
         {
            BoxColliderComponent* colliderB = pairInfo.first;
            ASSERT(colliderB);
            bool lastFrame = pairInfo.second.bCollisionPrevFrame;
            bool curFrame = pairInfo.second.bCollisionCurrFrame;
            if (curFrame || lastFrame)
            {
               if (curFrame && lastFrame)
               {
                  //Collision continue
                  colliderA->GetEntityOwner()->OnCollision(*colliderB);
                  colliderB->GetEntityOwner()->OnCollision(*colliderA);
               }
               else if (curFrame && !lastFrame)
               {
                  //Collision Start
                  colliderA->GetEntityOwner()->OnCollisionEnter(*colliderB);
                  colliderB->GetEntityOwner()->OnCollisionEnter(*colliderA);
               }
               else if (!curFrame && lastFrame)
               {
                  colliderA->GetEntityOwner()->OnCollisionExit(*colliderB);
                  colliderB->GetEntityOwner()->OnCollisionExit(*colliderA);
               }
            }
         }
      }
   }

   static std::unordered_map<BoxColliderComponent*, bool> umapCollidersToCheck(1000);   //reserve place for 1000 colliders
   static CollisionInfoManager collisionsManager;

}



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

}