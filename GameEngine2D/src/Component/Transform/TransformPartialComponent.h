#pragma once
#include "Component/Component.h"
#include <glm/glm.hpp>

//this is the base class for the transform(world) and the UI transform component
class TransformPartialComponent : public Component
{
public:
   COMPONENT_TYPE(Transform)
   COMPONENT_NAME("TransformPartial")
   
   TransformPartialComponent(const glm::vec2& pos, const glm::vec2& scale);
   virtual ~TransformPartialComponent();
   
   virtual ComponentSubType GetSubType() const = 0;

public:
   glm::vec2 m_vPosition;
   glm::vec2 m_vScale;
};