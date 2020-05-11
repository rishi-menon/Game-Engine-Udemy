
#include "pch.h"
#include "Font.h"
#include "Game/Game.h"

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

   //Currently this will take linear time in complexity for each tagId... This can be sped up by using a data structure (Might be worth considering if a lot of saving is being done)
   std::string Font::GetFontId() const
   {
      const std::unordered_map<std::string, Engine::Font*>& umap = Game::s_pAssetManager->GetFontMap();
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