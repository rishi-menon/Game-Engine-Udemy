local mod = {}mod.Name = "Bullet"
mod.Enabled = false
mod.Components = {}
mod.Components.Transform = {
	Active = true,
	Position = { X = 0.0, Y = 0.0 },
	Scale = { X = 0.1, Y = 0.1 },
	Velocity = { X = 0.0, Y = 1.0 }
}
mod.Components.Sprite = {
	Active = true,
	Id = "bullet-enemy",
	TextureDefaultRect = { X = 0, Y = 0, W = 4, H = 4 } 
}
mod.Components.BoxCollider = {
	Active = true,
	Offset = { X = 0.0, Y = 0.0 },
	Scale = { X = 1.0, Y = 1.0 },
	Tag = "Bullet",
	TextureId = "collision-texture"
}
return mod