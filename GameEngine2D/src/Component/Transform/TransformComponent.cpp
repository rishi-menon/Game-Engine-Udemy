
#include "pch.h"
#include "TransformComponent.h"
#include "Game/Game.h"

TransformComponent::TransformComponent(const glm::vec2& pos, const glm::vec2& vel, const glm::vec2& scale) :
   TransformPartialComponent (pos, scale),
   m_vVeloctiy (vel)
{
}

//Use ONLY while creating a component via a lua script
TransformComponent::TransformComponent() : 
   TransformPartialComponent(glm::vec2{ 0.0f, 0.0f }, glm::vec2{ 0.0f, 0.0f }),
   m_vVeloctiy (glm::vec2{ 0.0f, 0.0f })
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

bool TransformComponent::SetValueTable(const sol::table& table)
{

   bool bSuccess = TransformPartialComponent::SetValueTable(table);
   
   //Rotation
   {
      sol::optional<sol::table> velocityTable = table["Velocity"];
      if (velocityTable == sol::nullopt)  return false;

      sol::optional<float> velX = velocityTable.value()["x"];
      sol::optional<float> velY = velocityTable.value()["y"];
      if ( velX == sol::nullopt || velY == sol::nullopt) { return false; }

      m_vVeloctiy.x = velX.value();
      m_vVeloctiy.y = velY.value();
   }
   
   return true;
}