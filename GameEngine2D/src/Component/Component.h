#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <array>
#include <lua/include/sol.hpp>

class Entity;

//Components... For other files that include this header mainly
class Component;
class TransformComponent;
class TransformUIComponent;
class SpriteComponent;
class AnimationComponent;
class PlayerControllerComponent;
class BoxColliderComponent;
class SelfDestructComponent;

class UITextComponent;

class EnemyMovementScript;


enum class ComponentType : unsigned int
{
   
   None = 0,
   Transform,
   TransformUI,
   Sprite,
   Animation,   //for a spritesheet
   PlayerController,
   BoxCollider,
   SelfDestruct,

   UIText,

   //custom scripts
   EnemyMovementScript
};

using Components = std::vector<Component*>;
//map of POINTER to the vector, not the actual vector itself.. The actual vector will be stored in the Entity object... (So the entity object should have a map that stores the VECTOR and not the POINTER to it).
using ComponentsMap = std::unordered_map<ComponentType, const Components*>;

//These global arrays will be used by GetComponentsGeneric method
namespace GenericComponent
{
   extern const std::vector<ComponentType> TransformPartial;
}


#define COMPONENT_TYPE(x)  public: \
                           const static ComponentType GetStaticType()     { return ComponentType::##x; } \
                           virtual ComponentType GetType() const override { return ComponentType::##x; }

#define COMPONENT_NAME(x)  public: \
                           virtual std::string GetName() const override { return x; }
                           



class Component
{
public:
   Component() : m_pEntityOwner(nullptr), m_bIsEnabled(true) {}
   virtual ~Component() {}

   //Callbacks?
   virtual void OnInitialise() {}

   virtual void OnPreUpdate(double deltaTime) {}  //All the components preupdate gets called before the postupdate
   virtual void OnUpdate(double deltaTime) {}   //in seconds
   
   virtual void OnRender() {}
   virtual void OnDestroy() {}

   //properties
   virtual std::string GetName() const = 0;  //only for debugging currently. Could be useful while creating GUI though ?
   virtual ComponentType GetType() const = 0;

   inline Entity* GetEntityOwner() const { return m_pEntityOwner; }
   void SetEntityOwner(Entity* pEntity) { m_pEntityOwner = pEntity; }

   bool GetEnabled() const { return m_bIsEnabled; }
   void SetEnabled(bool bEnabled) { m_bIsEnabled = bEnabled; }

   //Collisions
   virtual void OnCollisionEnter(BoxColliderComponent& otherCollider) {}
   virtual void OnCollision(BoxColliderComponent& otherCollider)      {}
   virtual void OnCollisionExit(BoxColliderComponent& otherCollider)  {}

   //While instantiating a gameobject, the components from the prefab are copied into a new one... If you dont want a component to be copied, then override this function in that specific component to return false
   virtual bool CopyDuringInstantiate() const { return true; }


   virtual bool SetValueTable(const sol::table& table) { return true; }

protected:
   Entity* m_pEntityOwner;
   bool m_bIsEnabled;
};

