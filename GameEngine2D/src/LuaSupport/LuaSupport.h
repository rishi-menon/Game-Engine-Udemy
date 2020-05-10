#pragma once

#include <lua/include/sol.hpp>

class Game;
class Map;
class Entity;
class EntityManager;
class Component;
class AssetManager;

namespace Engine::Lua
{
   //Load scene stuff
   extern bool LoadScene(Game& game, const std::string& srcFile);
   extern bool LoadAssets  (const sol::table& assetTable);
   extern bool LoadMap     (const sol::table& mapTable, Map& outMap);
   extern bool LoadCamera  (const sol::table& cameraTable, Entity*& outpEntityFollow, const EntityManager& manager);
   extern bool LoadAllEntities(const sol::table& entitiesTable, EntityManager& manager);
   extern bool CreateEntity(const sol::table& entityTable, EntityManager& manager);
   extern bool LoadComponentValues(Component* pComp, const sol::table& valuesTable);

   //save scene stuff
   extern bool SaveScene(Game& game, const std::string& srcFile, std::string& outString);
   extern std::string GetAssets(const AssetManager& assetManager);
}