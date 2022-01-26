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



#ifndef CAT_H
#define CAT_H



#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include "game.h"



#define VELOCITY_CATS_FAST 1.5f
#define VELOCITY_CATS_NORMAL 1.0f
#define VELOCITY_CATS_SLOW  0.5f



#define ANIMATION_TIMEOUT_CATS_FAST 2
#define ANIMATION_TIMEOUT_CATS_NORMAL 4
#define ANIMATION_TIMEOUT_CATS_SLOW 8
#define ANIMATION_TIMEOUT_CATS_DANCING 8
#define ANIMATION_TIMEOUT_CATS_SLEEPING 4



#define ANIMATION_SEQUENCE_CAT_MOVING_LEFT 23
#define ANIMATION_SEQUENCE_CAT_MOVING_RIGHT 25
#define ANIMATION_SEQUENCE_CAT_DANCING 27
#define ANIMATION_SEQUENCE_CAT_SLEEPING_LEFT 29
#define ANIMATION_SEQUENCE_CAT_SLEEPING_RIGHT 31



enum
{
	STATE_CAT_IDLE,
	STATE_CAT_MOVING_UP,
	STATE_CAT_MOVING_RIGHT,
	STATE_CAT_MOVING_DOWN,
	STATE_CAT_MOVING_LEFT,
	STATE_CAT_DANCING,
	STATE_CAT_SLEEPING
};



/**
* Initialize Cats.
*
* \param game: A pointer to a Game structure
* \returns No return value (void)
*/
void setAndInitializeCats ( struct Game *game );



/**
* Initialize a Cat to idle state.
*
* \param game: A pointer to a Game structure
* \param cat: index of cat to be initialized
* \returns No return value (void)
*/
void setAndInitializeCatStateIdle ( struct Game *game, uint8_t cat );



/**
* Initialize a Cat to moving up state.
*
* \param game: A pointer to a Game structure
* \param cat: index of cat to be initialized
* \param distance: distance to move cat, sets to target position
* \returns No return value (void)
*/
void setAndInitializeCatStateMovingUp ( struct Game *game, uint8_t cat, uint16_t distance );



/**
* Initialize a Cat to moving right state.
*
* \param game: A pointer to a Game structure
* \param cat: index of cat to be initialized
* \param distance: distance to move cat, sets to target position
* \returns No return value (void)
*/
void setAndInitializeCatStateMovingRight ( struct Game *game, uint8_t cat, uint16_t distance );



/**
* Initialize a Cat to moving down state.
*
* \param game: A pointer to a Game structure
* \param cat: index of cat to be initialized
* \param distance: distance to move cat, sets to target position
* \returns No return value (void)
*/
void setAndInitializeCatStateMovingDown ( struct Game *game, uint8_t cat, uint16_t distance );



/**
* Initialize a Cat to moving left state.
*
* \param game: A pointer to a Game structure
* \param cat: index of cat to be initialized
* \param distance: distance to move cat, sets to target position
* \returns No return value (void)
*/
void setAndInitializeCatStateMovingLeft ( struct Game *game, uint8_t cat, uint16_t distance );



/**
* Initialize all Cats to dancing state.
*
* \param game: A pointer to a Game structure
* \returns No return value (void)
*/
void setAndInitializeCatsStateDancing ( struct Game *game );



/**
* Initialize all Cats to sleeping state.
*
* \param game: A pointer to a Game structure
* \returns No return value (void)
*/
void setAndInitializeCatsStateSleeping ( struct Game *game );



/**
* Update all Cats.
*
* \param game: A pointer to a Game structure
* \returns No return value (void)
*/
void updateCats ( struct Game *game );



/**
* Update Cat moving up state.
*
* \param game: A pointer to a Game structure
* \param cat: index of cat to be updated
* \returns No return value (void)
*/
void updateCatStateMovingUp ( struct Game *game, uint8_t cat );



/**
* Update Cat moving right state.
*
* \param game: A pointer to a Game structure
* \param cat: index of cat to be updated
* \returns No return value (void)
*/
void updateCatStateMovingRight ( struct Game *game, uint8_t cat );



/**
* Update Cat moving down state.
*
* \param game: A pointer to a Game structure
* \param cat: index of cat to be updated
* \returns No return value (void)
*/
void updateCatStateMovingDown ( struct Game *game, uint8_t cat );



/**
* Update Cat moving left state.
*
* \param game: A pointer to a Game structure
* \param cat: index of cat to be updated
* \returns No return value (void)
*/
void updateCatStateMovingLeft ( struct Game *game, uint8_t cat );



/**
* Update all Cats dancing state.
*
* \param game: A pointer to a Game structure
* \returns No return value (void)
*/
void updateCatsStateDancing ( struct Game *game );



/**
* Update all Cats sleeping state.
*
* \param game: A pointer to a Game structure
* \returns No return value (void)
*/
void updateCatsStateSleeping ( struct Game *game );



/**
* Checks to see if a cat can move in a specific direction.
*
* \param game: A pointer to a Game structure
* \param cat: index of cat
* \param direction: one of four directions (based on enum: UP, RIGHT, DOWN, LEFT)
* \returns 1 if cat can move in the direction, 0 if not
*/
uint8_t checkCatMove ( struct Game *game, uint8_t cat, uint8_t direction );



/**
* Selects a random direction (based on enum: UP, RIGHT, DOWN, LEFT) for the cat to move.
*
* \param game: A pointer to a Game structure
* \param cat: index of cat
* \returns No return value (void)
*/
void selectCatDirection ( struct Game *game, uint8_t cat );



/**
* Gets the maximum of tiles that are possible for the cat to move in a specific direction.
*
* \param game: A pointer to a Game structure
* \param cat: index of cat
* \param direction: one of four directions (based on enum: UP, RIGHT, DOWN, LEFT)
* \returns The maximum number of cells the cat can move in the requested direction
*/
uint16_t getCatLinearDistance ( struct Game *game, uint8_t cat, uint8_t direction );



/**
* Sets the start position (cell) of each cat on the playfield.
*
* \param game: A pointer to a Game structure
* \returns No return value (void)
*/
void setCatsStartPosition ( struct Game *game );



/**
* Sets the velocity of all the cats.
*
* \param game: A pointer to a Game structure
* \param velocity_setting: An absolute (non-negative) velocity value
* \returns No return value (void)
*/
void setCatsVelocity ( struct Game *game, float velocity_setting );



/**
* Adds the cat sprites to the spritebatch.
*
* \param game: A pointer to a Game structure
* \returns No return value (void)
*/
void renderCats ( struct Game *game );



#endif
