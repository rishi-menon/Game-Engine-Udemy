local mod = {}mod.Name = "Tank"
mod.Enabled = true
mod.Components = {}
mod.Components.Transform = {
	Active = true,
	Position = { X = 0.0, Y = 0.0 },
	Scale = { X = 1.0, Y = 1.0 },
	Velocity = { X = -0.5, Y = 0.0 }
}
mod.Components.Sprite = {
	Active = true,
	Id = "tank-big-right",
	TextureDefaultRect = { X = 0, Y = 0, W = 32, H = 32 } 
}
mod.Components.BoxCollider = {
	Active = true,
	Offset = { X = 0.0, Y = 0.0 },
	Scale = { X = 1.0, Y = 1.0 },
	Tag = "Enemy",
	TextureId = "collision-texture"
}
mod.Components.EnemyMovementScript = {
	Active = true,
}
return mod