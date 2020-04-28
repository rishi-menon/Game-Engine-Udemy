#include "pch.h"
#include "SpriteComponent.h"
#include "Transform/TransformComponent.h"
#include "Transform/TransformUIComponent.h"

#include "Game/Game.h"
#include "Entity/Entity.h"

#include "TextureManager.h"

SpriteComponent::SpriteComponent(AssetID id) :
   m_SpriteFlip (SDL_FLIP_NONE),
   m_pTexture (nullptr),
   m_rectSource {0, 0, 0, 0},
   m_rectDestination {0, 0, 0, 0},
   m_pPartialTransformComponent(nullptr),
   m_dRotationDeg (0.0)
{
   SetTexture(id);
}
SpriteComponent::~SpriteComponent()
{

}
void SpriteComponent::SetTexture(AssetID id)
{
   m_pTexture = Game::s_pAssetManager->GetTexture(id);
   ASSERT(m_pTexture);
}

void SpriteComponent::OnInitialise()
{
   ASSERT(m_pEntityOwner); //VERY bad if this fails
   m_pPartialTransformComponent = m_pEntityOwner->GetComponent<TransformPartialComponent>();
   ASSERT(m_pPartialTransformComponent);   //this should exist
   m_TransformType = m_pPartialTransformComponent->GetSubType();

   ASSERT(m_pTexture);
   m_rectDefault.x = 0;
   m_rectDefault.y = 0;
   m_rectDefault.w = m_pTexture->GetWidth();
   m_rectDefault.h = m_pTexture->GetHeight();
   ResetSourceRect();
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
   if (m_TransformType == ComponentSubType::TransformWorld)
   {
      Game::s_camera.WorldTransformToScreenRect(*static_cast<TransformComponent*>(m_pPartialTransformComponent), m_rectDestination);
   }
   else if (m_TransformType == ComponentSubType::TransformUI)
   {
      Game::s_camera.WorldTransformToScreenRect(*static_cast<TransformUIComponent*>(m_pPartialTransformComponent), m_rectDestination);
   }
   TextureManager::DrawTexture(m_pTexture->GetTexture(), m_rectSource, m_rectDestination, m_dRotationDeg, m_SpriteFlip);
}
