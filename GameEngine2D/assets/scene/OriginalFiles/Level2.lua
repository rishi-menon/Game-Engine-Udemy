
assets = {
	textures = { 
		{ Id = "tank-big-right", Src = "assets\\images\\tank-big-right.png" },
		{ Id = "chopper-spritesheet", Src = "assets\\images\\chopper-spritesheet.png" },
		{ Id = "radar", Src = "assets\\images\\radar.png" },
		{ Id = "collision-texture", Src = "assets\\images\\collision-texture.png" },
		{ Id = "bullet-enemy", Src = "assets\\images\\bullet-enemy.png" },
		{ Id = "jungle", Src = "assets\\tilemaps\\jungle.png" },
	},
	fonts = {
		{ Id = "charriot", Src = "assets\\fonts\\charriot.ttf", Size = 100 },
	}
}

map = {
	Id = "jungle",
	Src = "assets/tilemaps/jungle.map",
	TileSize = 32,
	PosX = -15,
	PosY = 15
}

camera = {
	PosX = 0,
	PosY = 0,
	PixelsPerUnit = 40,
	FollowEntity = "Player"
}

entities = {}
entities[1] = {}
mod.Name = "Bullet"
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
entities[2] = {}
mod.Name = "Player"
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
		{ Id = "down", Layout = {0, 1, }, Speed = 17.0, }, 
		{ Id = "right", Layout = {2, 0, }, Speed = 17.0, }, 
		{ Id = "left", Layout = {4, 5, }, Speed = 17.0, }, 
		{ Id = "up", Layout = {6, 7, }, Speed = 17.0, }, 
	}
}
mod.Components.BoxCollider = {
	Active = true,
	Offset = { X = 0.0, Y = 0.0 },
	Scale = { X = 1.0, Y = 1.0 },
	Tag = "Player",
	TextureId = "collision-texture"
}
mod.Components.PlayerController = {
	Active = true,
	MovementKeys = { Up = 4, Left = 4, Down = 22, Right = 7 },
	FireKey = 44,
	Velocity = {X = 4.0, Y = 4.0}
}
mod.Components.EnemyMovementScript = {
	Active = true,
}
