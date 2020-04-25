#include "pch.h"
#include "Game.h"
#include "Constants.h"

#include "Entity/EntityManager.h"

//Components
#include "Component/TransformComponent.h"
#include "Component/SpriteComponent.h"
#include "Component/AnimationComponent.h"
#include "Component/PlayerControllerComponent.h"

EntityManager g_EntityManager;   //To do: temporary global EntityManager... Move to static class member maybe ?

SDL_Renderer* Game::s_pRenderer = 0;
AssetManager* Game::s_pAssetManager = new AssetManager(&g_EntityManager);
SDL_Event     Game::s_event;

Game::Game() :
   m_bIsRunning (false),
   m_pWindow(nullptr),
   m_nLastUpdateTick (0)
{
   LOG("Initialising Game", Log::Trace);
}
Game::~Game()
{
}

void Game::LoadLevel(int nLevelNumber)
{
   //Create assets
   s_pAssetManager->AddTexture(AssetID::Sprite_Tank,         "assets/images/tank-big-right.png");
   s_pAssetManager->AddTexture(AssetID::SpriteSheet_Chopper, "assets/images/chopper-spritesheet.png");
   s_pAssetManager->AddTexture(AssetID::SpriteSheet_Radar,   "assets/images/radar.png");
   //Create Entitys and add components
   {
      Entity& entity = g_EntityManager.AddEntity("Tank");
      entity.AddComponent<TransformComponent>(glm::vec2{ 40,0 }, glm::vec2{ 0, 10 }, glm::vec2{ 32, 32 });
      entity.AddComponent<SpriteComponent>(AssetID::Sprite_Tank, 32, 32);
   }
   {
      Entity& entity = g_EntityManager.AddEntity("Chopper");
      entity.AddComponent<TransformComponent>(glm::vec2{ 70,0 }, glm::vec2{ 0, 0 }, glm::vec2{ 32, 32 });
      entity.AddComponent<SpriteComponent>(AssetID::SpriteSheet_Chopper, 64, 128);
      
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
      const float speed = 150;
      compController.m_vecVelocity = glm::vec2(speed, speed);
      
   }
   {
      Entity& entity = g_EntityManager.AddEntity("Radar");
      entity.AddComponent<TransformComponent>(glm::vec2{ 150,50 }, glm::vec2{ 0, 0 }, glm::vec2{ 64, 64 });
      entity.AddComponent<SpriteComponent>(AssetID::SpriteSheet_Radar, 64, 64);

      AnimationComponent& component = entity.AddComponent<AnimationComponent>();
      const double dRotationSpeed = 150;   //in deg per sec
      component.SetGridCoords(1, 1);
      //use the default animation.. aka AnimationType::None
      //component.AddAnimation(AnimationID::Default, AnimationLayout({ 0,1,2,3,4,5,6,7 }, 10));
      //component.SetCurrentAnimation(AnimationID::Default);
      component.SetRotationSpeed(dRotationSpeed);
   }
   LOG_ALL_ENTITIES(g_EntityManager);

}

void Game::Initialise(const unsigned int unWidth, const unsigned int unHeight)
{
   //returns 0 on successful init
   if (SDL_Init(SDL_INIT_EVERYTHING))
   {
      LOG("Error: Could not initialise SDL", Log::Error);
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
   if (!m_pWindow) { return; }

   if (!s_pRenderer)
   {
      s_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
      ASSERT(s_pRenderer);
      if (!s_pRenderer) { return; }
   }
   else
   {
      //Two Game were created ? This is bad... Currently the renderer is static
      ASSERT(false);
   }

   LoadLevel(0);

   //Everthing went well
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
      LOG(ss.str().c_str(), Log::Trace);
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
   
   g_EntityManager.OnUpdate(deltaTime);
}
void Game::OnRender()
{
   SDL_SetRenderDrawColor(s_pRenderer, 20, 20, 20, 255);
   SDL_RenderClear(s_pRenderer);
   
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