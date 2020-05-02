#pragma once

namespace TextureManager
{
   extern SDL_Texture* LoadTexture(const char* const fileName);

   extern void DrawTexture(SDL_Texture* pTexture, const SDL_Rect& rectSource, const SDL_Rect& rectDest, const double dAngleDeg, const SDL_RendererFlip flip);

   extern void DeleteTexture(SDL_Texture*& pTexture);
}