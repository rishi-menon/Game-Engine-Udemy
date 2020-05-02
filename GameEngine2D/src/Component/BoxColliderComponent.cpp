
#include "pch.h"
#include "BoxColliderComponent.h"

#include "Entity/Entity.h"
#include "Game/Game.h"

BoxColliderComponent::BoxColliderComponent(const glm::vec2& offset, const glm::vec2& scale, const std::string& id) :
   m_vOffset (offset), m_vScale (scale),
   m_pTexture (nullptr),
   m_bDrawTexture (true)   //To do: change this to false eventually
{
   if (!id.empty())
   {
      m_pTexture = Game::s_pAssetManager->GetTexture(id);
      ASSERT(m_pTexture && m_pTexture->GetTexture());
      m_rectSource.x = 0;
      m_rectSource.y = 0;
      m_rectSource.w = m_pTexture->GetWidth();
      m_rectSource.h = m_pTexture->GetHeight();
      
   }
}
BoxColliderComponent::~BoxColliderComponent()
{
}

void BoxColliderComponent::OnInitialise()
{
   m_pTransformComponent = m_pEntityOwner->GetComponent<TransformComponent>();
   ASSERT(m_pTransformComponent);
}
void BoxColliderComponent::OnUpdate(double deltaTime)
{

}
void BoxColliderComponent::OnRender()
{
   if (m_pTexture && m_pTexture->GetTexture())
   {
      DrawCollisionBox();
   }
}

void BoxColliderComponent::GetRect(Engine::Rect& rect) const
{
   m_pTransformComponent->GetRect(rect);
   rect.Translate(m_vOffset.x, m_vOffset.y);
   rect.Scale(m_vScale.x, m_vScale.y);
}
Engine::Rect BoxColliderComponent::GetRect() const
{
   Engine::Rect rect;
   GetRect(rect);
   return rect;
}

void BoxColliderComponent::DrawCollisionBox()
{
   if (m_bDrawTexture)
   {
      ASSERT(m_pTexture && m_pTexture->GetTexture());

      SDL_Rect rectScreen;
      Game::s_camera.WorldRectToScreenRect(GetRect(), rectScreen);
      TextureManager::DrawTexture(m_pTexture->GetTexture(), m_rectSource, rectScreen, 0.0f, SDL_FLIP_NONE);
   }
}