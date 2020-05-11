#pragma once

#include <lua/include/sol.hpp>

class Game;
class Map;
class Entity;
class EntityManager;
class Component;
class AssetManager;
class Camera;

namespace Engine::Lua
{
   //Load scene stuff
   extern bool LoadScene(Game& game, const std::string& srcFile);
   extern bool LoadAssets  (const sol::table& assetTable);
   extern bool LoadMap     (const sol::table& mapTable, Map& outMap);
   extern bool LoadCamera  (const sol::table& cameraTable, Camera& camera, Game* game);
   extern bool LoadAllEntities(const sol::table& entitiesTable, EntityManager& manager);
   extern bool CreateEntity(const sol::table& entityTable, EntityManager& manager);

   //save scene stuff
   extern bool SaveScene(Game& game, const std::string& strFolderName, const std::string& strFileName);
   extern std::string SaveAssetsLua(const AssetManager& assetManager);
   extern std::string SaveMapLua(const Map& map);
   extern std::string SaveCameraLua(const Camera& camera, const Game* pGame);
}