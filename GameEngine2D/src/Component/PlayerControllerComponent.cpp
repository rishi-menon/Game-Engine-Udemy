
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
   m_nKeyUp      =    GetScanCodeFromString (up);
   m_nKeyRight   =    GetScanCodeFromString (left);
   m_nKeyDown    =    GetScanCodeFromString (down);
   m_nKeyLeft    =    GetScanCodeFromString (right);
}

void PlayerControllerComponent::SetFireControl(const std::string& st)
{
   m_nKeyFire    =     GetScanCodeFromString(st);
}

int PlayerControllerComponent::GetScanCodeFromString(const std::string& string)
{
#if 0
   std::string st = string;
   //convert to lower case
   for (std::size_t i = 0; i < st.size(); i++)
   {
      st[i] = tolower(string[i]);
   }
   //To do: find a generic way of doing this
   if (st.size() != 1)
   {
      if (st == "up") { return SDLK_UP; }
      else if (st == "right") { return SDL_SCANCODE_RIGHT; }
      else if (st == "down") { return SDL_SCANCODE_DOWN; }
      else if (st == "left") { return SDL_SCANCODE_LEFT; }
      else if (st == "space") { return SDL_SCANCODE_SPACE; }
      else if (st == "esc") { return SDL_SCANCODE_ESCAPE; }
   }
   else
   {
      char c = st[0];
      if (isdigit(c))
      {
         //0 has a value AFTER 9 hence why it has to be handled seperately
         if (c == '0')  return SDL_SCANCODE_0;
         else return (c - '1' + SDL_SCANCODE_1);
      }
      //handle alphabets
   }
   //unhandled keypress
   ASSERT(false);
#else
   LOGW("\nWARNING: Executing untested SDL method...\n");
   int nCode = SDL_GetScancodeFromName(string.c_str());
   ASSERT(nCode != SDL_SCANCODE_UNKNOWN);
   return nCode;
#endif
}

int PlayerControllerComponent::GetKeyCodeFromString(const std::string& string)
{
#if 0
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
#else
   LOGW("\nWARNING: Executing untested SDL method...\n");
   int code = SDL_GetKeyFromScancode((SDL_Scancode)GetScanCodeFromString(string));
   ASSERT(code != SDLK_UNKNOWN);
   return code;
#endif
}
//overrides
void PlayerControllerComponent::OnInitialise() {
   m_pTransformComponent = m_pEntityOwner->GetComponent<TransformComponent>();
   ASSERT(m_pTransformComponent);
   m_pAnimationComponent = m_pEntityOwner->GetComponent<AnimationComponent>();   //this could be null 
}
void PlayerControllerComponent::OnUpdate(double deltaTime)
{

#if 0
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
#else

   //To do: diagonal movement
   m_pTransformComponent->m_vVeloctiy.x = 0;
   m_pTransformComponent->m_vVeloctiy.y = 0;

   if (Engine::Input::GetKeyPressed(m_nKeyUp))
   {
      m_pTransformComponent->m_vVeloctiy = glm::vec2(0, m_vecVelocity.y);
      if (m_pAnimationComponent)
      {
         m_pAnimationComponent->SetCurrentAnimation(AnimationID::DirUp);
      }
   }
   else if (Engine::Input::GetKeyPressed(m_nKeyRight))
   {
      m_pTransformComponent->m_vVeloctiy = glm::vec2(m_vecVelocity.x, 0);
      if (m_pAnimationComponent)
      {
         m_pAnimationComponent->SetCurrentAnimation(AnimationID::DirRight);
      }
   }
   else if (Engine::Input::GetKeyPressed(m_nKeyDown))
   {
      m_pTransformComponent->m_vVeloctiy = glm::vec2(0, -m_vecVelocity.y);
      if (m_pAnimationComponent)
      {
         m_pAnimationComponent->SetCurrentAnimation(AnimationID::DirDown);
      }
   }
   else if (Engine::Input::GetKeyPressed(m_nKeyLeft))
   {
      m_pTransformComponent->m_vVeloctiy = glm::vec2(-m_vecVelocity.x, 0);
      if (m_pAnimationComponent)
      {
         m_pAnimationComponent->SetCurrentAnimation(AnimationID::DirLeft);
      }
   }
   else if (Engine::Input::GetKeyPressed(m_nKeyFire))
   {
      //To do: Fire projectiles here ?
   }

#endif
}