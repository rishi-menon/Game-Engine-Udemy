#pragma once
#include "TransformPartialComponent.h"

class TransformUIComponent : public TransformPartialComponent
{
public:
   COMPONENT_NAME("Transform UI");
   COMPONENT_TYPE(TransformUI);

   //Position and Scale are stored in pixels. (If you decide to change this then you need to change the camera class WorldTransformToScreen)
   TransformUIComponent(const glm::vec2& pos, const glm::vec2& scale);
   virtual ~TransformUIComponent();
   
private:
};