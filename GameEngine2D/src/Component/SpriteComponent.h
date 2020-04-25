#pragma once

#include <SDL.h>

#include "TextureManager.h"
#include "AssetManager.h"

#include "TransformComponent.h"

class AnimationComponent;

class SpriteComponent : public Component
{
   friend class AnimationComponent;
public:
   COMPONENT_TYPE(Sprite);
   SpriteComponent(AssetID id, int width, int height);
   ~SpriteComponent();
   //overrides
   virtual void OnInitialise() override;
   virtual void OnUpdate(double deltaTime) override;
   virtual void OnRender() override;

   void SetTexture(AssetID id);
   
public:
   SDL_RendererFlip m_SpriteFlip;
private:
   SDL_Texture* m_pTexture;
   SDL_Rect m_rectSource;
   SDL_Rect m_rectDestination;

   TransformComponent* m_pTransformComponent;
   int m_nTextureWidth;    //In Pixels
   int m_nTextureHeight;   //In Pixels

   double m_dRotationDeg;  //rotation of the texture in degrees
};
