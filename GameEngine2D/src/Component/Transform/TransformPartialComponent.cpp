
#include "pch.h"
#include "TransformPartialComponent.h"

TransformPartialComponent::TransformPartialComponent(const glm::vec2& pos, const glm::vec2& scale) :
   m_vPosition(pos), m_vScale(scale)
{
}

TransformPartialComponent::~TransformPartialComponent()
{

}