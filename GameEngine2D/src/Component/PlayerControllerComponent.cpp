
#include "pch.h"
#include "Entity/Entity.h"
#include "Game/Game.h"

//components
#include "PlayerControllerComponent.h"
#include "Transform/TransformComponent.h"
#include "AnimationComponent.h"

PlayerControllerComponent::PlayerControllerComponent() :
   m_vecVelocity(0, 0),
   m_pTransformComponent (nullptr),
   m_nKeyUp (0),
   m_nKeyRight(0),
   m_nKeyDown(0),
   m_nKeyLeft(0),
   m_nKeyFire(0)
{

}
PlayerControllerComponent::~PlayerControllerComponent()
{

}

void PlayerControllerComponent::SetMovementControls(const std::string& up, const std::string& right, const std::string& down, const std::string& left)
{
   m_nKeyUp       = GetKeyCodeFromString (up);
   m_nKeyRight    = GetKeyCodeFromString (left);
   m_nKeyDown     = GetKeyCodeFromString (down);
   m_nKeyLeft     = GetKeyCodeFromString (right);
}

void PlayerControllerComponent::SetFireControl(const std::string& st)
{
   m_nKeyFire = GetKeyCodeFromString(st);
}

int PlayerControllerComponent::GetKeyCodeFromString(const std::string& string)
{
   std::string st = string;
   //convert to lower case
   for (std::size_t i = 0; i < st.size(); i++)
   {
      st[i] = tolower(string[i]);
   }
   if (st.size() == 1)     { return static_cast<int>(st[0]); ASSERT(st[0] <= 'Z' && st[0] >= 'a'); }
   else if (st == "up")    { return SDLK_UP; }
   else if (st == "right") { return SDLK_RIGHT; }
   else if (st == "down")  { return SDLK_DOWN; }
   else if (st == "left")  { return SDLK_LEFT; }
   else if (st == "space") { return SDLK_SPACE; }
   else if (st == "esc")   { return SDLK_ESCAPE;}

   ASSERT(false); //Key was not converted properly ?
   return 0;
   
}
//overrides
void PlayerControllerComponent::OnInitialise() {
   m_pTransformComponent = m_pEntityOwner->GetComponent<TransformComponent>();
   ASSERT(m_pTransformComponent);
   m_pAnimationComponent = m_pEntityOwner->GetComponent<AnimationComponent>();   //this could be null 
}
void PlayerControllerComponent::OnUpdate(double deltaTime)
{
   //LOGW("Type: %d", Game::s_event.type);
   if (Game::s_event.type == SDL_KEYDOWN)
   {
      int key = Game::s_event.key.keysym.sym;
      if (key == m_nKeyUp)
      {
         m_pTransformComponent->m_vVeloctiy = glm::vec2(0, m_vecVelocity.y);
         //m_pTransformComponent->m_vVeloctiy.y = -m_vecVelocity.y;
         if (m_pAnimationComponent)
         {
            m_pAnimationComponent->SetCurrentAnimation(AnimationID::DirUp);
         }
      }
      else if (key == m_nKeyRight)
      {
         m_pTransformComponent->m_vVeloctiy = glm::vec2(m_vecVelocity.x, 0);
         //m_pTransformComponent->m_vVeloctiy.x = m_vecVelocity.x;
         if (m_pAnimationComponent)
         {
            m_pAnimationComponent->SetCurrentAnimation(AnimationID::DirRight);
         }
      }
      else if (key == m_nKeyDown)
      {
         m_pTransformComponent->m_vVeloctiy = glm::vec2(0, -m_vecVelocity.y);
         //m_pTransformComponent->m_vVeloctiy.y = m_vecVelocity.y;
         if (m_pAnimationComponent)
         {
            m_pAnimationComponent->SetCurrentAnimation(AnimationID::DirDown);
         }
      }
      else if (key == m_nKeyLeft)
      {
         m_pTransformComponent->m_vVeloctiy = glm::vec2(-m_vecVelocity.x, 0);
         //m_pTransformComponent->m_vVeloctiy.x = -m_vecVelocity.x;
         if (m_pAnimationComponent)
         {
            m_pAnimationComponent->SetCurrentAnimation(AnimationID::DirLeft);
         }
      }
      else if (key == m_nKeyFire)
      {
         //To do: Fire projectiles here ?
      }
   }
   else if (Game::s_event.type == SDL_KEYUP)
   {
      int key = Game::s_event.key.keysym.sym;
      if (key == m_nKeyUp)
      {
         m_pTransformComponent->m_vVeloctiy.y = 0;
      }
      else if (key == m_nKeyRight)
      {
         m_pTransformComponent->m_vVeloctiy.x = 0;
      }
      else if (key == m_nKeyDown)
      {
         m_pTransformComponent->m_vVeloctiy.y = 0;
      }
      else if (key == m_nKeyLeft)
      {
         m_pTransformComponent->m_vVeloctiy.x = 0;
      }
   }
}