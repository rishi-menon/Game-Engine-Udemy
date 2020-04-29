#pragma once
#include <glm/glm.hpp>

namespace Engine::Input
{
   extern void OnProcessInput();

   extern void GetMousePos(int& outX, int& outY);
   extern void GetMousePos(glm::vec2& outVecPos);
   extern glm::vec2 GetMousePos();

   extern bool GetKeyPressed(int SDLScanCode);
}