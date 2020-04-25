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
   LOG_LINE_BREAK();
   std::vector<Entity*>::iterator itEntity = m_vEntities.begin();
   int i = 1;
   for (; itEntity != m_vEntities.end(); itEntity++)
   {
      ASSERT(*itEntity);
      std::vector<Component*>& list = (*itEntity)->GetComponentsVector();
      std::vector<Component*>::iterator it = list.begin();

      std::stringstream ss;
      ss <<"Entity " << i << ": "<< (*itEntity)->GetName();
      i++;
      LOG(ss.str().c_str(), Log::Trace);
      int j = 1;
      for (; it != list.end(); it++)
      {
         ASSERT(*it);
         std::stringstream ssComponent;
         ssComponent << "\tComponent " << j <<": " << (*it)->GetName();
         j++;
         LOG(ssComponent.str().c_str(), Log::Trace);
      }
      LOG_LINE_BREAK();
   }

}
#endif