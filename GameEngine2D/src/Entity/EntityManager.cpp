
#include "pch.h"
#include "EntityManager.h"
#include "Collision/CollisionManager.h"

EntityManager::EntityManager()
{
}
EntityManager::~EntityManager()
{
   
   for (Entity* pEntity : m_listEntities)
   {
      ASSERT(pEntity);
      delete (pEntity);
   }
   m_listEntities.clear();
   m_listEntitiesToDelete.clear();
}

EntityManager& EntityManager::operator = (EntityManager&& other)
{
   m_listEntities = std::move(other.m_listEntities);
   m_listEntitiesToDelete = std::move(other.m_listEntitiesToDelete);
   return (*this);
}

void EntityManager::OnUpdate(double deltaTime)
{
   for (Entity* pEntity : m_listEntities)
   {
      ASSERT(pEntity);
      if (pEntity->GetIsActive())
      {
         pEntity->OnUpdate(deltaTime);
      }
   }
}
void EntityManager::OnRender()
{
   for (Entity* pEntity : m_listEntities)
   {
      ASSERT(pEntity);
      if (pEntity->GetIsActive())
      {
         pEntity->OnRender();
      }
   }
}

//void EntityManager::OnDestroy()
//{
//   std::vector<Entity*>::iterator it = m_vEntities.begin();
//
//   for (; it != m_vEntities.end(); it++)
//   {
//      ASSERT(*it);
//      //Only call ondestroy if the entity is enabled or not ?
//      (*it)->OnDestroy();
//   }
//}
Entity* EntityManager::AddEntity(const std::string& strName /*= ""*/)
{
   Entity* pEntity = new Entity(this, strName);
   AddEntity(pEntity);
   return pEntity;
}

void EntityManager::AddEntity(Entity* pEntity)
{
   ASSERT(pEntity);
   if (pEntity)
   {
      m_listEntities.push_back(pEntity);
   }
}


//liftime of 0.0 means that the object does not get automatically destroyed
Entity* EntityManager::Instantiate(Entity* pEntity, double dLifetime)   //lifetime is in seconds
{
   ASSERT(pEntity);
   if (!pEntity)  return nullptr;

   Entity* pNewEntity = AddEntity(pEntity->GetName());

   for (const auto& pair : pEntity->GetComponentsMap())
   {
      const Components& components = pair.second;
      for (Component* pComponent : components)
      {
         ASSERT(pComponent);
         if (pComponent->CopyDuringInstantiate())
         {
            pNewEntity->CopyComponent(pComponent);
         }
      }
   }

   //safer to check if the number is bigger than this value instead of checking if lifeTime != 0
   if (dLifetime > 1.0e-5)
   {
      pNewEntity->AddComponent<SelfDestructComponent>(dLifetime);
   }
   else
   {
      ASSERT(false);
      //delete later
   }
   
   pNewEntity->OnInitialise();
   return pNewEntity;
}

Entity* EntityManager::GetEntityFromName(const std::string& strName) const
{
   for (Entity* pEntity : m_listEntities)
   {
      if (pEntity->GetName() == strName)
      {
         return pEntity;
      }
   }
   return nullptr;
}

void EntityManager::DeleteEntities()
{
   if (m_listEntitiesToDelete.empty ()) return;
   
   std::unordered_set<Entity*> setDeleted;
   for (Entity* pEntity : m_listEntitiesToDelete)
   {
      if (setDeleted.find(pEntity) == setDeleted.end())
      {
         m_listEntities.remove(pEntity);

         setDeleted.emplace(pEntity);  //for safety... so that the same entity is not deleted twice
         delete pEntity;
      }
      else
      {
         ASSERT(false);
      }
   }
   m_listEntitiesToDelete.clear();
   setDeleted.clear();
}
void EntityManager::DestroyEntity(Entity* const pEntity)
{
   ASSERT(pEntity);
   if (!pEntity)  return;
   
   //Add this entity to the delete list... After All updates and all renders, the entities in this list are deleted... This is done because the OnUpdate function of SelfDestruct Component calls this function... The for loop that calls all the OnUpdate functions of all components might not be over and hence if the entity is deleted then the program will crash

   m_listEntitiesToDelete.push_back(pEntity);

   const Components* pColliderComponents;
   pEntity->GetComponents<BoxColliderComponent>(pColliderComponents);
   ASSERT(pColliderComponents);
   for (Component* pComp : (*pColliderComponents))
   {
     Engine::CollisionManager::DeleteFromCollisionList(static_cast<BoxColliderComponent*>(pComp));
   }
   
#ifdef DEBUG
   //check if pEntity actually belongs to this manager... Ideally it should always belong in the list and if it doesnt then it would be easy to catch it and trace it here instead of in DeleteEntities function (which gets called at the end of the game loop)

   auto& it = std::find(m_listEntities.begin(), m_listEntities.end(), pEntity);
   ASSERT(it != m_listEntities.end());
#endif // DEBUG
}