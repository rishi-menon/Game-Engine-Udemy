
#include "pch.h"
#include "TransformComponent.h"
#include "Game/Game.h"

TransformComponent::TransformComponent(const glm::vec2& pos, const glm::vec2& vel, const glm::vec2& scale) :
   TransformPartialComponent (pos, scale),
   m_vVeloctiy (vel)
{
}

TransformComponent::~TransformComponent()
{
}
void TransformComponent::OnInitialise()
{

}

void TransformComponent::OnUpdate(double deltaTime)
{
   Translate((float)(m_vVeloctiy.x * deltaTime), (float)(m_vVeloctiy.y * deltaTime));
}

void TransformComponent::OnRender()
{
   //SDL_Rect rect;
   //Game::s_camera.WorldTransformToScreenRect(*this, rect);
   //SDL_SetRenderDrawColor(Game::s_pRenderer, 255, 10, 10, 255);
   //SDL_RenderFillRect(Game::s_pRenderer, &rect);
}

void TransformComponent::OnCollisionEnter(BoxColliderComponent& otherCollider)
{
   LOGW("\n\nCollision START \n\n");
}
void TransformComponent::OnCollision(BoxColliderComponent& otherCollider)
{
   LOGW("Collision");
}
void TransformComponent::OnCollisionExit(BoxColliderComponent& otherCollider)
{
   LOGW("\n\nCollision END\n\n");
}