#include "pch.h"
#include "AssetManager.h"
#include "TextureManager.h"
#include "Log/Log.h"

AssetManager::AssetManager(EntityManager* pManager) :
   m_pEntityManager(pManager)
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
   for (std::unordered_map<AssetID, SDL_Texture*>::iterator it = m_umapTextures.begin();
      it != m_umapTextures.end(); it++)
   {
      ASSERT(it->second);
      TextureManager::DeleteTexture(it->second);
   }
   m_umapTextures.clear();
}

void AssetManager::AddTexture(AssetID assetID, const char* const path)
{
   SDL_Texture* pTexture = TextureManager::LoadTexture(path);
   ASSERT(pTexture);
   m_umapTextures.insert({ assetID, pTexture });
}
SDL_Texture* AssetManager::GetTexture(AssetID id) const
{
   std::unordered_map<AssetID, SDL_Texture*>::const_iterator it = m_umapTextures.find(id);

   if (it != m_umapTextures.end())
   {
      return it->second;
   }

   LOGW("Warning: Could not find asset %d", static_cast<unsigned int>(id));
   return nullptr;
}