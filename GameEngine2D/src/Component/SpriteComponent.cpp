#include "pch.h"
#include "SpriteComponent.h"
#include "TransformComponent.h"

#include "Game/Game.h"
#include "Entity/Entity.h"

#include "TextureManager.h"

SpriteComponent::SpriteComponent(AssetID id, int width, int height) :
   m_SpriteFlip (SDL_FLIP_NONE),
   m_pTexture (nullptr),
   m_pTransformComponent (nullptr),
   m_nTextureWidth (width),
   m_nTextureHeight (height),
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
   m_pTransformComponent = m_pEntityOwner->GetComponent<TransformComponent>();
   ASSERT(m_pTransformComponent);   //this should exist

   m_rectSource.x = 0;
   m_rectSource.y = 0;
   m_rectSource.w = m_nTextureWidth;
   m_rectSource.h = m_nTextureHeight;
}

void SpriteComponent::OnUpdate(double deltaTime)
{
   m_rectDestination.x = static_cast<int>(m_pTransformComponent->m_vPosition.x);
   m_rectDestination.y = static_cast<int>(m_pTransformComponent->m_vPosition.y);
   m_rectDestination.w = static_cast<int>(m_pTransformComponent->m_vScale.x);
   m_rectDestination.h = static_cast<int>(m_pTransformComponent->m_vScale.y);
}
void SpriteComponent::OnRender()
{
   TextureManager::DrawTexture(m_pTexture, m_rectSource, m_rectDestination, m_dRotationDeg, m_SpriteFlip);
}
