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

   void OnInitialise() override;
   void OnUpdate(double deltaTime) override;

   void EnemyMovementScript::OnCollisionEnter(BoxColliderComponent& otherCollider) override;
   void EnemyMovementScript::OnCollision(BoxColliderComponent& otherCollider)  override;
   void EnemyMovementScript::OnCollisionExit(BoxColliderComponent& otherCollider) override;

private:
   Entity* m_pEntityPrefab;
   TransformComponent* m_pTransform;
   double m_dTime;
};