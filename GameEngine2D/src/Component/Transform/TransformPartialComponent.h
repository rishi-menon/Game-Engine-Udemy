#pragma once
#include "Component/Component.h"
#include <glm/glm.hpp>
#include "Collision/Rect.h"

//this is the base class for the transform(world) and the UI transform component
class TransformPartialComponent : public Component
{
public:
   TransformPartialComponent(const glm::vec2& pos, const glm::vec2& scale);
   virtual ~TransformPartialComponent();

   void GetRect(Engine::Rect& rect) const;
   Engine::Rect GetRect() const;

   void Translate(float dx, float dy);
   void Translate(const glm::vec2& offset);

   void SetPosition(float x, float y);
   void SetPosition(const glm::vec2& pos);
   
   const glm::vec2& GetPosition() const { return m_vPosition; }
   const glm::vec2& GetScale() const { return m_vScale; }

   void SetScale(float x, float y);
   void SetScale(const glm::vec2& pos);

   virtual bool SetValueTable(const sol::table& table) override;
   
protected:
   void SetPositionWithoutCollision(float x, float y);
   void SetPositionWithoutCollision(const glm::vec2& pos);

private:
   inline void AddToCollisionListHelper();   //Helper function to add the entity to the collision check list when it moves.
private:
   glm::vec2 m_vPosition;
   //this is the total width and height of the component... so position (0,0) and scale of (2,2) would mean it ranges position ranges from (-1,1) (For world transform)
   glm::vec2 m_vScale;  
};