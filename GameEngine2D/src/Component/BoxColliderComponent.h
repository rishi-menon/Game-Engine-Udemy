#pragma once
#include "Transform/TransformComponent.h"
#include <glm/glm.hpp>
#include "Assets/AssetManager.h"

class BoxColliderComponent : public Component
{
public:
   COMPONENT_TYPE(BoxCollider);
   COMPONENT_NAME("Box Collider");

   BoxColliderComponent(const glm::vec2& offset = glm::vec2(0,0), const glm::vec2& scale = glm::vec2(1,1), AssetID id = AssetID::None);
   ~BoxColliderComponent();

   void OnInitialise() override;
   void OnUpdate(double deltaTime) override;
   void OnRender() override;

   void GetRect(Engine::Rect& rect) const;
   Engine::Rect GetRect() const;

private:
   void DrawCollisionBox();
private:
   TransformComponent* m_pTransformComponent;

   glm::vec2 m_vOffset;
   glm::vec2 m_vScale;

   AssetID m_AssetId;
   Engine::Texture* m_pTexture;
   SDL_Rect m_rectSource;

   bool m_bDrawTexture;
};