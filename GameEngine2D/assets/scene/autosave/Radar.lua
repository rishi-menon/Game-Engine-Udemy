local mod = {}mod.Name = "Radar"
mod.Enabled = true
mod.Components = {}
mod.Components.TransformUI = {
	Active = true,
	Position = { X = 700.0, Y = 20.0 },
	Scale = { X = 64.0, Y = 64.0 }
}
mod.Components.Sprite = {
	Active = true,
	Id = "radar",
	TextureDefaultRect = { X = 0, Y = 0, W = 64, H = 64 } 
}
mod.Components.Animation = {
	Active = true,
	GridSize = { X = 1, Y = 1 },
	RotationSpeed = 150.0,
	StartingAnimation = "",
	AnimationList = {
	}
}
mod.Components.TextUI = {
	Active = true,
	Offset = { X = 0.0, Y = -5.0 },
	Scale =  { X = 1.4, Y = 1.0 },
	FontId = "charriot",
	StartingText = "Radar",
	StartingColor = {r = 0, g = 230, b = 100, a = 255}
}
return mod