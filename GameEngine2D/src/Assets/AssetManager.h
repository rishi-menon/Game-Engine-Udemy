#pragma once

#include <unordered_map>
#include "Texture.h"

class EntityManager;

enum class AssetID : unsigned int
{
   Sprite_Tank = 0,

   SpriteSheet_Chopper,
   SpriteSheet_Radar,

   Tilemap_ocean
};

class AssetManager
{
public:
   AssetManager(/*EntityManager* pEntity*/);
   ~AssetManager();

   void ClearData();
   void AddTexture(AssetID assetID, const char* const path);
   Engine::Texture* GetTexture(AssetID id) const;


private:
   //EntityManager* m_pEntityManager;
   std::unordered_map<AssetID, Engine::Texture*> m_umapTextures;
};