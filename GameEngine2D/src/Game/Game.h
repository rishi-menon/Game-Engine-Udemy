#pragma once

#include "AssetManager.h"

class Game
{
public:
   Game();
   ~Game();

   inline bool GetIsRunning() const { return m_bIsRunning; }

   void Initialise(const unsigned int unWidth, const unsigned int unHeight);
   void OnProcessInput();
   void OnUpdate();
   void OnRender();
   void OnDestroy();

   void LoadLevel(int nLevelNumber);

   static SDL_Renderer* s_pRenderer;
   static AssetManager* s_pAssetManager;
   static SDL_Event s_event;

private:
   void DoUpdate(double deltaTime);
private:
   bool m_bIsRunning;
   Uint32 m_nLastUpdateTick;

   SDL_Window* m_pWindow;

};