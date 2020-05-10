#include "pch.h"
#include "FontManager.h"
#include "Game/Game.h"

namespace Engine {
   FontData::FontData(Engine::Font* pFont, const std::string& strText, const SDL_Color& col) :
      m_pFont(pFont), m_strText(strText), m_Color(col), m_bRegenerateTexture(true), m_pTexture(nullptr)
   {
   }
}

namespace Engine::FontManager
{
   Engine::Font* LoadFont(const char* const path, const int nSize)
   {
      Engine::Font* pFont = new Engine::Font(path, nSize);
      ASSERT(pFont);
      return pFont;
   }
    
   void DrawFont(::Engine::FontData& fontData, const SDL_Rect& rectDest)
   {
      //Regenerate the texture if necessary
      ASSERT(fontData.GetFont() && fontData.GetFont()->GetFont());
      if (!fontData.GetFont() || !fontData.GetFont()->GetFont())   return;
      if (fontData.m_bRegenerateTexture || !fontData.m_pTexture)
      {
         fontData.m_bRegenerateTexture = false;
         if (fontData.m_pTexture)
         {
            SDL_DestroyTexture(fontData.m_pTexture);
         }
         ASSERT(fontData.GetFont()->GetFont());
         SDL_Surface* pSurface = TTF_RenderText_Blended(fontData.GetFont()->GetFont(), fontData.GetText().c_str(), fontData.GetColor());
         ASSERT(pSurface);

         fontData.m_pTexture = SDL_CreateTextureFromSurface(Game::s_pRenderer, pSurface);
         SDL_FreeSurface(pSurface);
         ASSERT(fontData.m_pTexture);
      }

      //if rectSrc is null then it uses the entire texture
      SDL_RenderCopy(Game::s_pRenderer, fontData.m_pTexture, 0, &rectDest);
   }
}