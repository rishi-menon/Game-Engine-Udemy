#include "pch.h"
#include "Map.h"

#include <fstream>
#include <string>

#include "Component/Transform/TransformComponent.h"
#include "Component/SpriteComponent.h"

#include "Game/Game.h"

static const float fTileSizeWorldUnits = 2.0f;

Map::Map() :
   m_nTileTextureSize(0),
   m_rectTiles ()
{
}
Map::~Map()
{

}


bool Map::LoadMap(const char* const mapPath, const std::string& mapAssetID, int tileSize, float StartPosX, float StartPosY)
{
   int nOldTileSize = m_nTileTextureSize;
   m_nTileTextureSize = tileSize;

   bool bSuccess = true;
   float currentPosX = StartPosX;
   float currentPosY = StartPosY;
   //Keep Adding new objects to the manager and if the map fails for any reason then dont use it... If it succeeds then store this manager in the memeber variable
   EntityManager manager;

   std::ifstream file;
   file.open(mapPath);

   if (!file.is_open() || file.eof()) { bSuccess = false; }

   if (bSuccess)
   {
      static const int nSkipCharacters = 1000;
      char buffer[100];
      file.ignore(nSkipCharacters, ':');
      file.getline(buffer, 100);

      bSuccess = bSuccess && (!StringR::strcmpi(buffer, "Tiles"));   //strcmpi returns 0 when the strings are the same

      //This is taking advantage of short circuit evaluation. DO NOT write it as &= as that would not perform short circuit evaluation.
      bSuccess = bSuccess && LoadTiles(manager, file, mapAssetID, currentPosX, currentPosY);

      //read other stuff if required

      file.close();
   }
   ASSERT(bSuccess);
   if (bSuccess)
   {
      m_managerTiles = std::move(manager);

      m_rectTiles.SetRectPoints(StartPosX - fTileSizeWorldUnits /2.0f, StartPosY + fTileSizeWorldUnits / 2.0f, currentPosX - fTileSizeWorldUnits / 2.0f, currentPosY + fTileSizeWorldUnits / 2.0f);
      return true;
   }
   else
   {
      m_nTileTextureSize = nOldTileSize;
      return false;
   }

}

//PosX, PosY are the start coordinates of creating the map... If the map succeds then it stores the x and y position of the last tile
bool Map::LoadTiles(EntityManager& manager, std::ifstream& file, const std::string& id, float& PosX, float& PosY)
{ 
   float currentPosX = PosX, currentPosY = PosY;
   //if two consecutive endline characters are encountered then break
   bool bEndLine = false;
   char cRead;
   bool bSuccess = true;

   float fLastTilePosX;

   while (bSuccess)
   {
      //Digit 1
      file.get(cRead);
      if (bEndLine && cRead == ':')  { file.unget(); break; }
      if (bEndLine && cRead == '\n') { break; }
      if (!isdigit(cRead) || file.eof()) { bSuccess = false; break; }
      int nSourceY = static_cast<int>(cRead - '0');

      //Digit 2
      file.get(cRead);
      if (!isdigit(cRead) || file.eof()) { bSuccess = false; break; }
      int nSourceX = static_cast<int>(cRead - '0');

      AddTile(manager, id, currentPosX, currentPosY, nSourceX, nSourceY);

      file.get(cRead);
      if (file.eof()) { /*For consistencey...*/ fLastTilePosX = currentPosX; currentPosY -= fTileSizeWorldUnits; break; }
      bEndLine = false;
      switch (cRead)
      {
         case ',':
            currentPosX += fTileSizeWorldUnits;
            break;
         case '\n':
            bEndLine = true;
            fLastTilePosX = currentPosX;
            currentPosX = PosX;
            currentPosY -= fTileSizeWorldUnits;
            break;
         default:
            bSuccess = false;
            break;
      }
   }

   if (bSuccess)
   {
      //stores the x and y position of the last tile
      PosX = fLastTilePosX;
      PosY = currentPosY + fTileSizeWorldUnits; //one extra gets subtracted as there might be another line in the file
      return true;
   }
   return false;
}

void Map::AddTile(EntityManager& manager, const std::string& id, float posx, float posy, int sourceX, int sourceY)
{
#if defined (WINDOWS) && defined (DEBUG)
   char name[20];
   static int count = 0;
   sprintf_s(name, 20, "TileMap %d", count);
   count++;
   Entity& entity = manager.AddEntity(name);
#else
   Entity& entity = manager.AddEntity("TileMap");
#endif // WINDOWS

   const int temp = 1;
   entity.AddComponent<TransformComponent>(glm::vec2{ posx, posy}, glm::vec2{ 0,0 }, glm::vec2{ fTileSizeWorldUnits, fTileSizeWorldUnits });
   SpriteComponent& comp = *entity.AddComponent<SpriteComponent>(id);

   entity.OnInitialise();

   SDL_Rect rect;
   rect.x = sourceX * m_nTileTextureSize;
   rect.y = sourceY * m_nTileTextureSize;
   rect.w = m_nTileTextureSize;
   rect.h = m_nTileTextureSize;
   comp.SetSourceRect(rect);
}

void Map::OnUpdate(double deltaTime)
{
   m_managerTiles.OnUpdate(deltaTime);
}
void Map::OnRender()
{
   m_managerTiles.OnRender();
}
//void Map::OnDestroy()
//{
//   m_managerTiles.OnDestroy();
//}