
#include "pch.h"
#include "SelfDestructComponent.h"
#include "Entity/EntityManager.h"

void SelfDestructComponent::OnUpdate(double deltaTime)
{
   m_dTimeElapsed += deltaTime;
   if (m_dTimeElapsed >= m_dTimeTotal)
   {
      //Destroy the gameobject
      ASSERT(m_pEntityOwner);
      m_pEntityOwner->GetEntityManager()->DestroyEntity(m_pEntityOwner);
   }
}