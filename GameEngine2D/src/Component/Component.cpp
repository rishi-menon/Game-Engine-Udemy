#include "Component.h"
#include "Log/Log.h"
#include "Common/StringHelper.h"

//These global arrays will be used by GetComponentsGeneric method
namespace GenericComponent
{
   const std::vector<ComponentType> TransformPartial = {ComponentType::Transform, ComponentType::TransformUI};
}

bool Component::SetValueTable(const sol::table& table)
{
   ASSERT (sol::type::boolean == table["Active"]);
   sol::optional<bool> active = table["Active"];
   if (active)
   {
      m_bIsEnabled = active.value();
      return true;
   }
   ASSERT(false);
   return false;
}

std::string Component::SaveComponentToLua() const
{
   std::string strLua = StringR::Format("\tActive = %s,\n", m_bIsEnabled ? "true" : "false");
   return strLua;
}