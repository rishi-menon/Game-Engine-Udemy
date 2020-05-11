#pragma once

#include "Component.h"
#include <string>

class PlayerControllerComponent : public Component
{
public:
   COMPONENT_TYPE(PlayerController)
   COMPONENT_NAME("PlayerController")
public:
   PlayerControllerComponent();
   ~PlayerControllerComponent();

   //overrides
   void OnInitialise() override;
   void OnUpdate(double deltaTime) override;

   void SetMovementControls(const std::string& up, const std::string& left, const std::string& down, const std::string& right);

   void SetFireControl(const std::string& st);

   virtual bool SetValueTable(const sol::table& table) override;
   virtual std::string SaveComponentToLua(const std::string& strSubTableName) const override;

public:
   glm::vec2 m_vecVelocity;
private:
   static int GetKeyCodeFromString(const std::string& st);
   static int GetScanCodeFromString(const std::string& string);


private:
   TransformComponent* m_pTransformComponent;
   AnimationComponent* m_pAnimationComponent;

   int m_nKeyUp;
   int m_nKeyRight;
   int m_nKeyDown;
   int m_nKeyLeft;
   int m_nKeyFire;

};