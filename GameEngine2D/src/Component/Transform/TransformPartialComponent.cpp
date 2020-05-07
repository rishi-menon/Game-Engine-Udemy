
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
void TransformPartialComponent::SetPosition(float x, float y)
{
   m_vPosition.x = x;
   m_vPosition.y = y;
   AddToCollisionListHelper();
}
void TransformPartialComponent::Translate(const glm::vec2& offset) 
{ 
   Translate (offset.x, offset.y); 
}

void TransformPartialComponent::SetPosition(const glm::vec2& pos)
{
   SetPosition(pos.x, pos.y);
}