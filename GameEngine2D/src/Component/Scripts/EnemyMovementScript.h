#pragma once
#include "Component/Component.h"

class Entity;

class EnemyMovementScript : public Component
{
   COMPONENT_TYPE(EnemyMovementScript);
   COMPONENT_NAME("Enemy Movement Script");
public:
   EnemyMovementScript();
   ~EnemyMovementScript();

   //Overrides
   void OnInitialise() override;
   void OnUpdate(double deltaTime) override;

   void OnCollisionEnter(BoxColliderComponent* otherCollider) override;
   void OnCollision(BoxColliderComponent* otherCollider)  override;
   void OnCollisionExit(BoxColliderComponent* otherCollider) override;

   virtual bool SetValueTable(const sol::table& table) override;
   virtual std::string SaveComponentToLua(const std::string& strSubTableName) const override;

private:
   Entity* m_pEntityPrefab;
   TransformComponent* m_pTransform;
   double m_dTime;
};