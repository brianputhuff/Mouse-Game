# Mouse Game
Eat the cheese, avoid the cats, collect the bonus items! A game for computers.


1. How to play
2. Controls
3. Compiling and running


## 1. How to play
The object of the game is to move the mouse over all cells containing a cheese nugget. There are 50 cheese nuggets randomly placed within a single stage. Eat all 50 cheese nuggets and the stage is complete. There are 16 stages in total. Complete all 16 stages and the game will end. 

![Screenshot of first area of game](https://github.com/brianputhuff/mousegame/blob/0c21b8af1c50bc8f0ce7827ebaf9efa5ad4b8b36/mousegame_20211221-153640.png)

**Note:** Stage structures are randomly generated, so every play session will yield unique layouts.

There are four cats that move about the stage. If the mouse makes contact with any of the four cats, the player loses that mouse. The player has an initial reserve set of mice. Every time a mouse is lost, one of the reserve mice are depleted and the game continues. If there are no reserve mice available, the game will end.

After a specific duration of play in a stage, a coffee icon will appear at a random location within the stage. If the mouse consumes the coffee, all cats will move at a much slower rate of speed for a limited time.

After a specific duration of play in a stage, a bonus icon will appear at a random location in the stage. If the mouse consumes the bonus icon, all cats will move at a much faster rate of speed for a limited time, however the player will get a major score increase.

![Screenshot of second area of game](https://github.com/brianputhuff/mousegame/blob/0c21b8af1c50bc8f0ce7827ebaf9efa5ad4b8b36/mousegame_20211221-154021.png)

The player will be awarded an extra mouse to his reserve mice when the player's score reaches intervals of 10,000 points. If the player completes a stage without consuming the coffee icon, additional stage completion points are awarded.


## 2. Controls
The game supports keyboard and game controller controls. To use a game controller, ensure it is connected prior to starting the application. The game currently does not have hot plug checking, so if you lose game controller connection, you will need to close the game application and restart it after you've re-established connection.

To move the mouse with the game controller, use either the left analog stick or the dpad.
To move the mouse with the keyboard, use the cursor keys or the following:

 `w` = UP
 
 `a` = LEFT
 
 `s` = DOWN
 
 `d` = RIGHT

To pause the game during the game play, press the `TAB` key or the `START BUTTON` on the game controller.

To start the game press the `z` key on the keyboard or the `A BUTTON` on the game controller.

To exit the game application, press the `ESC` key on the keyboard at any time.

To change the color palette, press `,` (comma) or `.` (period) to cycle forward and backward respectively through the palette options. If you are using a game controller, use may cycle through the palette options using the `LEFT BUTTON (LB)` and `RIGHT BUTTON (RB)` respectively.

To save a screenshot of the game in progress, press `v` on the keyboard, or the `Y BUTTON` on a game controller.
NOTE: Game screenshots are saved to the game folder. They are scaled to the size of the game window scale, and stored as .BMP files.


## 3. Compiling and running
There is a makefile included in this repository. Use `make` to build an executable.

**Note:** You will need to have SDL2 and SDL mixer software development libraries installed to compile.

[SDL2](https://www.libsdl.org/)

[SDL Mixer](ttps://github.com/libsdl-org/SDL_mixer) 

If all goes according to plan and you were able to build this game, simply run the executable `.\mousegame`to play.

**Note:** You will need to the shared object library files installed for bothe SDL2 and SDL mixer in order to run the game.

