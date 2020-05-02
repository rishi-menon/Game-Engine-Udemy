#include "pch.h"
#include "AssetManager.h"
#include "Log/Log.h"


AssetManager::AssetManager()
{
   //reserve size to store the assets
   m_umapTextures.reserve(20);
   m_umapFonts.reserve(5);
}

AssetManager::~AssetManager()
{
   ClearData();
}

void AssetManager::ClearData()
{
   //Free textures
   for (std::unordered_map<std::string, Engine::Texture*>::iterator it = m_umapTextures.begin();
      it != m_umapTextures.end(); it++)
   {
      ASSERT(it->second);
      delete (it->second);
   }
   m_umapTextures.clear();

   //Free fonts
   for (std::unordered_map<std::string, TTF_Font*>::iterator it = m_umapFonts.begin();
      it != m_umapFonts.end(); it++)
   {
      ASSERT(it->second);
      TTF_CloseFont(it->second);
   }
   m_umapFonts.clear();
}

void AssetManager::AddTexture(const std::string& key, const char* const path)
{
   Engine::Texture* pTexture = new Engine::Texture(path);
   if (!pTexture || !pTexture->GetTexture())
   {
      LOGW("Could not find texture (Path: \"%s\")\n", path);
   }
   ASSERT(pTexture && pTexture->GetTexture());
   m_umapTextures.emplace(key, pTexture);
}

void AssetManager::AddFont(const std::string& key, const char* const path, int nSize)
{
   TTF_Font* pFont = Engine::FontManager::LoadFont(path, nSize);
   ASSERT(pFont);
   if (!pFont)
   {
      LOGW("Could not load font at path %s (key: %s)\n", path, key.c_str());
   }
   m_umapFonts.emplace(key, pFont);
}
Engine::Texture* AssetManager::GetTexture(const std::string& key) const
{
   std::unordered_map<std::string, Engine::Texture*>::const_iterator it = m_umapTextures.find(key);

   if (it != m_umapTextures.end())
   {
      return it->second;
   }

   LOGW("Warning: Could not find asset %s", key);
   return nullptr;
}
TTF_Font* AssetManager::GetFont(const std::string& fontID) const
{
   std::unordered_map<std::string, TTF_Font*>::const_iterator it = m_umapFonts.find(fontID);
   if (it != m_umapFonts.end())
   {
      ASSERT(it->second);
      return it->second;
   }
   ASSERT(false);
   return nullptr;
}