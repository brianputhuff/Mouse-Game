/**

Mouse Game
Version 0.9.8

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



#ifndef MOB_H
#define MOB_H



#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include "animation.h"



enum
{
	DIRECTION_UP,
	DIRECTION_RIGHT,
	DIRECTION_DOWN,
	DIRECTION_LEFT
};



/**
  The MOB structure defines the general data required for movable objects (MOBs) in the game.
*/
struct MOB
{
	uint8_t state;
	uint8_t direction;
	uint32_t timer;
	uint32_t timeout;
	SDL_FPoint position;
	SDL_FPoint velocity;
	SDL_Point playfield_position;
	SDL_Point target_position;
	SDL_Point collision_box_offset;
	SDL_Rect collision_box;
	struct Animation *animation;
};



/**
* Allocates memory on the heap for a MOB structure.
*
* \param No input parameters
* \returns A pointer to the allocated MOB structure
*/
struct MOB *createMOB ( void );



/**
* Frees memory from the heap of a previously allocated MOB structure.
*
* \param graphics: A pointer to an MOB structure
* \returns No return value (void)
*/
void destroyMOB ( struct MOB *mob );



/**
* Updates a MOB pixel position (x, y) based on velocity.
*
* \param graphics: A pointer to an MOB structure
* \returns No return value (void)
*/
void updateMOBPosition ( struct MOB *mob );



/**
* Updates a MOB playfield cell position (x, y) based on position.
*
* \param graphics: A pointer to an MOB structure
* \returns No return value (void)
*/
void updateMOBPlayfieldPosition ( struct MOB *mob );



/**
* Updates a MOB collision box pixel position (x, y) based on position and offset.
*
* \param graphics: A pointer to an MOB structure
* \returns No return value (void)
*/
void centerMOBCollisionBox ( struct MOB *mob );



/**
* Checks to see if MOB timer has reached zero. If not, the MOB timer is decremented by 1;
*
* \param graphics: A pointer to an MOB structure
* \returns 1 if timeout has occurred, 0 if not
*/
uint8_t checkMOBTimeout ( struct MOB *mob );



/**
* Sets a MOB velocity in both axis.
*
* \param mob: A pointer to an MOB structure
* \param vx: A horizontal velocity (float)
* \param vy: A vertical velocity (float)
* \returns No return value (void)
*/
void setMOBVelocity ( struct MOB *mob, float vx, float vy );



/**
* Sets a MOB pixel position on both axis.
*
* \param mob: A pointer to an MOB structure
* \param x: A horizontal pixel position (float)
* \param y: A vertical pixel position (float)
* \returns No return value (void)
*/
void setMOBPosition ( struct MOB *mob, float x, float y );



/**
* Sets a MOB target pixel position on both axis.
*
* \param mob: A pointer to an MOB structure
* \param x: A target horizontal pixel position (int16)
* \param y: A target vertical pixel position (int16)
* \returns No return value (void)
*/
void setMOBTargetPosition ( struct MOB *mob, int16_t x, int16_t y );



/**
* Sets a MOB playfield cell position on both axis.
*
* \param mob: A pointer to an MOB structure
* \param x: A horizontal playfield cell position (int16)
* \param y: A vertical playfield cell pixel position (int16)
* \returns No return value (void)
*/
void setMOBPlayfieldPosition ( struct MOB *mob, int16_t x, int16_t y );



#endif
