/**

Mouse Game

Copyright 2021 Brian Puthuff

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors
   may be used to endorse or promote products derived from this software without
   specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/



#ifndef GAME_H
#define GAME_H



#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include "animation.h"
#include "audio.h"
#include "fps.h"
#include "graphics.h"
#include "input.h"
#include "sprite.h"
#include "tile.h"
#include "videomap.h"
#include "mob.h"
#include "bonus.h"
#include "coffee.h"
#include "stage.h"
#include "title.h"
#include "gameover.h"
#include "play.h"
#include "score.h"
#include "cat.h"
#include "ending.h"



/* version */
#define VERSION_MAJOR 1
#define VERSION_MINOR 0
#define VERSION_PATCH 0



/* point values */
#define POINTS_CHEESE 5
#define POINTS_COFFEE 50
#define POINTS_STAGE_COMPLETE 100
#define POINTS_BONUS 1000
#define POINTS_STAGE_COMPLETE_NO_COFFEE 2500
#define EXTRA_MOUSE 10000



/* other data */
#define DATA_START_REMAINING_MICE 6
#define NUMBER_OF_CATS 4
#define ENDING_STAGE 2



/* timeouts */
#define TIMEOUT_GAME_OVER 300
#define TIMEOUT_VERSION_DISPLAY 300
#define TIMEOUT_FLASHING_MESSAGE 16



/* game states */
enum
{
	STATE_GAME_TITLE_PRIMARY,
	STATE_GAME_TITLE_SECONDARY,
	STATE_GAME_TITLE_TERTIARY,
	STATE_GAME_TITLE_QUATERNARY,
	STATE_GAME_STAGE_IN,
	STATE_GAME_PLAY,
	STATE_GAME_STAGE_COMPLETE,
	STATE_GAME_STAGE_OUT,
	STATE_GAME_DEATH,
	STATE_GAME_GAME_OVER,
	STATE_GAME_ENDING,
	STATE_GAME_VERSION
};



/* shared enum for direction */
enum
{
	UP,
	RIGHT,
	DOWN,
	LEFT
};



/* flashing mesage states */
enum
{
	STATE_FLASHING_MESSAGE_SHOWN,
	STATE_FLASHING_MESSAGE_NOT_SHOWN
};



struct Game
{
	/* general data */
	uint8_t state;
	uint8_t paused;
	uint8_t coffee_flag;
	uint8_t remaining_mice;
	uint8_t remaining_cheese;
	uint8_t step_message;
	uint16_t timer;
	uint32_t total_cheese_eaten;
	uint32_t score;
	uint32_t extra_mouse;
	float cats_velocity;

	/* functional system structures */
	struct Audio *audio;
	struct Graphics *graphics;
	struct Input *input;

	/* resource structures */
	struct AnimationSequences *animationsequences;
	struct SpriteBatch *spritebatch;
	struct Sprites *sprites;
	struct Tiles *tiles;
	struct VideoMap *videomap;

	/* object structures */
	struct MOB *mouse;
	struct MOB *cats [ NUMBER_OF_CATS ];
	struct MOB *coffee;
	struct MOB *bonus;

	/* sub structures */
	struct Stage *stage;
	struct Title *title;

	/* frames per second control */
	struct FramesPerSecond fps;
};



/**
* Allocates memory on the heap for a Game structure.
*
* \param No parameters
* \returns A pointer to the allocated Game structure
*/
struct Game *createGame ( void );



/**
* Frees memory from the heap of a previously allocated Game structure.
*
* \param animation: A pointer to a Game structure
* \returns No return value (void)
*/
void destroyGame ( struct Game *game );



/**
* Initialize Game struct state data.
*
* \param game: A pointer to a Game structure
* \param state: The game state to set
* \returns No return value (void)
*/
void setAndInitializeGameState ( struct Game *game, uint8_t state );



/**
* Sets and initializes the Game state data for displaying the version information.
*
* \param game: A pointer to a Game structure
* \returns No return value (void)
*/
void setAndInitializeGameStateVersion ( struct Game *game );



/**
* Initializes all the animation sequences used in the game.
*
* \param game: A pointer to an AnimationSequences structure
* \returns No return value (void)
*/
void initializeAnimationSequences ( struct AnimationSequences *animationsequences );



/**
* Initializes all the sprites used in the game.
*
* \param game: A pointer to an Sprites structure
* \returns No return value (void)
*/
void initializeSprites ( struct Sprites *sprites );



/**
* Initializes all the game variables required for a new game.
*
* \param game: A pointer to a Game structure
* \returns No return value (void)
*/
void newGame ( struct Game *game );



/**
* Runs the main game loop.
*
* \param game: A pointer to a Game structure
* \returns No return value (void)
*/
void runGame ( struct Game *game );



/**
* Updates the current game state.
*
* \param game: A pointer to a Game structure
* \returns No return value (void)
*/
void updateGameState ( struct Game *game );



/**
* Updates the version display game state.
*
* \param game: A pointer to a Game structure
* \returns No return value (void)
*/
void updateGameStateVersion ( struct Game *game );



/**
* Add points to score variable. Also checks for and adds an extra mouse to reserve if applicable. Updates display on scoreboard.
*
* \param game: A pointer to a Game structure
* \param points: The amount of points to add to the current score
* \returns No return value (void)
*/
void addPoints ( struct Game *game, uint32_t points );



/**
* Add an additional mouse to mouse reserves. Updates display on scoreboard.
*
* \param game: A pointer to a Game structure
* \returns No return value (void)
*/
void addMouse ( struct Game *game );



/**
* Removes one mouse from the mouse reserves. Updates display on scoreboard.
*
* \param game: A pointer to a Game structure
* \returns No return value (void)
*/
void subtractMouse ( struct Game *game );



/**
* Increment stage number. Updates display on scoreboard.
*
* \param game: A pointer to a Game structure
* \returns No return value (void)
*/
void addStage ( struct Game *game );



/**
* Decrement cheese eaten number. Updates display on scoreboard.
*
* \param game: A pointer to a Game structure
* \returns No return value (void)
*/
void subtractCheese ( struct Game *game );



/* fallback*/
void testGame ( struct Game *game );



#endif
