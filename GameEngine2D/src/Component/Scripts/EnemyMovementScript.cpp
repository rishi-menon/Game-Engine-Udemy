
#include "pch.h"
#include "EnemyMovementScript.h"

#include "Entity/EntityManager.h"


EnemyMovementScript::EnemyMovementScript() :
   m_pEntityPrefab (nullptr),
   m_pTransform(nullptr),
   m_dTime(0.0)
{
}
EnemyMovementScript::~EnemyMovementScript()
{

}

void EnemyMovementScript::OnInitialise()
{
   ASSERT(m_pEntityOwner);
   std::string strBulletName = "Bullet";  //Take this as a parameter instead ?
   m_pEntityPrefab = m_pEntityOwner->GetEntityManager().GetEntityFromName(strBulletName);
   ASSERT(m_pEntityPrefab);

   m_pTransform = m_pEntityOwner->GetComponent<TransformComponent>();
   ASSERT(m_pTransform);
}

void EnemyMovementScript::OnUpdate(double deltaTime)
{
   m_dTime += deltaTime;
   if (m_pEntityOwner && m_dTime > 3)
   {
      m_dTime = 0.0;
      Entity& newEntity = m_pEntityOwner->GetEntityManager().Instantiate(m_pEntityPrefab, 1.5);
      newEntity.SetIsActive(true);
      TransformComponent* pComponent = newEntity.GetComponent<TransformComponent>();
      ASSERT(pComponent);
      pComponent->SetPosition(m_pTransform->GetPosition());
      LOGW("Created Bullet");
   }
}

void EnemyMovementScript::OnCollisionEnter(BoxColliderComponent& otherCollider)
{
   LOGW("\nCollision START\n\n");
}
void EnemyMovementScript::OnCollision(BoxColliderComponent& otherCollider)
{
   LOGW("Collision...\n");
}
void EnemyMovementScript::OnCollisionExit(BoxColliderComponent& otherCollider)
{
   LOGW("\nCollision END\n");
}