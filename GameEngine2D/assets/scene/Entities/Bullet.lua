local mod = {}

mod.Name = "Bullet"
mod.Enabled = false    

mod.Components = {}

mod.Components.Transform = {
   Position = { X = 0.0, Y = 0.0 },
   Velocity = { X = 0.0, Y = 1.0 },
   Scale    = { X = 0.1, Y = 0.1 }   
}
mod.Components.Sprite = {
   Id = "bullet-enemy",
}

mod.Components.BoxCollider = {
   Offset = { X = 0, Y = 0 },
   Scale =  { X = 1, Y = 1 },
   Tag = "Bullet",
   TextureId = "collision-texture"
}

return mod