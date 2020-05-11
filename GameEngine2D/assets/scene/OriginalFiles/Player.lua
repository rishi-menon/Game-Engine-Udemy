local mod = {}

mod.Name = "Player"
mod.Enabled = true    --This is completely optional... Sets the starting enabled to false 

mod.Components = {}

mod.Components.Transform = {
   Active = true,
   Position = { X = -14.0, Y = 0.0 },
   Velocity = { X = 0.0,   Y = 0.0 },
   Scale    = { X = 1.0,   Y = 1.0 },   
}
mod.Components.Sprite = {
   Active = true,
   Id = "chopper-spritesheet",
   --OPTIONAL...This is the default part of the texture which is rendered... If it is not present or ill formed then the entire texture is used as the default
   --TextureDefaultRect = {X = 0, Y = 0, W = 64, H = 64}   
}

mod.Components.Animation = {
   Active = true,
   GridSize = { X = 2, Y = 4 },
   StartingAnimation = "down",
   RotationSpeed = 0.0,

   AnimationList = {
      { 
         Id = "down", 
         Layout = {0, 1,},
         Speed = 17.0,
      },
      {
         Id = "right", 
         Layout = {2, 3,},
         Speed = 17.0,
      },
      {
         Id = "left", 
         Layout = {4, 5,},
         Speed = 17.0,
      },
      {
         Id = "up", 
         Layout = {6, 7,},
         Speed = 17.0,
      },
   }
}

mod.Components.BoxCollider = {
   Active = true,
   Offset = { X = 0, Y = 0 },
   Scale =  { X = 1, Y = 1 },
   Tag = "Player",
   TextureId = "collision-texture",
}

mod.Components.PlayerController = {
   Active = true,

--The MovementKeys can either be a string (like this) or it can be an integer representing the code... It is NOT recommended to use the direct code... (The engine reads the word and converts it into the number... The user might not know which number corresponds to which key). When the engine saves a file, it always saves it with the number
   MovementKeys = { Up = "w", Left = "a", Down = "s", Right = "d" },
   FireKey = "space",
   Velocity = {X = 4, Y = 4}
}

--[[
mod.Components.SelfDestruct = {
   Active = true,
   AliveTime = 4.0
}

mod.Components.TransformUI = {
   Active = true,
   Position = { X = 180.0, Y = 80.0 },
   Scale    = { X = 30.0,   Y = 30.0 }   
}

mod.Components.TextUI = {
   Active = true,
   Offset = { X = 0, Y = 60 },
   Scale =  { X = 10, Y = 1 },
   FontId = "charriot",

   --These are optional
   StartingText = "Player Rishi",
   StartingColor = {r = 25, g = 100, b = 210, a = 255}
}
]]


mod.Components.EnemyMovementScript = {
   Active = true,
}

return mod