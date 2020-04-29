#pragma once
#include "Component/Component.h"
#include "TransformPartialComponent.h"

class TransformComponent : public TransformPartialComponent
{
public:
   COMPONENT_NAME("Transform")
   COMPONENT_TYPE(Transform);

   TransformComponent(const glm::vec2& pos, const glm::vec2& vel, const glm::vec2& scale);
   virtual ~TransformComponent();

   virtual void OnInitialise() override;
   virtual void OnUpdate(double deltaTime) override;
   virtual void OnRender() override;

public:
   glm::vec2 m_vVeloctiy;
};