#pragma once

#include <unordered_map>

class EntityManager;

enum class AssetID : unsigned int
{
   Sprite_Tank = 0,

   SpriteSheet_Chopper,
   SpriteSheet_Radar
};

class AssetManager
{
public:
   AssetManager(EntityManager* pEntity);
   ~AssetManager();

   void ClearData();
   void AddTexture(AssetID assetID, const char* const path);
   SDL_Texture* GetTexture(AssetID id) const;


private:
   EntityManager* m_pEntityManager;
   std::unordered_map<AssetID, SDL_Texture*> m_umapTextures;
};