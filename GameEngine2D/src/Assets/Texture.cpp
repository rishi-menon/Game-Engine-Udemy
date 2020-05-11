#include "pch.h"
#include "Texture.h"

#include "Game/Game.h"

namespace Engine
{
   Texture::Texture(const char* const path) :
      m_nWidth(0),
      m_nHeight(0)
   {
      m_strPath = path;
      m_pTexture = TextureManager::LoadTexture(path);
      ASSERT(m_pTexture);
      SDL_QueryTexture(m_pTexture, 0, 0, &m_nWidth, &m_nHeight);
      ASSERT(m_nWidth && m_nHeight);
   }
   Texture::~Texture()
   {
      TextureManager::DeleteTexture(m_pTexture);
   }

   //Currently this will take linear time in complexity for each tagId... This can be sped up by using a data structure (Might be worth considering if a lot of saving is being done)
   std::string Texture::GetTextureId() const
   {
      const std::unordered_map<std::string, Engine::Texture*>& umap = Game::s_pAssetManager->GetTextureMap();
      for (auto& pair : umap)
      {
         ASSERT(pair.second);
         if (this == pair.second && pair.second)
         {
            ASSERT(pair.first.size());
            return pair.first;   //return the ID
         }
      }

      ASSERT(false);
      return "";
   }
}