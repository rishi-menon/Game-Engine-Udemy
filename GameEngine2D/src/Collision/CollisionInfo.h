#pragma once
#include <unordered_map>
#include <unordered_set>
#include "Component/BoxColliderComponent.h"

//////////////////////////////////////////////////////////////
//                   Helper Classes                         //
//////////////////////////////////////////////////////////////

class CollisionInfoManager;
extern std::unordered_map<BoxColliderComponent*, bool> umapCollidersToCheck;
extern CollisionInfoManager collisionsManager;
extern std::unordered_set<BoxColliderComponent*> usetDeletedColldiers;

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

   void Remap();

public:

   //The colliders are stored in a map of maps. Instead of having 2 entries in the map for the same collision (Eg obj A is the first key and obj B is the second key and vice versa), Use this function to get the First index and the second index regardless of order (And it is only stored once in the map of maps)
   static inline BoxColliderComponent* GetFirst(BoxColliderComponent* pColliderA, BoxColliderComponent* pColliderB)  { return (pColliderA < pColliderB) ? pColliderA : pColliderB; };
   static inline BoxColliderComponent* GetSecond(BoxColliderComponent* pColliderA, BoxColliderComponent* pColliderB)  { return (pColliderA < pColliderB) ? pColliderB : pColliderA; };



   std::unordered_map<BoxColliderComponent*, std::unordered_map<BoxColliderComponent*, CollisionInfo>>& GetCollisionsMap() { return m_mapCollisions; }

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
