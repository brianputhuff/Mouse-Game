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



#ifndef STAGE_H
#define STAGE_H



#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include "game.h"



#define NUMBER_OF_STAGES 16
#define WALLS_TO_GENERATE_PER_STAGE 50
#define CHEESE_TO_EAT_PER_STAGE 50
#define TIMEOUT_SNAIL_UPDATE 4



extern struct Game game;



enum
{
	TILE_FLOOR,
	TILE_WALL,
	TILE_CHEESE,
	TILE_BONUS
};



struct Snail
{
	uint8_t i;
	uint8_t counter;
	uint8_t direction;
	SDL_Point node;
	SDL_Point shift;
};



/**
* Initializes the Snail structure data for the snail wipe transition.
*
* \param A pointer to a Snail structure
* \returns A pointer to the Sprites structure
*/
void initializeSnail ( struct Snail *snail );



/**
* Updates the Snail structure data for the snail wipe transition.
*
* \param A pointer to a Snail structure
* \returns A pointer to the Sprites structure
*/
uint8_t updateSnail ( struct Game *game );



struct Playfield
{
	uint8_t *data;
	uint8_t w;
	uint8_t h;
	uint16_t a;
	struct Snail snail;
};



/**
* Allocates memory on the heap for a Playfield structure.
*
* \param width: The horizontal width of the playfield in 2 x 2 tile cells
* \param height: The vertical height of the playfield in 2 x 2 tile cells
* \returns A pointer to the Sprites structure
*/
struct Playfield *createPlayfield ( uint8_t width, uint8_t height );



/**
* Frees memory from the heap of a previously allocated Playfield structure.
*
* \param playfield: A pointer to a Playfield structure
* \returns No return value (void)
*/
void destroyPlayfield ( struct Playfield *playfield );



/**
* Populates the Playfield cells with walls and cheese.
*
* \param playfield: A pointer to a Playfield structure
* \returns No return value (void)
*/
void generatePlayfield ( struct Playfield *playfield );



/**
* Checks neighboring corner cells of the Playfield to see if the contain and empty space or a wall.
*
* \param playfield: A pointer to a Playfield structure
* \returns 1 if all corners are clear, 0 if any corner has a wall tile
*/
uint8_t verifyCornersAreClear ( struct Playfield *playfield, uint16_t i );



/**
* Copies all playfield cells to a video map structure.
*
* \param playfield: A pointer to a Playfield structure
* \param videomap: A pointer to a VideoMap structure
* \param wall_type: A wall type identifier value for the video map to draw a specific set of tiles for wall
* \returns No return value (void)
*/
void copyPlayFieldToVideoMap ( struct Playfield *playfield, struct VideoMap *videomap, uint8_t wall_type );



/**
* Copies a single playfield cell to a video map structure at a relational position.
*
* \param playfield: A pointer to a Playfield structure
* \param px: Horizontal playfield cell position
* \param py: Vertical playfield cell position
* \param videomap: A pointer to a VideoMap structure
* \param wall_type: A wall type identifier value for the video map to draw a specific set of tiles for wall
* \returns No return value (void)
*/
void copyPlayfieldCellToVideoMap ( struct Playfield *playfield, uint16_t px, uint16_t py, struct VideoMap *videomap, uint8_t wall_type );



/**
* Gets a single playfield cell value.
*
* \param playfield: A pointer to a Playfield structure
* \param x: Horizontal playfield cell position
* \param y: Vertical playfield cell position
* \returns The playfield cell value
*/
uint8_t getPlayfieldCell ( struct Playfield *playfield, uint16_t x, uint16_t y );



/**
* Sets a single playfield cell value.
*
* \param playfield: A pointer to a Playfield structure
* \param x: Horizontal playfield cell position
* \param y: Vertical playfield cell position
* \param value: The value to set for the playfield cell
* \returns No return value (void)
*/
void setPlayfieldCell ( struct Playfield *playfield, uint16_t x, uint16_t y, uint8_t value );



/**
* Sets a playfield cell values to 0.
*
* \param playfield: A pointer to a Playfield structure
* \returns No return value (void)
*/
void clearPlayfield ( struct Playfield *playfield );



/**
* Checks to see if an entire playfield row consists of only wall tiles.
*
* \param playfield: A pointer to a Playfield structure
* \param x: target x cell on playfield to skip
* \param y: target y cell on playfield
* \returns 0 if there is at least one empty space, 1 if all checked spaces are walls
*/
uint8_t greatWallHorizontalCheck ( struct Playfield *playfield, uint16_t x, uint16_t y );



/**
* Checks to see if an entire playfield column consists of only wall tiles.
*
* \param playfield: A pointer to a Playfield structure
* \param x: target x cell on playfield
* \param y: target y cell on playfield to skip
* \returns 0 if there is at least one empty space, 1 if all checked spaces are walls
*/
uint8_t greatWallVerticalCheck ( struct Playfield *playfield, uint16_t x, uint16_t y );




struct Stage
{
	uint8_t stage_number;
	uint8_t wall_tile;
	uint8_t bgm;
	struct Playfield *playfield;
};



/**
* Allocates memory on the heap for a Stage structure.
*
* \param No input arguments
* \returns A pointer to the Stage structure
*/
struct Stage *createStage ( void );



/**
* Frees memory from the heap of a previously allocated Stage structure.
*
* \param playfield: A pointer to a Stage structure
* \returns No return value (void)
*/
void destroyStage ( struct Stage *stage );



/**
* Sets and initializes the stage in state.
*
* \param playfield: A pointer to a Game structure
* \returns No return value (void)
*/
void setAndInitializeGameStateStageIn ( struct Game *game );



/**
* Sets and initializes the stage out state.
*
* \param playfield: A pointer to a Game structure
* \returns No return value (void)
*/
void setAndInitializeGameStateStageOut ( struct Game *game );



/**
* Sets and initializes the stage complete state.
*
* \param playfield: A pointer to a Game structure
* \returns No return value (void)
*/
void setAndInitializeGameStateStageComplete ( struct Game *game );



/**
* Updates the stage in state.
*
* \param playfield: A pointer to a Game structure
* \returns No return value (void)
*/
void updateGameStateStageIn ( struct Game *game );



/**
* Updates the stage out state.
*
* \param playfield: A pointer to a Game structure
* \returns No return value (void)
*/
void updateGameStateStageOut ( struct Game *game );



/**
* Updates the stage Complete state.
*
* \param playfield: A pointer to a Game structure
* \returns No return value (void)
*/
void updateGameStateStageComplete ( struct Game *game );



#endif
