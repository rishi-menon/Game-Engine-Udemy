assets = {
   textures = {

      [1] =   {   id = "tank-big-right",       src = "assets\\images\\tank-big-right.png"        },
      [2] =   {   id = "chopper-spritesheet",  src = "assets\\images\\chopper-spritesheet.png"   },
      [3] =   {   id = "radar",                src = "assets\\images\\radar.png"                 },
      [4] =   {   id = "collision-texture",    src = "assets\\images\\collision-texture.png"     },
      [5] =   {   id = "bullet-enemy",         src = "assets\\images\\bullet-enemy.png"          },
      [6] =   {   id = "jungle",               src = "assets\\tilemaps\\jungle.png"              }
   },
   fonts = {
      [1] = { id = "charriot",      src = "assets\\fonts\\charriot.ttf",      size = 100 }
   }
}

map = {
   --"assets/tilemaps/jungle.map", "jungle", 32, -15, 15

   id = "jungle",                            --Texture id
   src = "assets/tilemaps/jungle.map",       --Location of the .map file which contains which tiles to use in which position (text file)
   tileSize = 32,                            --the sprite size in the spritesheet texture (in pixels)
   PosX = -15.0,                             --X coordinate (world) of the top left tile in the map
   PosY =  15.0                              --Y coordinate (world) of the top left tile in the map
}

-- optional table (if table doesnt exist then x=0, y=0 and PixelsPerUnit=40 are the values used to initialise the camera)
camera = {
   PosX = 0.0,                              --Starting coordinates (World) 
   PosY = 0.0,                              --Starting coordinates (World) 
   PixelsPerUnit = 40.0,                    --This is value is optional... If it is not set then value is 40 by default  

   FollowEntity = "Player"                  --This value is optional... If it is not set then the value is "Player" by default
}

   -- The 'require' keyword uses . as the path seperator instead of \\.... So file "assets\\scene\\Entities\\player.lua" becomes assets.scene.Entities.
   --Also, dont specify the file extension while using the require keyword
local EntitiesPath = "assets.scene.Entities."
entities = {
     
   [1] = require (EntitiesPath .. "Player")
}