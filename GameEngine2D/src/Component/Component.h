#pragma once

#include <string>

class Entity;

//Components... For other files that include this header mainly
class TransformComponent;
class SpriteComponent;
class AnimationComponent;
class PlayerControllerComponent;

enum class ComponentType : unsigned int
{
   None = 0,
   Transform,
   Sprite,
   Animation,   //for a spritesheet
   PlayerController
};

//To do: GetComponent<TransformPartial> should return a list of all the transform components and            GetComponent<TransformComponent> should return the specific component
enum class ComponentSubType : unsigned int
{
   //transform
   TransformWorld = 0,
   TransformUI
};

#define COMPONENT_TYPE(x)  static ComponentType GetStaticType()           { return ComponentType::##x; } \
                           virtual ComponentType GetType() const override { return ComponentType::##x; }

#define COMPONENT_NAME(x)  virtual std::string GetName() const override   { return x; } \
                           static  std::string GetStaticName()            { return x; } /*Purely for debugging purposes*/
class Component
{
public:
   Component() {}
   virtual ~Component() {}

   //Callbacks?
   virtual void OnInitialise() {}

   virtual void PreUpdate(double deltaTime) {}  //All the components preupdate gets called before the postupdate
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
};

