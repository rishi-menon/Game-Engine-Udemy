#pragma once
#include "Transform/TransformComponent.h"
#include <glm/glm.hpp>
#include "Assets/AssetManager.h"


class BoxColliderComponent : public Component
{
public:
   COMPONENT_TYPE(BoxCollider);
   COMPONENT_NAME("Box Collider");

   BoxColliderComponent();
   BoxColliderComponent(const std::string& colliderTag, const glm::vec2& offset = glm::vec2(0,0), const glm::vec2& scale = glm::vec2(1,1), const std::string& id = "");
   ~BoxColliderComponent();

   void OnInitialise() override;
   void OnUpdate(double deltaTime) override;
   void OnRender() override;

   void GetRect(Engine::Rect& rect) const;
   Engine::Rect GetRect() const;

   const std::string& GetTag() const { return m_strTag; }

   //Lua
   virtual bool SetValueTable(const sol::table& table) override;

   virtual std::string SaveComponentToLua(const std::string& strSubTableName) const override;

#ifdef EX_2020_DRAW_FADED_BOX
   void OnCollision(BoxColliderComponent& other) override;
   void OnCollisionExit(BoxColliderComponent& other) override;
#endif

private:
   void DrawCollisionBox();
private:
   TransformComponent* m_pTransformComponent;

   glm::vec2 m_vOffset;
   glm::vec2 m_vScale;
   std::string m_strTag;

   Engine::Texture* m_pTexture;
   SDL_Rect m_rectSource;
   bool m_bDrawTexture;

#ifdef EX_2020_DRAW_FADED_BOX
   bool m_bDrawFadedBackground;  //To draw the faded background when a collision takes place 
#endif
};