#pragma once

#include "Component/Component.h"
#include <vector>
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

#include "Log/Log.h"

//Components
#include "Component/Transform/TransformComponent.h"
#include "Component/Transform/TransformUIComponent.h"
#include "Component/SpriteComponent.h"
#include "Component/AnimationComponent.h"
#include "Component/PlayerControllerComponent.h"
#include "Component/BoxColliderComponent.h"
#include "Component/UITextComponent.h"
#include "Component/Scripts/EnemyMovementScript.h"
#include "Component/SelfDestructComponent.h"

class EntityManager;


class Entity
{
public:
   Entity(const std::string& strName = "");
   Entity(EntityManager* manager, const std::string& strName = "");
   ~Entity();

   void OnInitialise();
   void OnUpdate(double deltaTime);
   void OnRender();

   //To do: variable number of parameters, in normal and in template, AND std::forward 

   template <typename T, typename ... TArgs>
   T* AddComponent(TArgs&& ... args)
   {
      T* pComponent = new T(std::forward<TArgs>(args) ...);
      ASSERT(pComponent);
      if (pComponent)
      {
         std::unordered_map<ComponentType, Components>::iterator it = m_umapComponentType.find(T::GetStaticType());
         if (it != m_umapComponentType.end())
         {
            it->second.emplace_back(pComponent);
         }
         else
         {
            //comp.emplace_back(pComponent);
            m_umapComponentType.emplace(T::GetStaticType(), Components{ pComponent });
         }

         pComponent->SetEntityOwner(this);
         return pComponent;
      }
      return nullptr;
   }

   Component* CopyComponent(Component* pComponent);

   //Ideally use this to directly get the component when only a single one exists... If multiple components of the same type exists then it returns the first component in the array (the one which was added first)... Preferably use GetComponents if multiple components exists.
   template <typename T>
   T* GetComponent() const
   {
      std::unordered_map<ComponentType, Components>::const_iterator it = m_umapComponentType.find(T::GetStaticType());
      
      if (it != m_umapComponentType.end())
      {
         ASSERT(it->second.size() > 0);
         ASSERT(it->second.size() == 1);  //This function should mainly only be used when there is only one component... If there are multiple then the first component in the array is returned (which is probably bad as it can be random).... Use GetComponents in that case
         if (it->second.size() > 0)
         {
            ASSERT(it->second.at(0)->GetType() == T::GetStaticType());
            return static_cast<T*>(it->second.at(0));
         }
      }
      //Component was not found...
      return nullptr;
   }

   //Use this for getting an array of all components of a certain type (like all sprite components for example)... DO NOT use this function to get components of different types... Use the GetComponentsGeneric for that
   template <typename T>
   bool GetComponents(const Components*& outVec) const  //function returns the pointer to the vector of components (aka Componets) instead of creating a copy.
   {
      std::unordered_map<ComponentType, Components>::const_iterator it = m_umapComponentType.find(T::GetStaticType());
      if (it != m_umapComponentType.end())
      {
         outVec = &(it->second);
         return true;
      }
      return 0;
   }

   //Use this function if you want to get a components of different types
   bool GetComponentsGeneric(const std::vector<ComponentType>& vecComponents, ComponentsMap& map);

   inline bool GetIsActive() const { return m_bIsActive; }
   void SetIsActive(bool bIsActive) { m_bIsActive = bIsActive; }

   void OnCollisionEnter(BoxColliderComponent& otherCollider);
   void OnCollision(BoxColliderComponent& otherCollider);
   void OnCollisionExit(BoxColliderComponent& otherCollider);

   inline const std::unordered_map<ComponentType, Components>& GetComponentsMap() const { return m_umapComponentType; }
   
   inline EntityManager* GetEntityManager() const { ASSERT(m_pEntityManager); return m_pEntityManager; }
   void SetEntityManager(EntityManager* pManager) { m_pEntityManager = pManager; }

   inline const std::string& GetName() const { return m_strName; }
   void SetName(const std::string& strName) { m_strName = strName; }

private:
   void OnDestroy();

private:
   std::unordered_map<ComponentType, Components> m_umapComponentType;
   EntityManager* m_pEntityManager;

   bool m_bIsActive;
   std::string m_strName;
};