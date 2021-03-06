#include "pch.h"
#include "UITextComponent.h"

#include "Game/Game.h"

UITextComponent::UITextComponent() :
   m_FontData(),
   m_pTransformComponent(nullptr),
   m_vOffset(0.0f, 0.0f),
   m_vScale(0.0f, 0.0f)

{
   SetColor(SDL_Color{ 0,0,0,0 });
   SetText("");
}

//fontID is not an optional parameter (unlike the others)
UITextComponent::UITextComponent(const std::string& fontID, const glm::vec2& offset, const glm::vec2& scale) :
   m_FontData(),
   m_pTransformComponent(nullptr),
   m_vOffset (offset),
   m_vScale (scale)
{
   SetFont(fontID);
   SetColor(SDL_Color{ 0,0,0,0 });
   SetText("");
}
UITextComponent::~UITextComponent()
{

}
void UITextComponent::SetFont(const std::string& fontID)
{
   Engine::Font* pFont = Game::s_pAssetManager->GetFont(fontID);
   ASSERT(pFont);
   m_FontData.SetFont(pFont);
}

void UITextComponent::OnInitialise()
{
   ASSERT(m_pEntityOwner);
   m_pTransformComponent = m_pEntityOwner->GetComponent<TransformUIComponent>();
   ASSERT(m_pTransformComponent);

}
void UITextComponent::OnRender()
{
   
   Engine::Rect rectOriginal;
   GetRect(rectOriginal);
   SDL_Rect rectDest{ (int)rectOriginal.GetLeft(), (int)rectOriginal.GetTop(), (int)rectOriginal.GetWidth(), (int)rectOriginal.GetHeight() };
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

bool UITextComponent::SetValueTable(const sol::table& table)
{
   if (!Component::SetValueTable(table)) { ASSERT(false); return false; }
   //Offset
   {
      sol::optional<sol::table> offset = table["Offset"];
      if (!offset) { ASSERT(false); return false; }
      sol::optional<float> offsetX = offset.value()["X"];
      sol::optional<float> offsetY = offset.value()["Y"];
      if (!offsetX || !offsetY) { ASSERT(false); return false; }
      m_vOffset.x = offsetX.value();
      m_vOffset.y = offsetY.value();
   }

   //Scale
   {
      sol::optional<sol::table> scale = table["Scale"];
      if (!scale) { ASSERT(false); return false; }
      sol::optional<float> scaleX = scale.value()["X"];
      sol::optional<float> scaleY = scale.value()["Y"];
      if (!scaleX || !scaleY) { ASSERT(false); return false; }
      m_vScale.x = scaleX.value();
      m_vScale.y = scaleY.value();
   }
   //Font ID
   {
      sol::optional<std::string> fontID = table["FontId"];
      if (!fontID) { ASSERT(false); return false; }
      SetFont(fontID.value());
   }

   //These are optional additional data
   //starting text
   sol::optional<std::string> startingText = table["StartingText"];
   if (startingText)    SetText(startingText.value());
   //color
   {
      sol::optional<sol::table> color = table["StartingColor"];
      if (color)
      {
         sol::optional<int> r = color.value()["r"];
         sol::optional<int> g = color.value()["g"];
         sol::optional<int> b = color.value()["b"];
         sol::optional<int> a = color.value()["a"];
         ASSERT(r && g && b && a);
         if (r && g && b && a)
         {
            SDL_Color col;
            col.r = static_cast<char>(r.value());
            col.g = static_cast<char>(g.value());
            col.b = static_cast<char>(b.value());
            col.a = static_cast<char>(a.value());
            SetColor(col);
         }
      }
   }
   
   return true;
}

std::string UITextComponent::SaveComponentToLua(const std::string& strSubTableName) const
{
   ASSERT(m_FontData.GetFont());

   std::string strLua;
   strLua.reserve(100);
   strLua += StringR::Format("%s.Components.TextUI = {\n", strSubTableName.c_str());
   strLua += Component::SaveComponentToLua();
   strLua += StringR::Format("\tOffset = { X = %.1f, Y = %.1f },\n", m_vOffset.x, m_vOffset.y);
   strLua += StringR::Format("\tScale =  { X = %.1f, Y = %.1f },\n", m_vScale.x, m_vScale.y);
   strLua += StringR::Format("\tFontId = \"%s\",\n", StringR::ParsePath(m_FontData.GetFont()->GetFontId()).c_str());

   //These fields are optional technically
   strLua += StringR::Format("\tStartingText = \"%s\",\n", StringR::ParsePath(m_FontData.GetText()).c_str());

   const SDL_Color& col = m_FontData.GetColor();
   strLua += StringR::Format("\tStartingColor = {r = %d, g = %d, b = %d, a = %d}\n", col.r, col.g, col.b, col.a);
   strLua += '}';
   strLua += '\n';
   
   return strLua;
}
