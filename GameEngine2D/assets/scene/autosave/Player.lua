local mod = {}mod.Name = "Player"
mod.Enabled = true
mod.Components = {}
mod.Components.Transform = {
	Active = true,
	Position = { X = -14.0, Y = 0.0 },
	Scale = { X = 1.0, Y = 1.0 },
	Velocity = { X = 0.0, Y = 0.0 }
}
mod.Components.Sprite = {
	Active = true,
	Id = "chopper-spritesheet",
	TextureDefaultRect = { X = 0, Y = 0, W = 64, H = 128 } 
}
mod.Components.Animation = {
	Active = true,
	GridSize = { X = 2, Y = 4 },
	RotationSpeed = 0.0,
	StartingAnimation = "down",
	AnimationList = {
		{ Id = "right", Layout = {2, 3, }, Speed = 17.0, }, 
		{ Id = "down", Layout = {0, 1, }, Speed = 17.0, }, 
		{ Id = "up", Layout = {6, 7, }, Speed = 17.0, }, 
		{ Id = "left", Layout = {4, 5, }, Speed = 17.0, }, 
	}
}
mod.Components.PlayerController = {
	Active = true,
	MovementKeys = { Up = 26, Left = 4, Down = 22, Right = 7 },
	FireKey = 44,
	Velocity = {X = 4.0, Y = 4.0}
}
mod.Components.BoxCollider = {
	Active = true,
	Offset = { X = 0.0, Y = 0.0 },
	Scale = { X = 1.0, Y = 1.0 },
	Tag = "Player",
	TextureId = "collision-texture"
}
return mod