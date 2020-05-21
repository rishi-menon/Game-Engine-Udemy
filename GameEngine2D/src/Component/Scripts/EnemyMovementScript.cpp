
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
   std::string strBulletName = "Bullet";  //Take this as a parameter instead ?
   ASSERT(m_pEntityOwner && m_pEntityOwner->GetEntityManager());
   m_pEntityPrefab = m_pEntityOwner->GetEntityManager()->GetEntityFromName(strBulletName);
   ASSERT(m_pEntityPrefab);

   m_pTransform = m_pEntityOwner->GetComponent<TransformComponent>();
   ASSERT(m_pTransform);
}

void EnemyMovementScript::OnUpdate(double deltaTime)
{
   m_dTime += deltaTime;
   if (m_dTime > 1 && m_pEntityPrefab && m_pEntityOwner && m_pEntityOwner->GetEntityManager())
   {
      m_dTime = 0.0;
      Entity* pNewEntity = m_pEntityOwner->GetEntityManager()->Instantiate(m_pEntityPrefab, 5);
      if (pNewEntity)
      {
         pNewEntity->SetIsActive(true);
         TransformComponent* pComponent = pNewEntity->GetComponent<TransformComponent>();
         ASSERT(pComponent);
         pComponent->SetPosition(m_pTransform->GetPosition());
         //LOGW("Created Bullet");
      }
   }
}

void EnemyMovementScript::OnCollisionEnter(BoxColliderComponent* otherCollider)
{
   /*if (GetEntityOwner()->GetName() != "Tank")
      LOGW("\nCollision START\n\n");*/
}
void EnemyMovementScript::OnCollision(BoxColliderComponent* otherCollider)
{
   //LOGW("Collision...\n");
}
void EnemyMovementScript::OnCollisionExit(BoxColliderComponent* otherCollider)
{
   //if (GetEntityOwner()->GetName() != "Tank")
   //   LOGW("\nCollision END\n");
}

bool EnemyMovementScript::SetValueTable(const sol::table& table)
{
   if (!Component::SetValueTable(table)) { ASSERT(false); return false; }
   return true;
}
std::string EnemyMovementScript::SaveComponentToLua(const std::string& strSubTableName) const
{
   std::string strLua;
   strLua.reserve(100);

   strLua += StringR::Format("%s.Components.EnemyMovementScript = {\n", strSubTableName.c_str());
   strLua += Component::SaveComponentToLua();
   strLua += '}';
   strLua += '\n';
   return strLua;
}