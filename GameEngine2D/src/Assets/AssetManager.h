#pragma once

#include <unordered_map>
#include "Texture.h"
#include <string>

class EntityManager;


class AssetManager
{
public:
   AssetManager();
   ~AssetManager();

   void ClearData();
   void AddTexture(const std::string& key , const char* const path);
   Engine::Texture* GetTexture(const std::string& key) const;


private:
   std::unordered_map<std::string, Engine::Texture*> m_umapTextures;
};