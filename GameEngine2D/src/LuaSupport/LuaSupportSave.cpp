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
      file.open(filePath, std::fstream::out|std::fstream::trunc);
      if (!file.is_open())   return false;

      file << GetAssets(*Game::s_pAssetManager);
      file << GetMap(game.m_map);

      file.close();
      return true;
   }

   std::string GetAssets(const AssetManager& assetManager)
   {
      const std::unordered_map<std::string, Engine::Texture*>& textureMap = assetManager.GetTextureMap();
      const std::unordered_map<std::string, Engine::Font*>& fontMap = assetManager.GetFontMap();

      if (!textureMap.size() && !fontMap.size()) return ""; //both are empty
      std::stringstream ss;
      ss << "\nassets = {\n";
      bool bFirstAsset = true;   //first table doesnt end with a comma (or in other words all the succeeding tables start with a comma)

      //Textures
      if (textureMap.size())
      {
         if (!bFirstAsset)    ss << ',';
         bFirstAsset = false;

         ss << "\ttextures = {\n";
         auto it = textureMap.begin();
         //{   Id = "tank-big-right",       Src = "assets\\images\\tank-big-right.png"        }
         ASSERT(it->second);
         ss << "\t\t{ Id = \"" << it->first << "\", src = \"" << it->second->GetPath() << "\" }\n";
         it++;
         for (; it != textureMap.end(); it++)
         {
            ss << "\t\t,{ Id = \"" << it->first << "\", src = \"" << it->second->GetPath() << "\" }\n";
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
         ss << "\t\t{ Id = \"" << it->first << "\", Src = \"" << it->second->GetPath() << "\", Size = " << it->second->GetSize() << " }\n";

         it++;
         for (; it != fontMap.end(); it++)
         {
            ss << "\t\t,{ Id = \"" << it->first << "\", Src = \"" << it->second->GetPath() << "\", Size = " << it->second->GetSize() << " }\n";
         }

         ss << "\t}\n"; //closing bracket of fonts
      }

      ss << "}\n\n";  //closing bracket of assets
      return ss.str();
   }

   std::string GetMap(const Map& map)
   {
      const MapData& data = map.GetMapData();
      std::stringstream ss;
      ss << "\nmap = {\n";
      ss << "\tId = \"" << data.m_mapAssetID << "\",\n";
      ss << "\tSrc = \"" << data.m_mapPath << "\",\n";
      ss << "\tTileSize = " << data.m_tileSize<< ",\n";
      ss << "\tPosX = " << data.m_startPosX << ",\n";
      ss << "\tPosY = " << data.m_startPosY << "\n";

      ss << "}";//closing bracket for map
      return ss.str();
   }
}