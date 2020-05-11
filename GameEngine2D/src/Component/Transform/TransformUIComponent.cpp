
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
   if (!TransformPartialComponent::SetValueTable(table)) { ASSERT(false); return false; }

   return true;
}

std::string TransformUIComponent::SaveComponentToLua(const std::string& strSubTableName) const
{
   std::string strLua;
   strLua.reserve(100);
   strLua += StringR::Format("%s.Components.TransformUI = {\n", strSubTableName.c_str());
   strLua += TransformPartialComponent::SaveComponentToLua(false);
   strLua += '}';
   strLua += '\n';
   return strLua;
}
