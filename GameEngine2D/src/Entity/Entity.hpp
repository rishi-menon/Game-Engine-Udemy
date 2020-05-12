#pragma once

//This is for implementation of template functions inside Entity class

class Entity;
class Component;

template <typename T, typename ... TArgs>
inline T* Entity::AddComponent(TArgs&& ... args)
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

//Ideally use this to directly get the component when only a single one exists... If multiple components of the same type exists then it returns the first component in the array (the one which was added first)... Preferably use GetComponents if multiple components exists.
template <typename T>
inline T* Entity::GetComponent() const
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
inline bool Entity::GetComponents(const Components*& outVec) const  //function returns the pointer to the vector of components (aka Componets) instead of creating a copy.
{
   std::unordered_map<ComponentType, Components>::const_iterator it = m_umapComponentType.find(T::GetStaticType());
   if (it != m_umapComponentType.end())
   {
      outVec = &(it->second);
      return true;
   }
   return 0;
}