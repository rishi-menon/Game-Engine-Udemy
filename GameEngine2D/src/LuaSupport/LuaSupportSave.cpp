#include "pch.h"
#include "LuaSupport.h"
#include <fstream>

#include "Assets/AssetManager.h"

namespace Engine::Lua
{
   //the person calls this funcion does not have to worry about extensions... Just call it with "Assets\scene" and "Level1"...
   bool SaveScene(Game& game, const std::string& strFolderName, const std::string& strFileName, std::string& outString)
   {
      std::string filePath = strFolderName + "\\" + strFileName + ".lua";
      std::fstream file;
      file.open(filePath, std::fstream::out|std::fstream::trunc);
      if (!file.is_open())   return false;

      std::string strData;
      
   }

   std::string GetAssets(const AssetManager& assetManager)
   {
      const std::unordered_map<std::string, Engine::Texture*>& textureMap = assetManager.GetTextureMap();
      const std::unordered_map<std::string, Engine::Font*>& fontMap = assetManager.GetFontMap();

      if (!textureMap.size() && !fontMap.size()) return ""; //both are empty
      std::stringstream ss;
      ss << "assets = {\n";
      bool bFirstAsset = true;   //first table doesnt end with a comma (or in other words all the succeeding tables start with a comma)

      if (textureMap.size())
      {
         if (!bFirstAsset)    ss << ',';
         bFirstAsset = false;

         ss << "textures = {";
         for (auto& pair : textureMap)
         {

         }
         ss << "}"; //closing bracket of textures
      }

      ss << "}\n\n";  //closing bracket of assets
      return "";
   }

}