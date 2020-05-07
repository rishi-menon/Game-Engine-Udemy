#pragma once

#include "Entity/EntityManager.h"
#include "Assets/AssetManager.h"
#include "Collision/Rect.h"

class Map
{
public:
   Map();
   ~Map();

   bool LoadMap(const char* const mapPath, const std::string& mapAssetID, int tileSize, float StartPosX, float StartPosY);
   
   void OnUpdate(double deltaTime);
   void OnRender();
   //void OnDestroy();

   const Engine::Rect& GetRectMap() const { return m_rectTiles; }

   EntityManager& GetManager() { return m_managerTiles; }
private:
   void AddTile (EntityManager& manager, const std::string& id, float posx, float posy, int sourceX, int sourceY);
   bool LoadTiles(EntityManager& manager, std::ifstream& file, const std::string& id, float& StartPosX, float& StartPosY);

private:
   EntityManager m_managerTiles;
   int m_nTileTextureSize;
   Engine::Rect m_rectTiles;  //Stores the world position of the Tiles Map
};