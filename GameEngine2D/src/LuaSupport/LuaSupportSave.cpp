#include "pch.h"
#include "LuaSupport.h"
#include <fstream>

#include "Assets/AssetManager.h"
#include "Game/Game.h"

namespace Engine::Lua
{
   //the person calls this funcion does not have to worry about extensions... Just call it with "Assets\scene" and "Level1"...
   bool SaveScene(Game& game, const std::string& strFolderName, const std::string& strFileName)
   {

      std::string filePath;
      if (!strFolderName.empty())
      {
         filePath += strFolderName + "\\";
      }
      filePath += strFileName + ".lua";
      std::fstream file;
      file.open(filePath, std::fstream::out | std::fstream::trunc);
      if (!file.is_open())   return false;

      file << SaveAssetsLua(*Game::s_pAssetManager);
      file << SaveMapLua(game.m_map);
      file << SaveCameraLua(Game::s_camera, &game);

      //Get All Entities
      const std::list<Entity*>& list = Game::s_EntityManager.GetEntitiesList();
      std::size_t nIndex = 1; //In lua arrays start from 1 by default
      file << "\nentities = {}\n";
      for (Entity* pEntity : list)
      {
         ASSERT(pEntity);
         if (pEntity)
         {
            std::stringstream strTableName;

            strTableName << "entities[" << nIndex <<']';  //Eg: entities[1]
            std::string str = pEntity->SaveEntityLuaScene(strTableName.str());
            file << str;
            nIndex++;
         }
      }

      file.close();
      return true;
   }

   std::string SaveAssetsLua(const AssetManager& assetManager)
   {
      const std::unordered_map<std::string, Engine::Texture*>& textureMap = assetManager.GetTextureMap();
      const std::unordered_map<std::string, Engine::Font*>& fontMap = assetManager.GetFontMap();

      if (!textureMap.size() && !fontMap.size()) return ""; //both are empty

#if 0
      std::stringstream ss;
      ss << "\nassets = {\n";
      bool bFirstAsset = true;   //first table doesnt end with a comma (or in other words all the succeeding tables start with a comma)

      //Textures
      if (textureMap.size())
      {
         ss << "\t";
         if (!bFirstAsset)    ss << ',';
         bFirstAsset = false;

         ss<<"textures = { \n";
         auto it = textureMap.begin();
         //{   Id = "tank-big-right",       Src = "assets\\images\\tank-big-right.png"        }
         ASSERT(it->second);
         ss << "\t\t{ Id = \"" << StringR::ParsePath(it->first) << "\", Src = \"" << StringR::ParsePath(it->second->GetPath()) << "\" }\n";
         it++;
         for (; it != textureMap.end(); it++)
         {
            ss << "\t\t,{ Id = \"" << StringR::ParsePath(it->first) << "\", Src = \"" << StringR::ParsePath(it->second->GetPath()) << "\" }\n";
         }
         ss << "\t}\n"; //closing bracket of textures
      }

      //Fonts
      if (fontMap.size())
      {
         ss << "\t";
         if (!bFirstAsset)    ss << ',';
         bFirstAsset = false;

         ss<< "fonts = {\n";

         //{ Id = "charriot",      Src = "assets\\fonts\\charriot.ttf",      Size = 100 }
         auto it = fontMap.begin();
         ASSERT(it->second);
         ss << "\t\t{ Id = \"" << StringR::ParsePath(it->first) << "\", Src = \"" << StringR::ParsePath(it->second->GetPath()) << "\", Size = " << it->second->GetSize() << " }\n";

         it++;
         for (; it != fontMap.end(); it++)
         {
            ss << "\t\t,{ Id = \"" << StringR::ParsePath(it->first) << "\", Src = \"" << StringR::ParsePath(it->second->GetPath()) << "\", Size = " << it->second->GetSize() << " }\n";
         }

         ss << "\t}\n"; //closing bracket of fonts
      }

      ss << "}\n";  //closing bracket of assets
      return ss.str();
#else
      std::stringstream ss;
      ss << "\nassets = {\n";

      //Textures
      if (textureMap.size())
      {
         ss << "\ttextures = { \n";

         for (auto& pair : textureMap)
         {
            ASSERT(pair.second);
            ss << StringR::Format("\t\t{ Id = \"%s\", Src = \"%s\" },\n", StringR::ParsePath(pair.first).c_str(), StringR::ParsePath(pair.second->GetPath()).c_str());
         }
         ss << "\t},\n"; //closing bracket of textures
      }

      //Fonts
      if (fontMap.size())
      {
         ss << "\tfonts = {\n";
         //{ Id = "charriot",      Src = "assets\\fonts\\charriot.ttf",      Size = 100 }
         for (auto& pair : fontMap)
         {
            ASSERT(pair.second);
            ss << StringR::Format("\t\t{ Id = \"%s\", Src = \"%s\", Size = %d },\n", StringR::ParsePath(pair.first).c_str(), StringR::ParsePath(pair.second->GetPath()).c_str(), pair.second->GetSize());
         }
         ss << "\t}\n"; //closing bracket of fonts
      }

      ss << "}\n";  //closing bracket of assets
      return ss.str();
#endif

   }

   std::string SaveMapLua(const Map& map)
   {
      const MapData& data = map.GetMapData();
      std::stringstream ss;
      ss << "\nmap = {\n";
      ss << "\tId = \"" << StringR::ParsePath(data.m_mapAssetID) << "\",\n";
      ss << "\tSrc = \"" << StringR::ParsePath(data.m_mapPath) << "\",\n";
      ss << "\tTileSize = " << data.m_tileSize<< ",\n";
      ss << "\tPosX = " << data.m_startPosX << ",\n";
      ss << "\tPosY = " << data.m_startPosY << "\n";

      ss << "}\n";//closing bracket for map
      return ss.str();
   }

   std::string SaveCameraLua(const Camera& camera, const Game* pGame)
   {
/*
   PosX = 0.0,                              --Starting coordinates (World)
   PosY = 0.0,                              --Starting coordinates (World)
   PixelsPerUnit = 40.0,
*/
      std::stringstream ss;
      ss << "\ncamera = {\n";

      ss << "\tPosX = " << camera.GetPositionX() << ",\n";
      ss << "\tPosY = " << camera.GetPositionY() << ",\n";
      ss << "\tPixelsPerUnit = " << camera.GetPixelsPerUnit() << ",\n";
      ss << "\tFollowEntity = \"";
      if (pGame && pGame->GetCameraFollow())
      {
         std::string strr = pGame->GetCameraFollow()->GetName();
         ss << StringR::ParsePath(pGame->GetCameraFollow()->GetName());
      }
      ss << "\"\n";  //closing double quote for the camera follow entity name
      ss << "}\n";   //closing bracket for camera table
      return ss.str();
   }
}