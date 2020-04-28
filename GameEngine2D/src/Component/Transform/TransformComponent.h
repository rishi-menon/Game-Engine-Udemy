#pragma once

#include "TransformPartialComponent.h"

class TransformComponent : public TransformPartialComponent
{
public:
   COMPONENT_NAME("Transform")
   TransformComponent(const glm::vec2& pos, const glm::vec2& vel, const glm::vec2& scale);
   virtual ~TransformComponent();
   virtual ComponentSubType GetSubType() const override { return ComponentSubType::TransformWorld; }

   virtual void OnInitialise() override;
   virtual void OnUpdate(double deltaTime) override;
   //virtual void OnRender() override;

public:
   glm::vec2 m_vVeloctiy;
};