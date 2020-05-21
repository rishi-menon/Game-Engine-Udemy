
#include "pch.h"
#include "CollisionInfo.h"
#include "Entity/Entity.h"

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
               colliderA->GetEntityOwner()->OnCollision(colliderB);
               colliderB->GetEntityOwner()->OnCollision(colliderA);
            }
            else if (curFrame && !lastFrame)
            {
               //Collision Start
               colliderA->GetEntityOwner()->OnCollisionEnter(colliderB);
               colliderB->GetEntityOwner()->OnCollisionEnter(colliderA);
            }
            else if (!curFrame && lastFrame)
            {
               colliderA->GetEntityOwner()->OnCollisionExit(colliderB);
               colliderB->GetEntityOwner()->OnCollisionExit(colliderA);
            }
         }
      }
   }
}