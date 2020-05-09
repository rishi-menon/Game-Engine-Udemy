#include "pch.h"
#include "SpriteComponent.h"
#include "Transform/TransformComponent.h"
#include "Transform/TransformUIComponent.h"

#include "Game/Game.h"
#include "Entity/Entity.h"

#include "Assets/TextureManager.h"

//Do NOT use this constructor... It is only for creating components from a lua script.
SpriteComponent::SpriteComponent() :
   m_SpriteFlip(SDL_FLIP_NONE),
   m_pTexture(nullptr),
   m_rectSource{ 0, 0, 0, 0 },
   m_rectDestination{ 0, 0, 0, 0 },
   m_rectDefault{ 0, 0, 0, 0 },

   m_pPartialTransformComponent(nullptr),
   m_TransformComponentType(ComponentType::None),
   m_dRotationDeg(0.0)
{
}
SpriteComponent::SpriteComponent(const std::string& id) :
   m_SpriteFlip (SDL_FLIP_NONE),
   m_pTexture (nullptr),
   m_rectSource {0, 0, 0, 0},
   m_rectDestination {0, 0, 0, 0},
   m_rectDefault {0, 0, 0, 0},

   m_pPartialTransformComponent(nullptr),
   m_TransformComponentType (ComponentType::None),
   m_dRotationDeg (0.0)
{
   SetTexture(id);
   
   ASSERT(m_pTexture && m_pTexture->GetTexture());

   //m_rectSource.w = m_pTexture->GetWidth();
   //m_rectSource.h = m_pTexture->GetHeight();

   m_rectDefault.w = m_pTexture->GetWidth();
   m_rectDefault.h = m_pTexture->GetHeight();
   ResetSourceRect();
}
SpriteComponent::~SpriteComponent()
{

}
void SpriteComponent::SetTexture(const std::string& id)
{
   m_pTexture = Game::s_pAssetManager->GetTexture(id);
   ASSERT(m_pTexture && m_pTexture->GetTexture());
}

void SpriteComponent::OnInitialise()
{
   ASSERT(m_pEntityOwner); //VERY bad if this fails
   
   ComponentsMap map;
   if (m_pEntityOwner->GetComponentsGeneric(GenericComponent::TransformPartial, map))
   {
      ASSERT(map.size() == 1);
      m_TransformComponentType = map.begin()->first;;
      ASSERT(map.begin()->second->size());
      m_pPartialTransformComponent = static_cast<TransformPartialComponent*>(map.begin()->second->at(0));
   }
   else
   {
      ASSERT(false);
   }
   ASSERT(m_pPartialTransformComponent);   //this should exist
}

void SpriteComponent::OnUpdate(double deltaTime)
{
   //m_rectDestination.x = static_cast<int>(m_pTransformComponent->m_vPosition.x - m_pTransformComponent->m_vScale.x/2);
   //m_rectDestination.y = static_cast<int>(m_pTransformComponent->m_vPosition.y - m_pTransformComponent->m_vScale.y/2);
   //m_rectDestination.w = static_cast<int>(m_pTransformComponent->m_vScale.x);
   //m_rectDestination.h = static_cast<int>(m_pTransformComponent->m_vScale.y);
}
void SpriteComponent::OnRender()
{
   if (m_TransformComponentType == ComponentType::Transform)
   {
      Game::s_camera.WorldTransformToScreenRect(*static_cast<TransformComponent*>(m_pPartialTransformComponent), m_rectDestination);
   }
   else if (m_TransformComponentType == ComponentType::TransformUI)
   {
      Game::s_camera.WorldTransformToScreenRect(*static_cast<TransformUIComponent*>(m_pPartialTransformComponent), m_rectDestination);
   }
   else
   {
      return;
   }
   TextureManager::DrawTexture(m_pTexture->GetTexture(), m_rectSource, m_rectDestination, m_dRotationDeg, m_SpriteFlip);
}

bool SpriteComponent::SetValueTable(const sol::table& table)
{
   
   sol::optional<std::string> textureId = table["Id"];
   ASSERT(textureId != sol::nullopt);
   if (textureId == sol::nullopt)   return false;

   SetTexture(textureId.value());

   ASSERT(m_pTexture && m_pTexture->GetTexture());

   m_rectDefault.w = m_pTexture->GetWidth();
   m_rectDefault.h = m_pTexture->GetHeight();

   sol::optional<sol::table> defaultRect = table["TextureDefaultRect"];
   if (defaultRect != sol::nullopt)
   {
      sol::optional<int> x = defaultRect.value()["x"];
      sol::optional<int> y = defaultRect.value()["y"];
      sol::optional<int> w = defaultRect.value()["w"];
      sol::optional<int> h = defaultRect.value()["h"];
      ASSERT(x != sol::nullopt && y != sol::nullopt && w != sol::nullopt && h != sol::nullopt);
      if (x && y && w && h)
      {
         m_rectDefault = SDL_Rect{ x.value(), y.value(), w.value(), h.value() };
      }
   }
   ResetSourceRect();

   return true;
}