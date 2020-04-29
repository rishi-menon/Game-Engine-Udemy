
#include "Entity.h"
#include "Log/Log.h"
#include "Component/Transform/TransformComponent.h"

//To do: have a enum class to store the order in which the components are updated??

static const int nRendererUpdateOrderCount = 2;
static const std::array<ComponentType, nRendererUpdateOrderCount> arrayRendererOrder{
   ComponentType::Sprite,
   ComponentType::BoxCollider
};

Entity::Entity(EntityManager& manager, const std::string& strName /*= ""*/) :
   m_entityManager (manager),
   m_bIsActive (true),
   m_strName (strName)
{
   m_umapComponentType.reserve(10);   //reserve storage for 10 components to prevent constant allocation of memory
}
Entity::~Entity()
{
   std::unordered_map<ComponentType, Components>::iterator itComponents = m_umapComponentType.begin();

   for (; itComponents != m_umapComponentType.end(); itComponents++)
   {
      ASSERT(itComponents->second.size());
      for (Component* pComponent : itComponents->second)
      {
         delete pComponent;
      }
      itComponents->second.clear();
   }

   m_umapComponentType.clear();
}

bool Entity::GetComponentsGeneric(const std::vector<ComponentType>& vecComponents, ComponentsMap& map)
{
   for (ComponentType type : vecComponents)
   {
      std::unordered_map<ComponentType, Components>::const_iterator it = m_umapComponentType.find(type);
      if (it != m_umapComponentType.end())
      {
         ASSERT(it->second.size());
         map.emplace(type, &(it->second));
      }
   }
   return map.size();
}

void Entity::OnInitialise()
{
   std::unordered_map<ComponentType, Components>::iterator itEntities = m_umapComponentType.begin();

   for (; itEntities != m_umapComponentType.end(); itEntities++)
   {
      ASSERT(itEntities->second.size());
      for (Component* pComponent : itEntities->second)
      {
         pComponent->OnInitialise();
      }
   }
}

void Entity::OnUpdate(double deltaTime)
{
   std::unordered_map<ComponentType, Components>::iterator itEntities = m_umapComponentType.begin();

   for (; itEntities != m_umapComponentType.end(); itEntities++)
   {
      ASSERT(itEntities->second.size());
      for (Component* pComponent : itEntities->second)
      {
         pComponent->OnPreUpdate(deltaTime);
      }
   }

   itEntities = m_umapComponentType.begin();

   for (; itEntities != m_umapComponentType.end(); itEntities++)
   {
      ASSERT(itEntities->second.size());
      for (Component* pComponent : itEntities->second)
      {
         pComponent->OnUpdate(deltaTime);
      }
   }
}
void Entity::OnRender()
{
   for (int i = 0; i < arrayRendererOrder.size(); i++)
   {
      std::unordered_map<ComponentType, Components>::iterator it = m_umapComponentType.find(arrayRendererOrder.at(i));
      if (it != m_umapComponentType.end())
      {
         ASSERT(it->second.size());
         for (Component* pComponent : it->second)
         {
            pComponent->OnRender();
         }
      }
   }
}

void Entity::OnDestroy()
{
   std::unordered_map<ComponentType, Components>::iterator itEntities = m_umapComponentType.begin();
   for (; itEntities != m_umapComponentType.end(); itEntities++)
   {
      ASSERT(itEntities->second.size());
      for (Component* pComponent : itEntities->second)
      {
         pComponent->OnDestroy();
      }
   }

   m_bIsActive = false;
}