#include "pch.h"

#include "Constants.h"
#include "Game/Game.h"

//#ifdef __cplusplus
//extern "C"
//#endif

int main(int argc, char* argv[])
{

   Game* pGame = new Game;
   ASSERT(pGame);
   if (!pGame)
   {
      return -1;
   }
   // Game was created successfully
   pGame->Initialise(g_cWindowWidth, g_cWindowHeight);
   while (pGame->GetIsRunning())
   {
      pGame->OnProcessInput();
      pGame->OnUpdate();
      pGame->OnRender();
   }

   pGame->OnDestroy();

   //Pause the program to see console output and to prevent console from closing. Only in debug builds obviously
   LOG_PAUSE();
   return 0;
}