#pragma once

#include "Transform/TransformUIComponent.h"
#include "Assets/AssetManager.h"

class UITextComponent : public Component
{
public:
   COMPONENT_TYPE(UIText);
   COMPONENT_NAME("UI Text");
public:
   UITextComponent();
   UITextComponent(const std::string& fontID, const glm::vec2& offset = { 0.0f, 0.0f }, const glm::vec2& scale = { 1.0f, 1.0f });
   ~UITextComponent();

   void OnInitialise() override;
   void OnRender() override;

   void GetRect(Engine::Rect& rect) const;
   Engine::Rect GetRect() const;

   void SetFont(const std::string& fontID);
   void SetText(const std::string& text)  { m_FontData.SetText(text); }
   void SetColor(const SDL_Color& col)    { m_FontData.SetColor(col); }

   virtual bool SetValueTable(const sol::table& table) override;
   virtual std::string SaveComponentToLua(const std::string& strSubTableName) const override;

private:
   Engine::FontData m_FontData;
   TransformUIComponent* m_pTransformComponent;
   
   glm::vec2 m_vOffset;
   glm::vec2 m_vScale;
};