#pragma once

#include "Component.h"

class TransformComponent : public Component
{
public:
   COMPONENT_TYPE(Transform);
   TransformComponent(const glm::vec2& pos, const glm::vec2& vel, const glm::vec2& scale);

   virtual ~TransformComponent();

   virtual void OnInitialise() override;
   virtual void OnUpdate(double deltaTime) override;
   //virtual void OnRender() override;


public:
   glm::vec2 m_vPosition;
   glm::vec2 m_vVeloctiy;
   glm::vec2 m_vScale;

};