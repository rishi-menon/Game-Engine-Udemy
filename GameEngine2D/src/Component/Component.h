#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <array>

class Entity;

//Components... For other files that include this header mainly
class Component;
class TransformComponent;
class TransformUIComponent;
class SpriteComponent;
class AnimationComponent;
class PlayerControllerComponent;
class BoxColliderComponent;


enum class ComponentType : unsigned int
{
   
   None = 0,
   Transform,
   TransformUI,
   Sprite,
   Animation,   //for a spritesheet
   PlayerController,
   BoxCollider

};

using Components = std::vector<Component*>;
//map of POINTER to the vector, not the actual vector itself.. The actual vector will be stored in the Entity object... (So the entity object should have a map that stores the VECTOR and not the POINTER to it).
using ComponentsMap = std::unordered_map<ComponentType, const Components*>;

//These global arrays will be used by GetComponentsGeneric method
namespace GenericComponent
{
   extern const std::vector<ComponentType> TransformPartial;
}


#define COMPONENT_TYPE(x)  const static ComponentType GetStaticType()     { return ComponentType::##x; } \
                           virtual ComponentType GetType() const override { return ComponentType::##x; }

#define COMPONENT_NAME(x)  virtual std::string GetName() const override { return x; }
                           



class Component
{
public:
   Component() : m_pEntityOwner(nullptr) {}
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

protected:
   Entity* m_pEntityOwner;
   //To do: add a bool isEnabled
};

