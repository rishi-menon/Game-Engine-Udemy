#pragma once
#include "TransformPartialComponent.h"

class TransformUIComponent : public TransformPartialComponent
{
public:
   COMPONENT_NAME("Transform UI");
   COMPONENT_TYPE(TransformUI);

   //Position is the coordinates of the center and is stored as percentage across the screen with top left corner being (0,0). Scale is stored in pixels. (If you decide to change this then you need to change the camera class WorldTransformToScreen)
   TransformUIComponent(const glm::vec2& pos, const glm::vec2& scale);
   virtual ~TransformUIComponent();
   
private:
};