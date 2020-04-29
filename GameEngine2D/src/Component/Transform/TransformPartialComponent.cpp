
#include "pch.h"
#include "TransformPartialComponent.h"

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