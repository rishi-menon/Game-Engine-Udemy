local mod = {}

mod.Name = "Player"
mod.Enabled = true    --This is completely optional... Sets the starting enabled to false 

mod.Components = {}
mod.Components.Transform = {
   Position = {X = -14.0, Y = 0.0},
   Velocity = {X = 0.0,   Y = 0.0},
   Scale    = {X = 1.0,   Y = 1.0}   
}
mod.Components.Sprite = {
   Id = "chopper-spritesheet",
   --OPTIONAL...This is the default part of the texture which is rendered... If it is not present or ill formed then the entire texture is used as the default
   --TextureDefaultRect = {x = 0, y = 0, w = 64, h = 64}   
}

mod.Components.Animation = {
   GridSize = {X = 2, Y = 4},
   StartingAnimation = "down",
   RotationSpeed = 0.0,

   AnimationList = {
      [1] = { 
         Id = "down", 
         Layout = {0, 1},
         Speed = 17.0
      },
      [2] = {
         Id = "right", 
         Layout = {2, 3},
         Speed = 17.0
      },
      [3] = {
         Id = "left", 
         Layout = {4, 5},
         Speed = 17.0
      },
      [4] = {
         Id = "up", 
         Layout = {6, 7},
         Speed = 17.0
      }
   }
}

mod.Components.BoxCollider = {
   Offset = {X = 0, Y = 0},
   Scale =  {X = 1, Y = 1},
   Tag = "Player",
   TextureId = "collision-texture"
}

return mod