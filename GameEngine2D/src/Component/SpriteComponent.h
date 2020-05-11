#pragma once

#include <SDL.h>

#include "Assets/TextureManager.h"
#include "Assets/AssetManager.h"

#include "Transform/TransformComponent.h"

class AnimationComponent;

class SpriteComponent : public Component
{
   friend class AnimationComponent;
   
public:
   COMPONENT_TYPE(Sprite);
   COMPONENT_NAME("Sprite");

   SpriteComponent();
   SpriteComponent(const std::string& id);
   ~SpriteComponent();
   //overrides
   virtual void OnInitialise() override;
   virtual void OnUpdate(double deltaTime) override;
   virtual void OnRender() override;

   void SetTexture(const std::string& id);
   void SetSourceRect(const SDL_Rect& rect) { m_rectSource = rect; }
   void ResetSourceRect() { m_rectSource = m_rectDefault; }

   inline int GetWidth()  const { ASSERT(m_pTexture); return m_pTexture->GetWidth();  }
   inline int GetHeight() const { ASSERT(m_pTexture); return m_pTexture->GetHeight(); }

   //lua stuff
   virtual bool SetValueTable(const sol::table& table) override;
   virtual std::string SaveComponentToLua(const std::string& strSubTableName) const override;

public:
   SDL_RendererFlip m_SpriteFlip;
   SDL_Rect m_rectDefault;
private:
   Engine::Texture* m_pTexture;
   SDL_Rect m_rectSource;
   SDL_Rect m_rectDestination;

   //The sprite component could be attached to a gameobject with a world transform or it could be a UI element
   TransformPartialComponent* m_pPartialTransformComponent; 
   ComponentType m_TransformComponentType;

   //delete later:
   //int m_nTextureWidth;    //In Pixels
   //int m_nTextureHeight;   //In Pixels

   double m_dRotationDeg;  //rotation of the texture in degrees
};
