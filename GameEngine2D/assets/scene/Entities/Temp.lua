local mod = {}

mod.Components = {}
mod.Components.TransformUI = {
   Position = { X = 180.0, Y = 80.0 },
   Scale    = { X = 30.0,   Y = 30.0 }   
}

mod.Components.TextUI = {
   Offset = { X = 0, Y = 60 },
   Scale =  { X = 10, Y = 1 },
   FontId = "charriot",

   --These are optional
   StartingText = "Player Rishi",
   StartingColor = {r = 25, g = 100, b = 210, a = 255}
}

return mod