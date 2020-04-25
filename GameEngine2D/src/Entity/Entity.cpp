
#include "Entity.h"
#include "Log/Log.h"

Entity::Entity(EntityManager& manager, const std::string& strName /*= ""*/) :
   m_entityManager (manager),
   m_bIsActive (true),
   m_strName (strName)
{
   m_vComponents.reserve(10);   //reserve storage for 10 components to prevent constant allocation of memory
}
Entity::~Entity()
{
   for (std::vector<Component*>::iterator it = m_vComponents.begin();
      it != m_vComponents.end(); it++)
   {
      ASSERT(*it);
      delete (*it);
   }
   m_vComponents.clear();
   m_umapComponentType.clear();
}

void Entity::OnUpdate(double deltaTime)
{
   std::vector<Component*>::iterator itEntities = m_vComponents.begin();

   for (; itEntities != m_vComponents.end(); itEntities++)
   {
      ASSERT(*itEntities);
      (*itEntities)->OnUpdate(deltaTime);
   }
}
void Entity::OnRender()
{
   std::vector<Component*>::iterator itEntities = m_vComponents.begin();
   for (; itEntities != m_vComponents.end(); itEntities++)
   {
      ASSERT(*itEntities);
      (*itEntities)->OnRender();
   }
}

void Entity::OnDestroy()
{
   std::vector<Component*>::iterator itEntities = m_vComponents.begin();
   for (; itEntities != m_vComponents.end(); itEntities++)
   {
      ASSERT(*itEntities);
      (*itEntities)->OnDestroy();
   }

   m_bIsActive = false;
}