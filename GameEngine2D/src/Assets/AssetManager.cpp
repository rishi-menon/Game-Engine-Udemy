#include "pch.h"
#include "AssetManager.h"
#include "Log/Log.h"

AssetManager::AssetManager(/*EntityManager* pManager*/)
   //m_pEntityManager(pManager)
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
   for (std::unordered_map<AssetID, Engine::Texture*>::iterator it = m_umapTextures.begin();
      it != m_umapTextures.end(); it++)
   {
      ASSERT(it->second);
      delete (it->second);
      
   }
   m_umapTextures.clear();
}

void AssetManager::AddTexture(AssetID assetID, const char* const path)
{
   Engine::Texture* pTexture = new Engine::Texture(path);
   ASSERT(pTexture && pTexture->GetTexture());
   if (!pTexture || !pTexture->GetTexture())
   {
      LOGW("Could not find texture (ID: %d, Asset Folder: \"%s\")", assetID, path);
      LOGW("\n");
   }
   m_umapTextures.insert({ assetID, pTexture });
}
Engine::Texture* AssetManager::GetTexture(AssetID id) const
{
   std::unordered_map<AssetID, Engine::Texture*>::const_iterator it = m_umapTextures.find(id);

   if (it != m_umapTextures.end())
   {
      return it->second;
   }

   LOGW("Warning: Could not find asset %d", static_cast<unsigned int>(id));
   return nullptr;
}