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



#ifndef MOUSE_H
#define MOUSE_H



#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include "game.h"
#include "mob.h"



/* animation timeouts */
#define ANIMATION_TIMEOUT_MOUSE_DANCING 8
#define ANIMATION_TIMEOUT_MOUSE_DEATH 8
#define ANIMATION_TIMEOUT_MOUSE_MOVE 4



/* animation sequence indices */
#define ANIMATION_SEQUENCE_MOUSE_UP 0
#define ANIMATION_SEQUENCE_MOUSE_RIGHT 2
#define ANIMATION_SEQUENCE_MOUSE_DOWN 4
#define ANIMATION_SEQUENCE_MOUSE_LEFT 6
#define ANIMATION_SEQUENCE_MOUSE_DANCING 8
#define ANIMATION_SEQUENCE_MOUSE_DEATH_LEFT 10
#define ANIMATION_SEQUENCE_MOUSE_DEATH_RIGHT 12



/* mouse states */
enum
{
	STATE_MOUSE_IDLE,
	STATE_MOUSE_MOVING_UP,
	STATE_MOUSE_MOVING_DOWN,
	STATE_MOUSE_MOVING_LEFT,
	STATE_MOUSE_MOVING_RIGHT,
	STATE_MOUSE_DANCING,
	STATE_MOUSE_DEATH
};



/**
* Initializes mouse struct data to default settings.
*
* \param game: A pointer to a Game structure
* \returns No return value (void)
*/
void setAndInitializeMouse ( struct Game *game );



/**
* Initializes mouse struct data to idle state.
*
* \param game: A pointer to a Game structure
* \returns No return value (void)
*/
void setAndInitializeMouseStateIdle ( struct Game *game );



/**
* Initializes mouse struct data to moving up state.
*
* \param game: A pointer to a Game structure
* \returns No return value (void)
*/
void setAndInitializeMouseStateMovingUp ( struct Game *game );



/**
* Initializes mouse struct data to moving right state.
*
* \param game: A pointer to a Game structure
* \returns No return value (void)
*/
void setAndInitializeMouseStateMovingRight ( struct Game *game );



/**
* Initializes mouse struct data to moving down state.
*
* \param game: A pointer to a Game structure
* \returns No return value (void)
*/
void setAndInitializeMouseStateMovingDown ( struct Game *game );



/**
* Initializes mouse struct data to moving left state.
*
* \param game: A pointer to a Game structure
* \returns No return value (void)
*/
void setAndInitializeMouseStateMovingLeft ( struct Game *game );



/**
* Initializes mouse struct data to dancing state.
*
* \param game: A pointer to a Game structure
* \returns No return value (void)
*/
void setAndInitializeMouseStateDancing ( struct Game *game );



/**
* Initializes mouse struct data to dying state.
*
* \param game: A pointer to a Game structure
* \returns No return value (void)
*/
void setAndInitializeMouseStateDeath ( struct Game *game );



/**
* Update mouse struct data per state.
*
* \param game: A pointer to a Game structure
* \returns No return value (void)
*/
uint8_t updateMouseState ( struct Game *game );



/**
* Update mouse struct data per moving up state.
*
* \param game: A pointer to a Game structure
* \returns No return value (void)
*/
uint8_t updateMouseStateMovingUp ( struct Game *game );


/**
* Update mouse struct data per right state.
*
* \param game: A pointer to a Game structure
* \returns No return value (void)
*/
uint8_t updateMouseStateMovingRight ( struct Game *game );



/**
* Update mouse struct data per moving down state.
*
* \param game: A pointer to a Game structure
* \returns No return value (void)
*/
uint8_t updateMouseStateMovingDown ( struct Game *game );



/**
* Update mouse struct data per moving left state.
*
* \param game: A pointer to a Game structure
* \returns No return value (void)
*/
uint8_t updateMouseStateMovingLeft ( struct Game *game );



/**
* Update mouse struct data per dancing state.
*
* \param game: A pointer to a Game structure
* \returns 1 if sequence has completed, 0 otherwise
*/
uint8_t updateMouseStateDancing ( struct Game *game );



/**
* Update mouse struct data per dying state.
*
* \param game: A pointer to a Game structure
* \returns 1 if sequence has completed, 0 otherwise
*/
uint8_t updateMouseStateDeath ( struct Game *game );



/**
* Adds the mouse sprite to the spritebatch for rendering.
*
* \param game: A pointer to a Game structure
* \returns No return value (void)
*/
void renderMouse ( struct Game *game );



/**
* Checks to see if a potential mouse move direction is valid.
*
* \param game: A pointer to a Game structure
* \returns 1 if move is valid (empty playfield cell), 0 if not (walled playfield cell)
*/
uint8_t checkMouseMove ( struct Game *game, uint8_t direction );



#endif
