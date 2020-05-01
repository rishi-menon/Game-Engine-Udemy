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
   
   const glm::vec2& GetPosition() const { return m_vPosition; }
   const glm::vec2& GetScale() const { return m_vScale; }
   
private:
   glm::vec2 m_vPosition;
   //this is the total width and height of the component... so position (0,0) and scale of (2,2) would mean it ranges position ranges from (-1,1) (For world transform)
   glm::vec2 m_vScale;  
};