#pragma once

#include "Entity/EntityManager.h"
#include "Assets/AssetManager.h"
#include "Camera/Rect.h"

class Map
{
public:
   Map();
   ~Map();

   bool LoadMap(const char* const mapPath, AssetID mapAssetID, int tileSize, float StartPosX, float StartPosY);
   
   void OnUpdate(double deltaTime);
   void OnRender();
   void OnDestroy();

   const Engine::Rect& GetRectMap() const { return m_rectTiles; }
private:
   void AddTile (EntityManager& manager, AssetID id, float posx, float posy, int sourceX, int sourceY);
   bool LoadTiles(EntityManager& manager, std::ifstream& file, AssetID id, float& StartPosX, float& StartPosY);

private:
   EntityManager m_managerTiles;
   int m_nTileTextureSize;
   Engine::Rect m_rectTiles;  //Stores the world position of the Tiles Map
};