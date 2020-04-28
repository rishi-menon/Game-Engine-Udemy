#include "pch.h"
#include "Game.h"
#include "Constants.h"

#include "Entity/EntityManager.h"

//Components
#include "Component/Transform/TransformComponent.h"
#include "Component/Transform/TransformUIComponent.h"
#include "Component/SpriteComponent.h"
#include "Component/AnimationComponent.h"
#include "Component/PlayerControllerComponent.h"

EntityManager g_EntityManager;   //To do: temporary global EntityManager... Move to static class member maybe ?

SDL_Renderer* Game::s_pRenderer = 0;
AssetManager* Game::s_pAssetManager = new AssetManager ();
SDL_Event     Game::s_event;
Camera        Game::s_camera;

Game::Game() :
   m_bIsRunning (false),
   m_nLastUpdateTick (0),
   m_pentityCameraFollow(nullptr),
   m_pWindow(nullptr)
{
   LOGW("Initialising Game");
}
Game::~Game()
{
}

void Game::MoveCamera(double deltaTime)
{
   ASSERT(m_pentityCameraFollow);
   TransformComponent* comp = m_pentityCameraFollow->GetComponent<TransformComponent>();
   ASSERT(comp);

   //Value should be between 0 and 1... low values mean a greater lag
   const float fCameraSpeed = 1.3f;
   float fCameraPercent = static_cast<float>(MathR::Clamp01(fCameraSpeed * deltaTime));
   float fCameraDeltaX = static_cast<float>(MathR::Lerp(0.0f, comp->m_vPosition.x - s_camera.GetPositionX(), fCameraPercent));
   float fCameraDeltaY = static_cast<float>(MathR::Lerp(0.0f, comp->m_vPosition.y - s_camera.GetPositionY(), fCameraPercent));

   {
      float fMinDeltaX = m_map.GetRectMap().GetLeft() - s_camera.GetRectView().GetLeft(); //this is the maximum you can translate toward the left
      float fMaxDeltaX = m_map.GetRectMap().GetRight() - s_camera.GetRectView().GetRight();//this is the maximum you can translate toward the right
      fCameraDeltaX = static_cast<float>(MathR::Clamp(fCameraDeltaX, fMinDeltaX, fMaxDeltaX));
   }
   {
      float fMinDeltaY = m_map.GetRectMap().GetBottom() - s_camera.GetRectView().GetBottom();//this is the maximum you can translate toward the bottom edge
      float fMaxDeltaY = m_map.GetRectMap().GetTop() - s_camera.GetRectView().GetTop();//this is the maximum you can translate toward the top edge of the map
      fCameraDeltaY = static_cast<float>(MathR::Clamp(fCameraDeltaY, fMinDeltaY, fMaxDeltaY));
   }
   s_camera.TranslateViewRect(fCameraDeltaX, fCameraDeltaY);
   //To do: clamp the camera's position so that it doesnt go out of the map
}

void Game::LoadLevel(int nLevelNumber)
{
   //Create assets
   s_pAssetManager->AddTexture(AssetID::Sprite_Tank,         "assets\\images\\tank-big-right.png");
   s_pAssetManager->AddTexture(AssetID::SpriteSheet_Chopper, "assets\\images\\chopper-spritesheet.png");
   s_pAssetManager->AddTexture(AssetID::SpriteSheet_Radar,   "assets\\images\\radar.png");
   s_pAssetManager->AddTexture(AssetID::Tilemap_ocean,       "assets\\tilemaps\\jungle.png");

   //Load Tilemap
   m_map.LoadMap("assets/tilemaps/jungle.map", AssetID::Tilemap_ocean, 32, -15, 15);

   //Create Entitys and add components
   {
      Entity& entity = g_EntityManager.AddEntity("Tank");
      entity.AddComponent<TransformComponent>(glm::vec2{ 0,0 }, glm::vec2{ 0, -1 }, glm::vec2{ 1, 1 });
      entity.AddComponent<SpriteComponent>(AssetID::Sprite_Tank);
   }
   {
      Entity& entity = g_EntityManager.AddEntity("Chopper");
      m_pentityCameraFollow = &entity;

      entity.AddComponent<TransformComponent>(glm::vec2{ -14,0 }, glm::vec2{ 0, 0 }, glm::vec2{ 1, 1 });
      entity.AddComponent<SpriteComponent>(AssetID::SpriteSheet_Chopper);
      
      AnimationComponent& component = entity.AddComponent<AnimationComponent>();
      component.SetGridCoords(2, 4);
      const float fSpeed = 17; //animation frames per second
      component.AddAnimation(AnimationID::DirDown, AnimationLayout({ 0, 1 }, fSpeed));
      component.AddAnimation(AnimationID::DirRight, AnimationLayout({ 2, 3 }, fSpeed));
      component.AddAnimation(AnimationID::DirLeft, AnimationLayout({ 4, 5 }, fSpeed));
      component.AddAnimation(AnimationID::DirUp, AnimationLayout({ 6, 7 }, fSpeed));
      component.SetCurrentAnimation(AnimationID::DirDown);

      PlayerControllerComponent& compController = entity.AddComponent<PlayerControllerComponent>();
      compController.SetMovementControls("w", "a", "s", "d");
      const float speed = 4;
      compController.m_vecVelocity = glm::vec2(speed, speed );
      
   }
   {
      Entity& entity = g_EntityManager.AddEntity("Radar");
      const float dimension = 64.0f;
      entity.AddComponent<TransformUIComponent>(glm::vec2{ 0.95f, 0.05f }, glm::vec2{ dimension, dimension });
      SpriteComponent& sprite = entity.AddComponent<SpriteComponent>(AssetID::SpriteSheet_Radar);
      sprite.m_rectDefault = SDL_Rect{ 0,0,64,64 };
      sprite.ResetSourceRect();

      AnimationComponent& component = entity.AddComponent<AnimationComponent>();
      const double dRotationSpeed = 150;   //in deg per sec
      component.SetGridCoords(1, 1);
      //use the default animation.. aka AnimationType::None
      component.SetRotationSpeed(dRotationSpeed);
   }
   LOG_ALL_ENTITIES(g_EntityManager);

}

void Game::Initialise(const unsigned int unWidth, const unsigned int unHeight)
{
   //returns 0 on successful init
   if (SDL_Init(SDL_INIT_EVERYTHING))
   {
      LOGW("Error: Could not initialise SDL\n");
      ASSERT(false);
      return;
   }

   m_pWindow = SDL_CreateWindow(
         "",
         SDL_WINDOWPOS_CENTERED,
         SDL_WINDOWPOS_CENTERED,
         unWidth,
         unHeight,
         SDL_WINDOW_BORDERLESS
      );

   ASSERT(m_pWindow);
   if (!m_pWindow) { LOGW("Error: Could not create a window"); return; }

   if (!s_pRenderer)
   {
      s_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
      ASSERT(s_pRenderer);
      if (!s_pRenderer) { LOGW("Error: Could not create a renderer"); return; }
   }
   else
   {
      //Two Game were created ? This is bad... Currently the renderer is static
      LOGW("Error: Multiple Games were created");
      ASSERT(false);
      return;
   }


   //Everthing went well
   s_camera.SetDimensions(unWidth, unHeight);
   //const int a = 32
   s_camera.SetViewRect(0, 0, 40);

   LoadLevel(0);

   m_bIsRunning = true;
}
void Game::OnProcessInput()
{
   SDL_PollEvent(&s_event);
   switch (s_event.type)
   {
      case SDL_QUIT:
      {
         m_bIsRunning = false;
         break;
      }
      case SDL_KEYDOWN:
      {
         if (s_event.key.keysym.sym == SDLK_ESCAPE)
         {
            m_bIsRunning = false;
         }
         break;
      }
      default:
      {
         break;
      }
   }
}

void Game::OnUpdate()
{
   //time in milliseconds since sdl was initialised
   Uint32 nCurrentTick = SDL_GetTicks();

   //delta time is in milliseconds
   double deltaTime = static_cast<float>(nCurrentTick - m_nLastUpdateTick);
   m_nLastUpdateTick = nCurrentTick;

   //cap out deltatime in case it becomes too high (during debugging and breakpoints)
   const float fMaxDeltaTime = 50.0f;  //50 milliseconds which is 20 fps

   if (deltaTime < g_cTargetFrameDeltaTime)
   {
      //Onupdate is running too fast (faster than g_cTargetFPS). Wait for a few frames so that DoUpdate function gets called a maximum of targetFPS times

      SDL_Delay(static_cast<Uint32>(g_cTargetFrameDeltaTime - deltaTime));
   } 
   else if (deltaTime >= fMaxDeltaTime) 
   {
      //DeltaTime is too big...
      LOG_LINE_BREAK();
#ifdef DEBUG
      std::stringstream ss;
      ss << "DeltaTime was too large: " << deltaTime << " ms";
      LOGW(ss.str().c_str());
#endif // DEBUG
      deltaTime = fMaxDeltaTime;
      LOG_LINE_BREAK();
   }

   //Alright, NOW you can finally start doing update stuff
   DoUpdate(deltaTime / 1000.0);
}

void Game::DoUpdate(double deltaTime)
{
   //deltaTime is in seconds
   //In this function, you don't have to worry about frame rate and all that. Do your update here

   m_map.OnUpdate(deltaTime);
   g_EntityManager.OnUpdate(deltaTime);
   
   //move the camera after all the game objects have updated their positions
   if (m_pentityCameraFollow)
   {
      MoveCamera(deltaTime);
   }
}
void Game::OnRender()
{
   SDL_SetRenderDrawColor(s_pRenderer, 20, 20, 20, 255);
   SDL_RenderClear(s_pRenderer);

   m_map.OnRender();
   
   if (g_EntityManager.IsEmpty())
   {
      return;
   }
   g_EntityManager.OnRender();

   SDL_RenderPresent(s_pRenderer);
}
void Game::OnDestroy()
{

   delete s_pAssetManager;

   //SDL stuff
   SDL_DestroyRenderer(s_pRenderer);
   s_pRenderer = nullptr;
   SDL_DestroyWindow(m_pWindow);
   m_pWindow = nullptr;
   SDL_Quit();

}