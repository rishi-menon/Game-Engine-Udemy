
#include "pch.h"
#include "Font.h"

namespace Engine
{
   Font::Font(const char* const path, const int nSize) :
      m_nSize (nSize)
   {
      m_strPath = path;
      m_pFont = TTF_OpenFont(path, nSize);
      ASSERT(m_pFont);
   }
   Font::~Font()
   {
      TTF_CloseFont(m_pFont);
      m_pFont = nullptr;
   }
}