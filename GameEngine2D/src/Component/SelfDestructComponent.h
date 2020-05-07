#pragma once

#include "Component.h"

class SelfDestructComponent : public Component
{
   COMPONENT_TYPE(SelfDestruct);
   COMPONENT_NAME("Self Destruct");

public:
   SelfDestructComponent(double dTimeTotal) : m_dTimeTotal(dTimeTotal), m_dTimeElapsed(0.0) {}
   
   void OnUpdate(double deltaTime) override;
   virtual bool CopyDuringInstantiate() const override { return false; }


private:
   double m_dTimeTotal;    //in seconds
   double m_dTimeElapsed;  //in seconds
};