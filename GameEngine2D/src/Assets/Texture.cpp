#include "pch.h"
#include "Texture.h"

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
}