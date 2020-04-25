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

#define COMPONENT_TYPE(x)  virtual std::string GetName() const override   { return #x; } \
                           static std::string GetStaticName()             { return #x; } /*Purely for debugging purposes*/ \
                           static ComponentType GetStaticType()           { return ComponentType::##x; } \
                           virtual ComponentType GetType() const override { return ComponentType::##x; }

class Component
{
public:
   Component() {}
   virtual ~Component() {}

   virtual void OnInitialise() {}
   virtual void OnUpdate(double deltaTime) {}   //in seconds
   virtual void OnRender() {}

   virtual void OnDestroy() {}

   virtual std::string GetName() const = 0;  //only for debugging currently. Could be useful while creating GUI though ?
   virtual ComponentType GetType() const = 0;

   inline Entity* GetEntityOwner() const { return m_pEntityOwner; }
   void SetEntityOwner(Entity* pEntity) { m_pEntityOwner = pEntity; }

protected:
   Entity* m_pEntityOwner;
};

