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



#ifndef BONUS_H
#define BONUS_H



#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include "game.h"



#define TIMEOUT_BONUS_WAITING_TO_APPEAR 1200
#define TIMEOUT_BONUS_EFFECT 200
#define ANIMATION_SEQUENCE_BONUS_START 15



extern struct Game game;



enum
{
	STATE_BONUS_WAITING_TO_APPEAR,
	STATE_BONUS_SHOWN,
	STATE_BONUS_EFFECT,
	STATE_BONUS_DONE
};



/**
* Initialize Bonus struct data.
*
* \param game: A pointer to a Game structure
* \returns No return value (void)
*/
void setAndInitializeBonus ( struct Game *game );



/**
* Change state of Bonus struct data in sequence.
*
* \param game: A pointer to a Game structure
* \returns 1 if state is not the final (DONE) state, or zero if state is final (DONE)
*/
uint8_t nextBonusState ( struct Game *game );



/**
* Update state of Bonus struct data.
*
* \param game: A pointer to a Game structure
* \returns 1 if (EFFECT) state is complete, 0 for all other cases
*/
uint8_t updateBonusState ( struct Game *game );



/**
* Sets the display location (cell) of the bonus item on the playfield.
*
* \param game: A pointer to a Game structure
* \returns No return value (void)
*/
void setBonusPosition ( struct Game *game );



/**
* Adds the bonus item sprite to the spritebatch.
*
* \param game: A pointer to a Game structure
* \returns No return value (void)
*/
void renderBonus ( struct Game *game );



#endif
