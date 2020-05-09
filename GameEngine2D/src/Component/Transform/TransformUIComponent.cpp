
#include "pch.h"
#include "TransformUIComponent.h"

//Do NOT use this constructor... It is only for creating components from a lua script.
TransformUIComponent::TransformUIComponent() :
   TransformPartialComponent(glm::vec2{ 0.0f,0.0f }, glm::vec2{ 0.0f,0.0f })
{
}
TransformUIComponent::TransformUIComponent(const glm::vec2& pos, const glm::vec2& scale) :
   TransformPartialComponent (pos, scale)
{
}
TransformUIComponent::~TransformUIComponent()
{
}

bool TransformUIComponent::SetValueTable(const sol::table& table)
{
   return TransformPartialComponent::SetValueTable(table);
}
