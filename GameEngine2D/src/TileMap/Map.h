#pragma once

#include "Entity/EntityManager.h"
#include "Assets/AssetManager.h"
#include "Collision/Rect.h"

struct MapData
{
   MapData() {}
   MapData(const std::string& mapPath, const std::string& mapAssetID, int tileSize, float StartPosX, float StartPosY) :
      m_mapPath(mapPath),
      m_mapAssetID (mapAssetID),
      m_tileSize(tileSize),
      m_startPosX (StartPosX),
      m_startPosY (StartPosY)
   {
   }
   std::string m_mapPath;
   std::string m_mapAssetID;
   int m_tileSize;
   float m_startPosX;
   float m_startPosY;

};
class Map
{
public:
   Map();
   ~Map();

   bool LoadMap(const MapData& mapData);
   
   void OnUpdate(double deltaTime);
   void OnRender();
   //void OnDestroy();

   const Engine::Rect& GetRectMap() const { return m_rectTiles; }

   EntityManager& GetManager() { return m_managerTiles; }

   const MapData& GetMapData() const { return m_mapData; }
private:
   void AddTile (EntityManager& manager, const MapData& mapData, float posx, float posy, int sourceX, int sourceY);
   bool LoadTiles(EntityManager& manager, std::ifstream& file, const MapData& mapData, float& StartPosX, float& StartPosY);

private:
   EntityManager m_managerTiles;
   Engine::Rect m_rectTiles;  //Stores the world position of the Tiles Map
   
   MapData m_mapData;
};