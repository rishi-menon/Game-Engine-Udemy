#pragma once

#include "Assets/AssetManager.h"
#include "Camera/Camera.h"
#include "TileMap/Map.h"

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
   static Camera s_camera;

private:
   void DoUpdate(double deltaTime);
   void MoveCamera(double deltaTime);
private:
   bool m_bIsRunning;
   Uint32 m_nLastUpdateTick;

   Map m_map;
   Entity* m_pentityCameraFollow;

   SDL_Window* m_pWindow;
};