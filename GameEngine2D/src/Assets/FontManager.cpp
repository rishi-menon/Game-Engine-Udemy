#include "pch.h"
#include "FontManager.h"
#include "Game/Game.h"

namespace Engine {
   FontData::FontData(TTF_Font* pFont, const std::string& strText, const SDL_Color& col) :
      m_pFont(pFont), m_strText(strText), m_Color(col), m_bRegenerateTexture(true), m_pTexture(nullptr)
   {
   }
}

namespace Engine::FontManager
{
   TTF_Font* LoadFont(const char* const path, const int nSize)
   {
      TTF_Font* pFont = TTF_OpenFont(path, nSize);
      ASSERT(pFont);
      return pFont;
   }
    
   void DrawFont(::Engine::FontData& fontData, const SDL_Rect& rectDest)
   {
      //Regenerate the texture if necessary
      if (fontData.m_bRegenerateTexture || !fontData.GetFont())
      {
         fontData.m_bRegenerateTexture = false;
         if (fontData.m_pTexture)
         {
            SDL_DestroyTexture(fontData.m_pTexture);
         }
         ASSERT(fontData.GetFont());
         SDL_Surface* pSurface = TTF_RenderText_Blended(fontData.GetFont(), fontData.GetText().c_str(), fontData.GetColor());
         ASSERT(pSurface);

         fontData.m_pTexture = SDL_CreateTextureFromSurface(Game::s_pRenderer, pSurface);
         SDL_FreeSurface(pSurface);
         ASSERT(fontData.m_pTexture);
      }

      //if rectSrc is null then it uses the entire texture
      SDL_RenderCopy(Game::s_pRenderer, fontData.m_pTexture, 0, &rectDest);
   }
}