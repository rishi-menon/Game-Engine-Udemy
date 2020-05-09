local mod = {}

--[[
   {
      Entity& entity = s_EntityManager.AddEntity("Player");

      entity.AddComponent<TransformComponent>(glm::vec2{ -14,0 }, glm::vec2{ 0, 0 }, glm::vec2{ 1, 1 });
      entity.AddComponent<SpriteComponent>("chopper-spritesheet");
      AnimationComponent& compAnimation =         *entity.AddComponent<AnimationComponent>(2, 4);
      PlayerControllerComponent& compController = *entity.AddComponent<PlayerControllerComponent>();
      entity.AddComponent<BoxColliderComponent>("Player", glm::vec2{ 0, 0 }, glm::vec2{ 1,1 }, "collision-texture");

      const float fSpeed = 17; //animation frames per second
      compAnimation.AddAnimation(AnimationID::DirDown,  AnimationLayout({ 0, 1 }, fSpeed));
      compAnimation.AddAnimation(AnimationID::DirRight, AnimationLayout({ 2, 3 }, fSpeed));
      compAnimation.AddAnimation(AnimationID::DirLeft,  AnimationLayout({ 4, 5 }, fSpeed));
      compAnimation.AddAnimation(AnimationID::DirUp,    AnimationLayout({ 6, 7 }, fSpeed));
      compAnimation.SetCurrentAnimation(AnimationID::DirDown);
      
      
      compController.SetMovementControls("w", "a", "s", "d");
      const float speed = 4;
      compController.m_vecVelocity = glm::vec2(speed, speed );
      compController.SetFireControl("space");
      entity.OnInitialise();
      
   }
]]

mod.Name = "Player"
--mod.Enabled = false    --This is completely optional... Sets the starting enabled to false 

mod.Components = {}
mod.Components.Transform = {
   Position = {x = -14.0, y = 0.0},
   Velocity = {x = 0.0,   y = 0.0},
   Scale    = {x = 1.0,   y = 1.0}   
}
mod.Components.Sprite = {
   Id = "chopper-spritesheet",
   --OPTIONAL...This is the default part of the texture which is rendered... If it is not present or ill formed then the entire texture is used as the default
   --TextureDefaultRect = {x = 0, y = 0, w = 64, h = 64}   
}

return mod