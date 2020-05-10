#pragma once

#include "Entity.h"

class EntityManager
{
public:
   EntityManager();
   ~EntityManager();

   void OnUpdate(double deltaTime);
   void OnRender();

   //void OnDestroy();
   Entity* AddEntity(const std::string& strName = "");
   void AddEntity(Entity* pEntity);
   Entity* Instantiate(Entity* pEntity, double dLifetime);

   inline std::size_t GetCount() const { return m_listEntities.size(); }

   inline bool IsEmpty() const { return GetCount() == 0; }

   //inline std::vector<Entity*>& GetEntitiesVector() { return m_vEntities; }
   //inline const std::vector<Entity*>& GetEntitiesVector() const { return m_vEntities; }


   inline std::list<Entity*>& GetEntitiesList() { return m_listEntities; }
   inline const std::list<Entity*>& GetEntitiesList() const { return m_listEntities; }
   
   EntityManager& operator = (EntityManager&& other);
   EntityManager& operator += (EntityManager&& other);

   //Find gameobject with name. If there are multiple then it just returns the first match... To do: add Get multiple entities from name
   Entity* GetEntityFromName(const std::string& strName) const;

   //Deletes all the entities that were added in the list to delete... Call this function at the END of every game loop... (Call after collision detection because collision detection stores the pointer to the ColliderComponent and it would become a dangling pointer if the entity is deleted earlier
   void DeleteEntities();  

   void DestroyEntity(Entity* const pEntity);  //To do: add a destroy by name

private:
   std::list<Entity*> m_listEntities;
   std::list<Entity*> m_listEntitiesToDelete;
};