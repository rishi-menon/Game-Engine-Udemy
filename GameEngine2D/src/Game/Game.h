#pragma once

#include "Assets/AssetManager.h"
#include "Camera/Camera.h"
#include "TileMap/Map.h"

#include <lua/include/sol.hpp>

class Game;
namespace Engine::Lua {
   bool LoadScene(Game& game, const std::string& srcFile);
   bool SaveScene(Game& game, const std::string& strFolderName, const std::string& strFileName);
}
class Game
{
   friend bool Engine::Lua::LoadScene(Game& game, const std::string& srcFile);
   friend bool Engine::Lua::SaveScene(Game& game, const std::string& strFolderName, const std::string& strFileName);
public:
   Game();
   ~Game();

   inline bool GetIsRunning() const { return m_bIsRunning; }

   void Initialise(const unsigned int unWidth, const unsigned int unHeight);
   void OnProcessInput();
   void OnUpdate();
   void OnRender();
   void OnEndFrame();   //Gets called at the end of the game loop... for cleanup mainly
   void OnDestroy();

   bool LoadLevel(int nLevelNumber);

   static EntityManager s_EntityManager;
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