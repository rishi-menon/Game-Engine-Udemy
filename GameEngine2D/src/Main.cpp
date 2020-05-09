
#include "pch.h"

#include "Constants.h"
#include "Game/Game.h"

//#ifdef __cplusplus
//extern "C"
//#endif

int main(int argc, char* argv[])
{
   LOG_INIT_PRINT(argc, argv);

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
      pGame->OnEndFrame();
   }

   pGame->OnDestroy();

   //Pause the program to see console output and to prevent console from closing. Only in debug builds obviously
   //LOG_PAUSE();
   LOG_TERMINATE();
   return 0;
}