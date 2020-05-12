assets = {
   textures = {
      {   Id = "tank-big-right",       Src = "assets\\images\\tank-big-right.png"        },
      {   Id = "chopper-spritesheet",  Src = "assets\\images\\chopper-spritesheet.png"   },
      {   Id = "radar",                Src = "assets\\images\\radar.png"                 },
      {   Id = "collision-texture",    Src = "assets\\images\\collision-texture.png"     },
      {   Id = "bullet-enemy",         Src = "assets\\images\\bullet-enemy.png"          },
      {   Id = "jungle",               Src = "assets\\tilemaps\\jungle.png"              },
   },
   fonts = {
      { Id = "charriot",      Src = "assets\\fonts\\charriot.ttf",      Size = 100 },
   },
}

map = {
   --"assets/tilemaps/jungle.map", "jungle", 32, -15, 15

   Id = "jungle",                            --Texture id
   Src = "assets/tilemaps/jungle.map",       --Location of the .map file which contains which tiles to use in which position (text file)
   TileSize = 32,                            --the sprite size in the spritesheet texture (in pixels)
   PosX = -15.0,                             --X coordinate (world) of the top left tile in the map
   PosY =  15.0                              --Y coordinate (world) of the top left tile in the map
}

-- optional table (if table doesnt exist then x=0, y=0 and PixelsPerUnit=40 are the values used to initialise the camera)
camera = {
   PosX = 0.0,                              --Starting coordinates (World) 
   PosY = 0.0,                              --Starting coordinates (World) 
   PixelsPerUnit = 40.0,                    --This is value is optional... If it is not set then value is 40 by default  

   FollowEntity = "Player"                  --This value is optional... If it is not set then the camera does not follow any entity. Alternatively if it is set to "", then it is ignored.
}

   -- The 'require' keyword uses . as the path seperator instead of \\.... So file "assets\\scene\\Entities\\player.lua" becomes assets.scene.Entities.
   --Also, dont specify the file extension while using the require keyword
local EntitiesPath = "assets.scene.autosave."

entities = {}
entities[1] = require (EntitiesPath .. "Bullet")
entities[2] = require (EntitiesPath .. "Player")
entities[3] = require (EntitiesPath .. "Radar")
--entities[4] = require (EntitiesPath .. "Tank")