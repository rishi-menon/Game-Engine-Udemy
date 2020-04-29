#include "pch.h"
#include "InputManager.h"

namespace Engine::Input
{
   static const Uint8* keyboardState = nullptr;

   extern void OnProcessInput()
   {
      keyboardState = SDL_GetKeyboardState(nullptr);
   }
   extern void GetMousePos(int& outX, int& outY) {
      SDL_GetMouseState(&outX, &outY);
   }
   extern void GetMousePos(glm::vec2& outVecPos)
   {
      int x, y;
      GetMousePos(x, y);
      outVecPos.x = static_cast<float>(x);
      outVecPos.y = static_cast<float>(y);
   }
   extern glm::vec2 GetMousePos()
   {
      glm::vec2 vecPos;
      GetMousePos(vecPos);
      return vecPos;
   }

   extern bool GetKeyPressed (int SDLScanCode)
   {
      ASSERT(keyboardState);
      return keyboardState[SDLScanCode];
   }
}