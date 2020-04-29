#include "EntityManager.h"
#include "Log/Log.h"
#include <sstream>

EntityManager::EntityManager()
{
   //reserve storage for 100 entities
   m_vEntities.reserve(100);
}
EntityManager::~EntityManager()
{
   for (std::vector<Entity*>::iterator it = m_vEntities.begin();
      it != m_vEntities.end(); it++)
   {
      ASSERT(*it);
      delete (*it);
   }
   m_vEntities.clear();
}

EntityManager& EntityManager::operator = (EntityManager&& other)
{
   m_vEntities = std::move(other.m_vEntities);
   return (*this);
}

void EntityManager::OnUpdate(double deltaTime)
{
   std::vector<Entity*>::iterator it = m_vEntities.begin();

   for (; it != m_vEntities.end(); it++)
   {
      ASSERT(*it);
      (*it)->OnUpdate(deltaTime);
   }
}
void EntityManager::OnRender()
{
   std::vector<Entity*>::iterator it = m_vEntities.begin();

   for (; it != m_vEntities.end(); it++)
   {
      ASSERT(*it);
      (*it)->OnRender();
   }
}

void EntityManager::OnDestroy()
{
   std::vector<Entity*>::iterator it = m_vEntities.begin();

   for (; it != m_vEntities.end(); it++)
   {
      ASSERT(*it);
      (*it)->OnDestroy();
   }
}
Entity& EntityManager::AddEntity(const std::string& strName /*= ""*/)
{
   Entity* pEntity = new Entity(*this, strName);
   ASSERT(pEntity);
   m_vEntities.emplace_back(pEntity);
   return *pEntity;
}

#ifdef DEBUG
void EntityManager::LogAllEntities ()
{
   //To do: add this function maybe ? or cleanup
}
#endif