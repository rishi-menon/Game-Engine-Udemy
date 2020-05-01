#pragma once
#include "TextureManager.h"

namespace Engine {
   class Texture
   {
   public:
      Texture(const char* const path);
      ~Texture();

      inline SDL_Texture* GetTexture() const { return m_pTexture; }
      inline int          GetWidth()   const { return m_nWidth;   }
      inline int          GetHeight()  const { return m_nHeight;  }

   private:
      SDL_Texture* m_pTexture;
      int m_nWidth;
      int m_nHeight;
   };
}