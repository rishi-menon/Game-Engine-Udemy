
#include "pch.h"
#include "BoxColliderComponent.h"

#include "Entity/Entity.h"
#include "Game/Game.h"

BoxColliderComponent::BoxColliderComponent() :
   m_vOffset(0.0f,0.0f), m_vScale(0.0f, 0.0f),
   m_strTag(""),
   m_pTexture(nullptr),
   m_rectSource(SDL_Rect{ 0,0,0,0 }),
   m_bDrawTexture(true)   //To do: change this to false eventually
{
#ifdef EX_2020_DRAW_FADED_BOX
   m_bDrawFadedBackground = false;
#endif

}
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

bool BoxColliderComponent::SetValueTable(const sol::table& table)
{
   if (!Component::SetValueTable(table)) { ASSERT(false); return false; }

   sol::optional<sol::table> offset = table["Offset"];
   sol::optional<sol::table> scale = table["Scale"];
   sol::optional<std::string> tag = table["Tag"];
   sol::optional<std::string> textureId = table["TextureId"];

   ASSERT(textureId);
   if (!offset || !scale || !tag) { ASSERT(false); return false; }

   sol::optional<float> offsetX = offset.value()["X"];
   sol::optional<float> offsetY = offset.value()["Y"];
   sol::optional<float> scaleX = scale.value()["Y"];
   sol::optional<float> scaleY = scale.value()["Y"];

   if (!offsetX || !offsetY || !scaleX || !scaleY) { ASSERT(false); return false; }

   m_vOffset.x = offsetX.value();
   m_vOffset.y = offsetY.value();
   m_vScale.x = scaleX.value();
   m_vScale.y = scaleY.value();
   m_strTag = tag.value();

   if (textureId)
   {
      std::string id = textureId.value();
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
   return true;
}

std::string BoxColliderComponent::SaveComponentToLua(const std::string& strSubTableName) const
{
   ASSERT(m_pTexture);

   std::string strLua;
   strLua.reserve(100);

   strLua += StringR::Format("%s.Components.BoxCollider = {\n", strSubTableName.c_str());
   strLua += Component::SaveComponentToLua();

   strLua += StringR::Format("\tOffset = { X = %.1f, Y = %.1f },\n", m_vOffset.x, m_vOffset.y);
   strLua += StringR::Format("\tScale = { X = %.1f, Y = %.1f },\n", m_vScale.x, m_vScale.y);
   strLua += StringR::Format("\tTag = \"%s\",\n", StringR::ParsePath (m_strTag).c_str());
   strLua += StringR::Format("\tTextureId = \"%s\"\n", StringR::ParsePath (m_pTexture->GetTextureId()).c_str());
   strLua += '}';
   strLua += '\n';
   return strLua;
}

#ifdef EX_2020_DRAW_FADED_BOX
void BoxColliderComponent::OnCollision(BoxColliderComponent* other)
{
   ASSERT(other);
   m_bDrawFadedBackground = true;
}
void BoxColliderComponent::OnCollisionExit(BoxColliderComponent* other)
{
   ASSERT(other);
   m_bDrawFadedBackground = false;
}
#endif