#pragma once

#include "Entity/EntityManager.h"
#include "Assets/AssetManager.h"
#include "Collision/Rect.h"

struct MapData
{
   MapData() {}
   MapData(const std::string& mapPath, const std::string& mapAssetID, int tileSize, float StartPosX, float StartPosY, bool obstacles) :
      m_mapPath(mapPath),
      m_mapAssetID (mapAssetID),
      m_tileSize(tileSize),
      m_startPosX (StartPosX),
      m_startPosY (StartPosY),
      m_bObstacles (obstacles)
   {
   }
   std::string m_mapPath;
   std::string m_mapAssetID;
   int m_tileSize;
   float m_startPosX;
   float m_startPosY;

   bool m_bObstacles;
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

   const std::list<MapData>& GetMapData() const { return m_mapData; }

   void CheckCollision(float worldX, float worldY);

private:
   bool AddTile (EntityManager& manager, const MapData& mapData, float posx, float posy, int sourceX, int sourceY);
#if 0
   bool LoadTiles(EntityManager& manager, std::ifstream& file, const MapData& mapData, float& StartPosX, float& StartPosY);
#endif
private:
   EntityManager m_managerTiles;
   Engine::Rect m_rectTiles;  //Stores the world position of the Tiles Map
   
   std::list<MapData> m_mapData;
   std::unordered_map <int, bool> m_umapObstacles;
};