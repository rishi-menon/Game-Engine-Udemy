
#include "pch.h"
#include "BoxColliderComponent.h"

#include "Entity/Entity.h"
#include "Game/Game.h"

BoxColliderComponent::BoxColliderComponent(const std::string& colliderTag, const glm::vec2& offset, const glm::vec2& scale, const std::string& id) :
   m_vOffset (offset), m_vScale (scale),
   m_strTag (colliderTag),
   m_pTexture (nullptr),
   m_bDrawTexture (true)   //To do: change this to false eventually
{
#ifdef EX_2020_DRAW_FADED_BOX
   m_bDrawFadedBackground = false;
#endif

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

#ifdef EX_2020_DRAW_FADED_BOX
   if (m_bDrawTexture && m_bDrawFadedBackground)
   {
      ASSERT(m_pTexture && m_pTexture->GetTexture());

      SDL_Rect rectScreen;
      Game::s_camera.WorldRectToScreenRect(GetRect(), rectScreen);

      SDL_SetRenderDrawColor(Game::s_pRenderer, 90, 90, 90, 100);
      SDL_RenderFillRect(Game::s_pRenderer, &rectScreen);
   }
#endif // EX_2020_DRAW_FADED_BOX

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

#ifdef EX_2020_DRAW_FADED_BOX
void BoxColliderComponent::OnCollision(BoxColliderComponent& other)
{
   m_bDrawFadedBackground = true;
}
void BoxColliderComponent::OnCollisionExit(BoxColliderComponent& other)
{
   m_bDrawFadedBackground = false;
}
#endif