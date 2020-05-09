#pragma once

#include <lua/include/sol.hpp>

class Game;
class Map;
class Entity;
class EntityManager;
class Component;

namespace Engine::Lua
{
   extern bool LoadScene(Game& game, const std::string& srcFile);

   extern bool LoadAssets  (const sol::table& assetTable);
   extern bool LoadMap     (const sol::table& mapTable, Map& outMap);
   extern bool LoadCamera  (const sol::table& cameraTable, Entity*& outpEntityFollow, const EntityManager& manager);
   extern bool LoadAllEntities(const sol::table& entitiesTable, EntityManager& manager);

   extern bool CreateEntity(const sol::table& entityTable, EntityManager& manager);

   extern bool LoadComponentValues(Component* pComp, const sol::table& valuesTable);
}