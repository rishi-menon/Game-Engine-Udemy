
#include "Entity.h"
#include "Log/Log.h"
#include "Component/Transform/TransformComponent.h"

//To do: have a better way of setting the order of OnRender
static const int nRendererUpdateOrderCount = 3;
static const std::array<ComponentType, nRendererUpdateOrderCount> arrayRendererOrder{
   ComponentType::Sprite,
   ComponentType::BoxCollider,
   ComponentType::UIText
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
   OnDestroy();
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
Component* Entity::CopyComponent(Component* pComponent)
{
   ASSERT(pComponent);
   ComponentType type = pComponent->GetType();
   
   switch (type)
   {
   case ComponentType::Animation:        return (Component*)AddComponent<AnimationComponent>(*(AnimationComponent*)pComponent);

   case ComponentType::BoxCollider:      return (Component*)AddComponent<BoxColliderComponent>(*(BoxColliderComponent*)pComponent);

   case ComponentType::PlayerController: return (Component*)AddComponent<PlayerControllerComponent>(*(PlayerControllerComponent*)pComponent);
   case ComponentType::Sprite:              return (Component*)AddComponent<SpriteComponent>(*(SpriteComponent*)pComponent);
   case ComponentType::UIText:              return (Component*)AddComponent<UITextComponent>(*(UITextComponent*)pComponent);
   case ComponentType::Transform:           return (Component*)AddComponent<TransformComponent>(*(TransformComponent*)pComponent);
   case ComponentType::TransformUI:         return (Component*)AddComponent<TransformUIComponent>(*(TransformUIComponent*)pComponent);
   case ComponentType::EnemyMovementScript: return (Component*)AddComponent<EnemyMovementScript>(*(EnemyMovementScript*)pComponent);

   default:
      ASSERT(false);
      return nullptr;
   }
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
         if (pComponent->GetEnabled())
         {
            pComponent->OnPreUpdate(deltaTime);
         }
      }
   }

   itEntities = m_umapComponentType.begin();

   void* temp = this;

   for (; itEntities != m_umapComponentType.end(); itEntities++)
   {
      ASSERT(itEntities->second.size());
      for (Component* pComponent : itEntities->second)
      {
         if (pComponent->GetEnabled())
         {
            pComponent->OnUpdate(deltaTime);
         }
      }
   }
}
void Entity::OnRender()
{
   //To do: need to change this way of specifying order...
   for (std::size_t
      i = 0; i < arrayRendererOrder.size(); i++)
   {
      std::unordered_map<ComponentType, Components>::iterator it = m_umapComponentType.find(arrayRendererOrder.at(i));
      if (it != m_umapComponentType.end())
      {
         ASSERT(it->second.size());
         for (Component* pComponent : it->second)
         {
            if (pComponent->GetEnabled())
            {
               pComponent->OnRender();
            }
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
         ASSERT(pComponent);
         //Only call OnDestroy if the component is enabled or always ??
         pComponent->OnDestroy();
         
      }
   }
   m_bIsActive = false;
}

void Entity::OnCollisionEnter(BoxColliderComponent& otherCollider)
{
   for (std::pair<const ComponentType, Components>& pair : m_umapComponentType)
   {
      ASSERT(pair.second.size());
      for (Component* pComponent : pair.second)
      {
         if (pComponent->GetEnabled())
         {
            pComponent->OnCollisionEnter(otherCollider);
         }
      }
   }
}
void Entity::OnCollision(BoxColliderComponent& otherCollider)
{
   for (std::pair<const ComponentType, Components>& pair : m_umapComponentType)
   {
      ASSERT(pair.second.size());
      for (Component* pComponent : pair.second)
      {
         if (pComponent->GetEnabled())
         {
            pComponent->OnCollision(otherCollider);
         }
      }
   }
}
void Entity::OnCollisionExit(BoxColliderComponent& otherCollider)
{
   for (std::pair<const ComponentType, Components>& pair : m_umapComponentType)
   {
      ASSERT(pair.second.size());
      for (Component* pComponent : pair.second)
      {
         if (pComponent->GetEnabled())
         {
            pComponent->OnCollisionExit(otherCollider);
         }
      }
   }
}