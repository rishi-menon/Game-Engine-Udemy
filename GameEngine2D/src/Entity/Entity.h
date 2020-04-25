#pragma once

#include "Component/Component.h"
#include <vector>
#include <string>
#include <unordered_map>

class EntityManager;

class Entity
{
public:
   Entity(EntityManager& manager, const std::string& str = "");
   ~Entity();

   void OnUpdate(double deltaTime);
   void OnRender();
   void OnDestroy();

   //To do: variable number of parameters, in normal and in template, AND std::forward 
   template <typename T, typename ... TArgs>
   T& AddComponent(TArgs&& ... args)
   {
      T* pComponent = new T(std::forward<TArgs>(args) ...);
      m_umapComponentType.insert({ T::GetStaticType(), pComponent });
      m_vComponents.emplace_back(pComponent);

      pComponent->SetEntityOwner(this);
      pComponent->OnInitialise();
      return *pComponent;
   }

   template <typename T>
   T* GetComponent() const
   {
      std::unordered_map<ComponentType, Component*>::const_iterator it = m_umapComponentType.find(T::GetStaticType());
      if (it != m_umapComponentType.end())
      {
         return static_cast<T*>((*it).second);
      }
      //No Component was found... Probably bad ? GetComponent can also be used as HasComponent so its probably not very bad
      LOGW("Component %s does not exist", T::GetStaticName().c_str());
      return nullptr;
   }

   inline bool GetIsActive() const { return m_bIsActive; }

   inline std::size_t GetCount() { return m_vComponents.size(); }

   inline std::vector<Component*>& GetComponentsVector() { return m_vComponents; }

   inline const std::string& GetName() const { return m_strName; }
private:
   std::vector<Component*> m_vComponents;
   std::unordered_map<ComponentType, Component*> m_umapComponentType;
   EntityManager& m_entityManager;

   bool m_bIsActive;
   std::string m_strName;
};