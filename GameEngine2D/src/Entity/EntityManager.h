#pragma once

#include "Entity.h"

#ifdef DEBUG
#define LOG_ALL_ENTITIES(obj) (obj).LogAllEntities()
#else
#define LOG_ALL_ENTITIES (obj) 
#endif // DeBUG


class EntityManager
{
public:
   EntityManager();
   ~EntityManager();

   void OnUpdate(double deltaTime);
   void OnRender();

   void OnDestroy();
   Entity& AddEntity(const std::string& strName = "");

   inline std::size_t GetCount() const { return m_vEntities.size(); }

   inline bool IsEmpty() const { return GetCount() == 0; }

   inline std::vector<Entity*>& GetEntitiesVector() { return m_vEntities; }
   


#ifdef DEBUG
   void LogAllEntities();
#endif // DEBUG

private:
   std::vector<Entity*> m_vEntities;

};