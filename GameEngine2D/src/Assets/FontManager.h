#pragma once

#include <SDL_ttf.h>
#include <SDL.h>
#include "Font.h"

namespace Engine
{
   class FontData;
}
namespace Engine::FontManager
{
   extern Engine::Font* LoadFont(const char* const path, const int nSize);
   extern void DrawFont(::Engine::FontData& fontData, const SDL_Rect& rectDest);
}

namespace Engine
{
   class FontData
   {
      friend void ::Engine::FontManager::DrawFont(FontData& fontData, const SDL_Rect& rectDest);

   public:
      FontData(Engine::Font* pFont = nullptr, const std::string& strText = "", const SDL_Color& col = { 255,255,255,255 });

      Engine::Font* GetFont()           const {  return m_pFont;   }
      const std::string& GetText()  const {  return m_strText; }
      const SDL_Color& GetColor()   const {  return m_Color;   }

      void SetFont (Engine::Font* pFont)         {  m_bRegenerateTexture = true; m_pFont = pFont;  }
      void SetText (const std::string& text) {  m_bRegenerateTexture = true; m_strText = text; }
      void SetColor (const SDL_Color& col )   { m_bRegenerateTexture = true; m_Color = col;    }

   private:
      Engine::Font*   m_pFont;
      std::string m_strText;
      SDL_Color   m_Color;

      //This caching is to prevent the texture from being created every single draw frame.
      bool m_bRegenerateTexture;
      SDL_Texture* m_pTexture;
   };
}
