#pragma once

#include <unordered_map>
#include "Texture.h"
#include <SDL_ttf.h>

#include <string>
#include "FontManager.h"

class EntityManager;


class AssetManager
{
public:
   AssetManager();
   ~AssetManager();

   void ClearData();
   void AddTexture(const std::string& key , const char* const path);
   void AddFont(const std::string& key , const char* const path, int nSize);

   Engine::Texture* GetTexture(const std::string& key) const;
   TTF_Font* GetFont(const std::string& fontID) const;



private:
   std::unordered_map<std::string, Engine::Texture*> m_umapTextures;
   std::unordered_map<std::string, TTF_Font*> m_umapFonts;
};