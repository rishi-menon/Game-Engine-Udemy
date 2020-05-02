
#include "pch.h"
#include "TextureManager.h"
#include "Game/Game.h"

namespace TextureManager
{
   //To do: what do these functions actually do rishi
   extern SDL_Texture* LoadTexture(const char* const fileName)
   {
      SDL_Surface* surface = IMG_Load(fileName);
      SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::s_pRenderer, surface);
      SDL_FreeSurface(surface);
      return texture;
   }

   extern void DrawTexture(SDL_Texture* pTexture, const SDL_Rect& rectSource, const SDL_Rect& rectDest, const double dAngleDeg, const SDL_RendererFlip flip)
   {
      //To do: what do these functions actually do rishi
      SDL_RenderCopyEx(Game::s_pRenderer, pTexture, &rectSource, &rectDest, dAngleDeg, nullptr, flip);
   }

   extern void DeleteTexture(SDL_Texture*& pTexture)
   {
      SDL_DestroyTexture(pTexture);
      pTexture = nullptr;
   }
}