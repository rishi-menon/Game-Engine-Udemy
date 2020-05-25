# Game-Engine-Udemy
Engine Info:  
Creating a simple 2D game engine in C++. Currently the engine supports an Entity-Component system (Various components such as Transform, Sprite, Animation, UI have been created). The engine supports saving and loading a scene (saves/loads from a .lua file). Each entity can also be saved to a seperate lua file if required (This feature was added to make prefabs easier to implement in the future). The entity and each of it components can generate the lua file and can load its values from the lua file.  
The background view is loaded from a spritesheet and a .map file (which is actually just a .csv file which stores the index of the image in the spritesheet)
The engine supports an orthographic camera which converts world coordinates to screen coordinates and vice versa. It also controls the view rect (zoom level).  
Animation is only supported in the form of spritesheets at the moment. 
The engine also supports Axis Aligned Bounding Box (AABB) collision detection. It cannot check collision with rotated quads. It also only supports collision between two rectangles (Yes, I know what you might be thinking....it's very restrictive at the moment)

Game Info:  
The purpose behind this project is to build an engine not a game. But, building a game is the best way to furthur develop the engine. For that purpose, I would be building a game using the engine. The topic of the game is subject to change but at the moment it is a simple shooting game. Currently the player can hit space key to shoot and the tank (enemy) shoots at a regular interval. The bullet acts as a prefab and is instantiated when the player/tank shoots and is destroyed after a time interval. The radar does not work at the moment (It only rotates but doesnt show any enemies.)

Images:  
<img src = "Images\Img1.PNG" width="800">  
<img src = "Images\Img2.PNG" width="800">  
<img src = "Images\Img3.PNG" width="800">  
