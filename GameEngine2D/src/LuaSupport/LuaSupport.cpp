#include "pch.h"
#include "LuaSupport.h"

#include "Game/Game.h"
#include "TileMap/Map.h"
#include "Entity/EntityManager.h"

namespace Engine::Lua
{
   bool LoadScene(Game& game, const std::string& srcFile)
   {
      sol::state luaLevel;
      //sol::lib::package is for the 'require' keyword in lua
      luaLevel.open_libraries(sol::lib::base, sol::lib::os, sol::lib::math, sol::lib::package);
      
      try {
         luaLevel.script_file(srcFile);
      }
      catch (const std::exception& err)
      {
         printf(err.what());
         LOGW("\n");
         ASSERT(false);
         return false;
      }
      catch (...)
      {
         ASSERT(false);
         return false;
      }

   ////////////////////////////////////////////////////////////////////////
   //                   Start loading the scene                          //
   ////////////////////////////////////////////////////////////////////////
   //Load Assets...
      {
         sol::optional<sol::table> assetsTableExists = luaLevel["assets"];
         ASSERT(assetsTableExists);
         if (assetsTableExists && !LoadAssets(assetsTableExists.value()))  return false;
      }

      //Load Map...
      {
         sol::optional<sol::table> MapExists = luaLevel["map"];
         ASSERT(MapExists);
         if (MapExists && !LoadMap(MapExists.value(), game.m_map)) return false;
      }

      //Load Entities
      {
         sol::optional<sol::table> entitiesTable = luaLevel["entities"];
         ASSERT(entitiesTable);
         if (entitiesTable && !LoadAllEntities(entitiesTable.value(), Game::s_EntityManager)) return false;

      }

      //Load Camera (should be done after loading the entities).... The camera table in the lua file is completely optional and can be omitted
      Game::s_camera.SetViewRect(0, 0, 40);  //default camera view
      {
         sol::optional<sol::table> cameraTable = luaLevel["camera"];
         ASSERT(cameraTable);
         if (cameraTable && !LoadCamera(cameraTable.value(), game.m_pentityCameraFollow, Game::s_EntityManager))     return false;
      }
      return true;
   }

   ///////////////////////////////////////////////////////////////////////////////////////////////
   //                              Load Assets                                                  //
   ///////////////////////////////////////////////////////////////////////////////////////////////

   bool LoadAssets(const sol::table& assetTable)
   {
      //Load Textures
      {
         sol::optional tableTextures = assetTable["textures"];
         ASSERT(tableTextures != sol::nullopt);
         //assets count starts from 1 in the lua file
         if (tableTextures != sol::nullopt)
         {
            for (std::size_t nAssetCount = 1; true; nAssetCount++)
            {
               sol::optional<sol::table> tableExists = tableTextures.value()[nAssetCount];
               if (tableExists == sol::nullopt) break;

               sol::optional<std::string> strAssetId = tableExists.value()["Id"];
               sol::optional<std::string> strSource = tableExists.value()["Src"];
               if (strAssetId == sol::nullopt || strSource == sol::nullopt)
               {
                  ASSERT(false);
                  return false;  //something was wrong with the lua file
               }
               Game::s_pAssetManager->AddTexture(strAssetId.value().c_str(), strSource.value().c_str());
            }
         }
      }

      //Load Fonts
      {
         sol::optional tableFonts = assetTable["fonts"];
         ASSERT(tableFonts != sol::nullopt);
         if (tableFonts != sol::nullopt)
         {
            for (std::size_t nAssetCount = 1; true; nAssetCount++)
            {
               sol::optional<sol::table> tableExists = tableFonts.value()[nAssetCount];
               if (tableExists == sol::nullopt) break;

               sol::optional<std::string> strAssetId = tableExists.value()["Id"];
               sol::optional<std::string> strSource = tableExists.value()["Src"];
               sol::optional<int> nSize = tableExists.value()["Size"];

               if (strAssetId == sol::nullopt || strSource == sol::nullopt || nSize == sol::nullopt)
               {
                  ASSERT(false);
                  //something was wrong with the lua file
                  return false;
               }
               Game::s_pAssetManager->AddFont(strAssetId.value().c_str(), strSource.value().c_str(), nSize.value());
            }
         }
      }

      return true;
   }
   
   ///////////////////////////////////////////////////////////////////////////////////////////////
   //                              Load Map                                                     //
   ///////////////////////////////////////////////////////////////////////////////////////////////
   bool LoadMap(const sol::table& mapTable, Map& outMap)
   {
      sol::optional<std::string> strAssetId = mapTable["Id"];
      sol::optional<std::string> strSrc = mapTable["Src"];
      sol::optional<int> nTileSize = mapTable["TileSize"];
      sol::optional<float> fPosX = mapTable["PosX"];
      sol::optional<float> fPosY = mapTable["PosY"];

      if (strAssetId == sol::nullopt || strSrc == sol::nullopt || nTileSize == sol::nullopt || fPosX == sol::nullopt || fPosY == sol::nullopt)
      {
         ASSERT(false);
         //lua script is invalid
         return false;
      }

      outMap.LoadMap(strSrc.value(), strAssetId.value(), nTileSize.value(), fPosX.value(), fPosY.value());
      return true;
   }
   
   ///////////////////////////////////////////////////////////////////////////////////////////////
   //                              Load Camera                                                  //
   ///////////////////////////////////////////////////////////////////////////////////////////////
   bool LoadCamera(const sol::table& cameraTable, Entity*& outpEntityFollow, const EntityManager& manager)
   {
      sol::optional<float> fPosX = cameraTable["PosX"];
      sol::optional<float> fPosY = cameraTable["PosY"];
      if (!fPosX || !fPosY)
      {
         ASSERT(false);
         return false;
      }

      sol::optional<float> pixelsPerUnitOptional = cameraTable["PixelsPerUnit"];
      sol::optional<std::string> strFollowEntityOptional = cameraTable["FollowEntity"];

      float fPixelsPerUnit = (pixelsPerUnitOptional == sol::nullopt) ? 40.0f : pixelsPerUnitOptional.value();
      std::string strCameraFollowEntityName = (strFollowEntityOptional == sol::nullopt) ? "Player" : strFollowEntityOptional.value();

      Game::s_camera.SetViewRect(fPosX.value(), fPosY.value(), fPixelsPerUnit);
      outpEntityFollow = manager.GetEntityFromName(strCameraFollowEntityName);
      ASSERT(outpEntityFollow);
      return true;
   }

   ///////////////////////////////////////////////////////////////////////////////////////////////
   //                              Load Entities                                                //
   ///////////////////////////////////////////////////////////////////////////////////////////////
   bool LoadAllEntities(const sol::table& entitiesTable, EntityManager& manager)
   {
      Engine::Lua::CreateEntity(entitiesTable[1], manager);
      return true;
   }

   ///////////////////////////////////////////////////////////////////////////////////////////////
   //                              Load Components                                              //
   ///////////////////////////////////////////////////////////////////////////////////////////////
   //HELPER FUNCTION
   //If the component does not exist in the table then function returns true
   //If the component was added and loaded successfully then the function returns true
   //If the component was added but could not be loaded properly then the function returns false
   template <typename T>
   static bool LoadComponent(Entity* pEntity, const sol::table& componentsTable, const std::string& strComponentName)
   {
      ASSERT(pEntity);
      sol::optional<sol::table> component = componentsTable[strComponentName];
      if (component == sol::nullopt)   return true;   //Component does not exist in the list of component

      Component* pComp = pEntity->AddComponent<T>();
      ASSERT(pComp);
      if (!pComp) return false;

      bool bSuccess = pComp->SetValueTable(component.value());
      ASSERT(bSuccess);
      return bSuccess;
   }

   bool CreateEntity(const sol::table& entityTable, EntityManager& manager)
   {
      sol::optional<std::string> strEntityName = entityTable["Name"];
      sol::optional<bool> bIsEnabled = entityTable["Enabled"];

      ASSERT(strEntityName != sol::nullopt); //delete later .. The name in the lua file is optional

      Entity* pEntity = new Entity ();
      ASSERT(pEntity);
      if (!pEntity)  return false;

      if (strEntityName)  pEntity->SetName(strEntityName.value());
      if (bIsEnabled)     pEntity->SetIsActive(bIsEnabled.value());
      
      /////////////////////////////////////////////////////////////////////   
      //                      Add Components                             //
      bool bSuccess = true;

      sol::optional<sol::table> componentsTableOptional = entityTable["Components"];
      if (componentsTableOptional)
      {
         sol::table& compTable = componentsTableOptional.value();
         bSuccess = bSuccess && LoadComponent<TransformComponent>(pEntity, compTable, "Transform");
         bSuccess = bSuccess && LoadComponent<TransformUIComponent>(pEntity, compTable, "TransformUI");
         bSuccess = bSuccess && LoadComponent<SpriteComponent>(pEntity, compTable, "Sprite");
         bSuccess = bSuccess && LoadComponent<AnimationComponent>(pEntity, compTable, "Animation");
         bSuccess = bSuccess && LoadComponent<BoxColliderComponent>(pEntity, compTable, "BoxCollider");
         bSuccess = bSuccess && LoadComponent<PlayerControllerComponent>(pEntity, compTable, "PlayerController");
         bSuccess = bSuccess && LoadComponent<SelfDestructComponent>(pEntity, compTable, "SelfDestruct");
         bSuccess = bSuccess && LoadComponent<UITextComponent>(pEntity, compTable, "TextUI");
         bSuccess = bSuccess && LoadComponent<EnemyMovementScript>(pEntity, compTable, "EnemyMovementScript");
      }

      //Safety check... Check if all the components in the lua file were added or not
#if DEBUG
      if (componentsTableOptional && bSuccess)
      {
         int nLuaComponentCount = 0;
         for (auto& pair : componentsTableOptional.value())
         {
            nLuaComponentCount++;
         }
         int nComponentCount = pEntity->GetComponentsMap().size();
         ASSERT(nComponentCount == nLuaComponentCount);
      }
#endif // DEBUG


      if (bSuccess)
      {
         //All the components were added successfully
         manager.AddEntity(pEntity);
         pEntity->OnInitialise();
         return true;
      }
      else
      {
         LOGW("Error: Could not create entity \"%s\"", pEntity->GetName().c_str());
         ASSERT(false);
         delete pEntity;
         return false;
      }
   }
}