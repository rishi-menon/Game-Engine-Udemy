#pragma once
#include "Component/Component.h"
#include "TransformPartialComponent.h"

class EntityManager;
namespace Engine::Lua {
   bool CreateEntity(const sol::table& entityTable, EntityManager& manager);
}

class TransformComponent : public TransformPartialComponent
{
   friend bool Engine::Lua::CreateEntity (const sol::table& entityTable, EntityManager& manager);
public:
   COMPONENT_NAME("Transform")
   COMPONENT_TYPE(Transform);

   TransformComponent();
   TransformComponent(const glm::vec2& pos, const glm::vec2& vel, const glm::vec2& scale);
   virtual ~TransformComponent();

   virtual void OnInitialise() override;
   virtual void OnUpdate(double deltaTime) override;
   virtual void OnRender() override;

   virtual bool SetValueTable(const sol::table& table) override;

   virtual std::string SaveComponentToLua(const std::string& strSubTableName) const override;

public:
   glm::vec2 m_vVeloctiy;
};