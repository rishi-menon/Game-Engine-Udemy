#include "pch.h"
#include "AssetManager.h"
#include "Log/Log.h"

AssetManager::AssetManager()
{
   //reserve size to store the assets
   m_umapTextures.reserve(20);
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
}

void AssetManager::AddTexture(const std::string& key, const char* const path)
{
   Engine::Texture* pTexture = new Engine::Texture(path);
   if (!pTexture || !pTexture->GetTexture())
   {
      LOGW("Could not find texture (Path: \"%s\")", path);
      LOGW("\n");
   }
   ASSERT(pTexture && pTexture->GetTexture());
   m_umapTextures.insert({ key, pTexture });
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