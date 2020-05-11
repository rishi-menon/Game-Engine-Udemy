
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

void PlayerControllerComponent::SetMovementControls(const std::string& up, const std::string& left, const std::string& down, const std::string& right)
{
   m_nKeyUp      =    GetScanCodeFromString (up);
   m_nKeyLeft    =    GetScanCodeFromString (left);
   m_nKeyDown    =    GetScanCodeFromString (down);
   m_nKeyRight   =    GetScanCodeFromString (right);
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
         //To do: the animation that is played should be controlled by the lua script perhaps ?
         m_pAnimationComponent->SetCurrentAnimation("up");
      }
   }
   else if (Engine::Input::GetKeyPressed(m_nKeyRight))
   {
      m_pTransformComponent->m_vVeloctiy = glm::vec2(m_vecVelocity.x, 0);
      if (m_pAnimationComponent)
      {
         m_pAnimationComponent->SetCurrentAnimation("right");
      }
   }
   else if (Engine::Input::GetKeyPressed(m_nKeyDown))
   {
      m_pTransformComponent->m_vVeloctiy = glm::vec2(0, -m_vecVelocity.y);
      if (m_pAnimationComponent)
      {
         m_pAnimationComponent->SetCurrentAnimation("down");
      }
   }
   else if (Engine::Input::GetKeyPressed(m_nKeyLeft))
   {
      m_pTransformComponent->m_vVeloctiy = glm::vec2(-m_vecVelocity.x, 0);
      if (m_pAnimationComponent)
      {
         m_pAnimationComponent->SetCurrentAnimation("left");
      }
   }
   else if (Engine::Input::GetKeyPressed(m_nKeyFire))
   {
      //To do: Fire projectiles here ?
   }

#endif
}

bool PlayerControllerComponent::SetValueTable(const sol::table& table)
{
   if (!Component::SetValueTable(table)) { ASSERT(false); return false; }

   sol::optional<sol::table> movementKeys = table["MovementKeys"];
   sol::optional<sol::table> velocity = table["Velocity"];
   if (!movementKeys || !velocity) { ASSERT(false); return false; }

   sol::optional<float> velocityX = velocity.value()["X"];
   sol::optional<float> velocityY = velocity.value()["Y"];
   if (!velocityX || !velocityY) { ASSERT(false); return false; }

   //the keys can either be written as a string or a number representing the keycode (same keycode that is internally stored in the class)
   sol::type typeFireKey = table["FireKey"].get_type();
   if (typeFireKey == sol::type::string)
   {
      std::string strFireKey = table["FireKey"];
      SetFireControl(strFireKey);
   }
   else if (typeFireKey == sol::type::number)
   {
      //See the note below regarding the cast
      m_nKeyFire = static_cast<int>((float)table["FireKey"]);
   }
   else { ASSERT(false); return false; }
   
   m_vecVelocity.x = velocityX.value();
   m_vecVelocity.y = velocityY.value();

   //the keys can either be written as a string or a number representing the keycode (same keycode that is internally stored in the class)
   {
      sol::type typeUp = movementKeys.value()["Up"].get_type();
      sol::type typeDown = movementKeys.value()["Down"].get_type();
      sol::type typeLeft = movementKeys.value()["Left"].get_type();
      sol::type typeRight = movementKeys.value()["Right"].get_type();

      bool bAllSame = (typeUp == typeDown && typeUp == typeLeft && typeUp == typeRight);
      if (!bAllSame) { ASSERT(false); return false; }

      if (typeUp == sol::type::string)
      {
         std::string up = movementKeys.value()["Up"];
         std::string down = movementKeys.value()["Down"];
         std::string left = movementKeys.value()["Left"];
         std::string right = movementKeys.value()["Right"];
         SetMovementControls(up, left, down, right);
      }
      else if (typeUp == sol::type::number)
      {
         //Lua rounds up while implicitly returning an int.. so 7.9 would become an 8 instead of a 7... The keycode should NEVER be a floating point number in the first place but its a safety check.
         m_nKeyUp =  static_cast<int>((float)movementKeys.value()["Up"]);
         m_nKeyDown = static_cast<int>((float)movementKeys.value()["Down"]);
         m_nKeyLeft = static_cast<int>((float)movementKeys.value()["Left"]);
         m_nKeyRight = static_cast<int>((float)movementKeys.value()["Right"]);
      }
      else { ASSERT(false); return false; }
   }
  

   return true;
}

std::string PlayerControllerComponent::SaveComponentToLua(const std::string& strSubTableName) const
{
   std::string strLua;
   strLua.reserve(100);
      
   strLua += StringR::Format("%s.Components.PlayerController = {\n", strSubTableName.c_str());
   strLua += Component::SaveComponentToLua();
   strLua += StringR::Format("\tMovementKeys = { Up = %d, Left = %d, Down = %d, Right = %d },\n", m_nKeyUp, m_nKeyLeft, m_nKeyDown, m_nKeyRight);
   strLua += StringR::Format("\tFireKey = %d,\n", m_nKeyFire);
   strLua += StringR::Format("\tVelocity = {X = %.1f, Y = %.1f}\n", m_vecVelocity.x, m_vecVelocity.y);
   strLua += '}';
   strLua += '\n';

   return strLua;
}