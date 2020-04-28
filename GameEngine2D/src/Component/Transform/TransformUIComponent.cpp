
#include "pch.h"
#include "TransformUIComponent.h"

TransformUIComponent::TransformUIComponent(const glm::vec2& pos, const glm::vec2& scale) :
   TransformPartialComponent (pos, scale)
{
}
TransformUIComponent::~TransformUIComponent()
{
}