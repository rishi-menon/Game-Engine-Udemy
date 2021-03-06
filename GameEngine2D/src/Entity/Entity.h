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
   Component* CopyComponent(Component* pComponent);

   template <typename T, typename ... TArgs>
   inline T* AddComponent(TArgs&& ... args);

   //Ideally use this to directly get the component when only a single one exists... If multiple components of the same type exists then it returns the first component in the array (the one which was added first)... Preferably use GetComponents if multiple components exists.
   template <typename T>
   inline T* GetComponent() const;


   //Use this for getting an array of all components of a certain type (like all sprite components for example)... DO NOT use this function to get components of different types... Use the GetComponentsGeneric for that
   template <typename T>
   inline bool GetComponents(const Components*& outVec) const;  //function returns the pointer to the vector of components (aka Componets) instead of creating a copy.

   //Use this function if you want to get a components of different types
   bool GetComponentsGeneric(const std::vector<ComponentType>& vecComponents, ComponentsMap& map);

   inline bool GetIsActive() const { return m_bIsActive; }
   void SetIsActive(bool bIsActive) { m_bIsActive = bIsActive; }

   void OnCollisionEnter(BoxColliderComponent* otherCollider);
   void OnCollision(BoxColliderComponent* otherCollider);
   void OnCollisionExit(BoxColliderComponent* otherCollider);

   inline const std::unordered_map<ComponentType, Components>& GetComponentsMap() const { return m_umapComponentType; }
   
   inline EntityManager* GetEntityManager() const { ASSERT(m_pEntityManager); return m_pEntityManager; }
   void SetEntityManager(EntityManager* pManager) { m_pEntityManager = pManager; }

   inline const std::string& GetName() const { return m_strName; }
   void SetName(const std::string& strName) { m_strName = strName; }

   std::string SaveEntityLuaScene(const std::string& subTableName) const;  //use this to save the entity to a lua scene... main differnce is that this creates a table (ie: entities[0] = {},) before proceeding... This table creation is different while saving a prefab
   
   //save the entity as a seperate lua file which can be used as a prefab in the future (for instantiating)
   bool SaveEntityPrefabLua(const std::string& filePath) const;

private:
   void OnDestroy();
   void SaveEntityToLua(const std::string& subTableName, std::string& outStrLua) const;

private:
   std::unordered_map<ComponentType, Components> m_umapComponentType;
   EntityManager* m_pEntityManager;

   bool m_bIsActive;
   std::string m_strName;
};

//contains definition of the template functions
#include "Entity.hpp"