
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
entities[1].Name = "Bullet"
entities[1].Enabled = false
entities[1].Components = {}
entities[1].Components.Transform = {
	Active = true,
	Position = { X = 0.0, Y = 0.0 },
	Scale = { X = 0.1, Y = 0.1 },
	Velocity = { X = 0.0, Y = 1.0 }
}
entities[1].Components.Sprite = {
	Active = true,
	Id = "bullet-enemy",
	TextureDefaultRect = { X = 0, Y = 0, W = 4, H = 4 } 
}
entities[1].Components.BoxCollider = {
	Active = true,
	Offset = { X = 0.0, Y = 0.0 },
	Scale = { X = 1.0, Y = 1.0 },
	Tag = "Bullet",
	TextureId = "collision-texture"
}
entities[2] = {}
entities[2].Name = "Player"
entities[2].Enabled = true
entities[2].Components = {}
entities[2].Components.Transform = {
	Active = true,
	Position = { X = -14.0, Y = 0.0 },
	Scale = { X = 1.0, Y = 1.0 },
	Velocity = { X = 0.0, Y = 0.0 }
}
entities[2].Components.Sprite = {
	Active = true,
	Id = "chopper-spritesheet",
	TextureDefaultRect = { X = 0, Y = 0, W = 64, H = 128 } 
}
entities[2].Components.Animation = {
	Active = true,
	GridSize = { X = 2, Y = 4 },
	RotationSpeed = 0.0,
	StartingAnimation = "down",
	AnimationList = {
		{ Id = "down", Layout = {0, 1, }, Speed = 17.0, }, 
		{ Id = "right", Layout = {2, 3, }, Speed = 17.0, }, 
		{ Id = "left", Layout = {4, 5, }, Speed = 17.0, }, 
		{ Id = "up", Layout = {6, 7, }, Speed = 17.0, }, 
	}
}
entities[2].Components.BoxCollider = {
	Active = true,
	Offset = { X = 0.0, Y = 0.0 },
	Scale = { X = 1.0, Y = 1.0 },
	Tag = "Player",
	TextureId = "collision-texture"
}
entities[2].Components.PlayerController = {
	Active = true,
	MovementKeys = { Up = 26, Left = 4, Down = 22, Right = 7 },
	FireKey = 44,
	Velocity = {X = 4.0, Y = 4.0}
}
entities[3] = {}
entities[3].Name = "Radar"
entities[3].Enabled = true
entities[3].Components = {}
entities[3].Components.TransformUI = {
	Active = true,
	Position = { X = 700.0, Y = 20.0 },
	Scale = { X = 64.0, Y = 64.0 }
}
entities[3].Components.Sprite = {
	Active = true,
	Id = "radar",
	TextureDefaultRect = { X = 0, Y = 0, W = 64, H = 64 } 
}
entities[3].Components.Animation = {
	Active = true,
	GridSize = { X = 1, Y = 1 },
	RotationSpeed = 150.0,
	StartingAnimation = "",
	AnimationList = {
	}
}
entities[3].Components.TextUI = {
	Active = true,
	Offset = { X = 0.0, Y = -5.0 },
	Scale =  { X = 1.4, Y = 1.0 },
	FontId = "charriot",
	StartingText = "Radar",
	StartingColor = {r = 0, g = 230, b = 100, a = 255}
}
