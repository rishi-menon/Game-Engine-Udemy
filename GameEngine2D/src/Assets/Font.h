#pragma once

#include <SDL_ttf.h>

namespace Engine
{
   class Font
   {
   public:
      Font(const char* const path, const int nSize);
      ~Font();
      TTF_Font* GetTTFFont() const { return m_pFont; }
      int GetSize() const { return m_nSize; }
      const std::string& GetPath() const { return m_strPath; }

      std::string GetFontId() const;

   private:
      TTF_Font* m_pFont;
      int m_nSize;
      std::string m_strPath;
   };
}