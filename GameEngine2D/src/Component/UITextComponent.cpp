#include "pch.h"
#include "UITextComponent.h"

#include "Game/Game.h"

//fontID is not an optional parameter (unlike the others)
UITextComponent::UITextComponent(const std::string& fontID, const glm::vec2& offset, const glm::vec2& scale) :
   m_FontData(),
   m_pTransformComponent(nullptr),
   m_vOffset (offset),
   m_vScale (scale)
{
   SetFont(fontID);
}
UITextComponent::~UITextComponent()
{

}
void UITextComponent::SetFont(const std::string& fontID)
{
   TTF_Font* pFont = Game::s_pAssetManager->GetFont(fontID);
   ASSERT(pFont);
   m_FontData.SetFont(pFont);
}

void UITextComponent::OnInitialise()
{
   m_pTransformComponent = m_pEntityOwner->GetComponent<TransformUIComponent>();
   ASSERT(m_pTransformComponent);

}
void UITextComponent::OnRender()
{
   
   Engine::Rect rectOriginal;
   GetRect(rectOriginal);
   //rectDest.x = rectOriginal.GetLeft();
   //rectDest.y = rectOriginal.GetTop();
   //rectDest.w = rectOriginal.GetWidth();
   //rectDest.h = rectOriginal.GetHeight();
   SDL_Rect rectDest{ rectOriginal.GetLeft(), rectOriginal.GetTop(), rectOriginal.GetWidth(), rectOriginal.GetHeight() };
   Engine::FontManager::DrawFont(m_FontData, rectDest);
}

void UITextComponent::GetRect(Engine::Rect& rect) const
{
   m_pTransformComponent->GetRect(rect);
   rect.Translate(m_vOffset.x, m_vOffset.y);
   rect.Scale(m_vScale.x, m_vScale.y);
}
Engine::Rect UITextComponent::GetRect() const
{
   Engine::Rect rect;
   GetRect(rect);
   return rect;
}