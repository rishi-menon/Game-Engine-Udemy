
#include "pch.h"

#include "TransformPartialComponent.h"
#include "Component/BoxColliderComponent.h"

#include "Entity/Entity.h"
#include "Collision/CollisionManager.h"

TransformPartialComponent::TransformPartialComponent(const glm::vec2& pos, const glm::vec2& scale) :
   m_vPosition(pos), m_vScale(scale)
{
}

TransformPartialComponent::~TransformPartialComponent()
{

}

void TransformPartialComponent::GetRect(Engine::Rect& rect) const
{
   rect.SetCenter(m_vPosition.x, m_vPosition.y, m_vScale.x, m_vScale.y);
}
Engine::Rect TransformPartialComponent::GetRect() const
{
   Engine::Rect rect;
   GetRect(rect);
   return rect;
}

inline void TransformPartialComponent::AddToCollisionListHelper ()
{
   ASSERT(m_pEntityOwner);
   BoxColliderComponent* pBoxCollider = m_pEntityOwner->GetComponent<BoxColliderComponent>();
   if (pBoxCollider)
   {
      Engine::CollisionManager::AddToCollisionList(pBoxCollider);
   }
}
void TransformPartialComponent::Translate(float dx, float dy) 
{ 
   m_vPosition.x += dx;
   m_vPosition.y += dy;
   AddToCollisionListHelper();
}                        
void TransformPartialComponent::Translate(const glm::vec2& offset) 
{ 
   Translate (offset.x, offset.y); 
}
void TransformPartialComponent::SetPosition(float x, float y)
{
   m_vPosition.x = x;
   m_vPosition.y = y;
   AddToCollisionListHelper();
}

void TransformPartialComponent::SetPosition(const glm::vec2& pos)
{
   SetPosition(pos.x, pos.y);
}

void TransformPartialComponent::SetPositionWithoutCollision(float x, float y)
{
   m_vPosition.x = x;
   m_vPosition.y = y;
}
void TransformPartialComponent::SetPositionWithoutCollision(const glm::vec2& pos)
{
   SetPositionWithoutCollision(pos.x, pos.y);
}

void TransformPartialComponent::SetScale(float x, float y)
{  
   m_vScale.x = x;
   m_vScale.y = y;
}
void TransformPartialComponent::SetScale(const glm::vec2& pos)
{
   SetScale(pos.x, pos.y);
}

bool TransformPartialComponent::SetValueTable(const sol::table& table)
{
   if (!Component::SetValueTable(table)) { ASSERT(false); return false; }
   //Translation
   {
      sol::optional<sol::table> positionTable = table["Position"];
      if (!positionTable)  return false;

      sol::optional<float> posX = positionTable.value()["X"];
      sol::optional<float> posY = positionTable.value()["Y"];
      if (!posX || !posY) { return false; }

      m_vPosition.x = posX.value();
      m_vPosition.y = posY.value();
   }
   //Scale
   {
      sol::optional<sol::table> scaleTable = table["Scale"];
      if (!scaleTable)  return false;

      sol::optional<float> scaleX = scaleTable.value()["X"];
      sol::optional<float> scaleY = scaleTable.value()["Y"];
      if (!scaleX || !scaleY) { return false; }

      m_vScale.x = scaleX.value();
      m_vScale.y = scaleY.value();
   }
   return true;
}

std::string TransformPartialComponent::SaveComponentToLua(bool bAddMoreLines) const
{
   std::string strLua;
   strLua.reserve(100);
   strLua += Component::SaveComponentToLua();
   strLua += StringR::Format("\tPosition = { X = %.1f, Y = %.1f },\n", m_vPosition.x, m_vPosition.y);
   strLua += StringR::Format("\tScale = { X = %.1f, Y = %.1f }", m_vScale.x, m_vScale.y);
   if (bAddMoreLines) { strLua += ','; }
   strLua += '\n';
   return strLua;
}