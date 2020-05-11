
#include "pch.h"
#include "SelfDestructComponent.h"
#include "Entity/EntityManager.h"

void SelfDestructComponent::OnUpdate(double deltaTime)
{
   m_dTimeElapsed += deltaTime;
   if (m_dTimeElapsed >= m_dTimeTotal)
   {
      //Destroy the gameobject
      ASSERT(m_pEntityOwner);
      m_pEntityOwner->GetEntityManager()->DestroyEntity(m_pEntityOwner);
   }
}

bool SelfDestructComponent::SetValueTable(const sol::table& table)
{
   if (!Component::SetValueTable(table)) { ASSERT(false); return false; }
   sol::optional<double> totalTime = table["AliveTime"];
   if (!totalTime) { ASSERT(false); return false; }
   
   m_dTimeTotal = totalTime.value();
   m_dTimeElapsed = 0.0;
   return true;
}

std::string SelfDestructComponent::SaveComponentToLua(const std::string& strSubTableName) const
{

   std::string strLua;
   strLua.reserve(50);
   strLua += StringR::Format("%s.Components.SelfDestruct = {\n", strSubTableName.c_str());
   strLua += Component::SaveComponentToLua();
   strLua += StringR::Format("\tAliveTime = %.1f", m_dTimeTotal);
   strLua += '}';
   strLua += '\n';
   return strLua;
}
