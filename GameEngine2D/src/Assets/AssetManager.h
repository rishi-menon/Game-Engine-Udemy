#pragma once

#include <unordered_map>
#include "Texture.h"
#include "Font.h"

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
   Engine::Font* GetFont(const std::string& fontID) const;

   const std::unordered_map<std::string, Engine::Texture*>& GetTextureMap() const { return m_umapTextures; }
   const std::unordered_map<std::string, Engine::Font*>& GetFontMap() const { return m_umapFonts; }

private:
   std::unordered_map<std::string, Engine::Texture*> m_umapTextures;
   std::unordered_map<std::string, Engine::Font*> m_umapFonts;
};