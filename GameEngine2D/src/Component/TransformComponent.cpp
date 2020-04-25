
#include "pch.h"
#include "TransformComponent.h"
#include "Game/Game.h"

TransformComponent::TransformComponent(const glm::vec2& pos, const glm::vec2& vel, const glm::vec2& scale) :
   m_vPosition (pos), 
   m_vVeloctiy (vel),
   m_vScale (scale)
{
   LOG("Created Transform Component", Log::Trace);
}

TransformComponent::~TransformComponent()
{
}
void TransformComponent::OnInitialise()
{
}

void TransformComponent::OnUpdate(double deltaTime)
{
   m_vPosition.x += static_cast<float>(m_vVeloctiy.x * deltaTime);
   m_vPosition.y += static_cast<float>(m_vVeloctiy.y * deltaTime);
}

//void TransformComponent::OnRender()
//{
//   SDL_Rect rect{
//   (int)m_vPosition.x,
//   (int)m_vPosition.y,
//   (int)m_vScale.x,
//   (int)m_vScale.y
//   };
//
//   SDL_SetRenderDrawColor(Game::s_pRenderer, 255, 10, 10, 255);
//   SDL_RenderFillRect(Game::s_pRenderer, &rect);
//}