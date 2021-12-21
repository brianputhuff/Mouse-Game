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



#ifndef TITLE_H
#define TITLE_H



#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include "game.h"



#define TIMEOUT_TITLE_FLASHING_MESSAGE_SHOWN 12
#define TIMEOUT_TITLE_FLASHING_MESSAGE_NOT_SHOWN 12
#define TIMEOUT_TITLE_STEP_MESSAGE 180
#define TIMEOUT_TITLE_STEP_SCREEN 600



struct Title
{
	uint8_t step_screen;
	uint8_t step_message;

	uint8_t state_music_started;
	uint8_t state_flashing_message;

	uint32_t timer_flashing_message;

	uint32_t timer_step_screen;
	uint32_t timer_step_message;
};



/**
* Allocates memory on the heap for a Title structure.
*
* \param No input parameters (void)
* \returns A pointer to the Title structure
*/
struct Title *createTitle ( void );



/**
* Frees memory from the heap of a previously allocated Title structure.
*
* \param sequence: A pointer to an Title structure
* \returns No return value (void)
*/
void destroyTitle ( struct Title *title );



/**
* Sets title state to the main title screen and initializes Title structure data.
*
* \param sequence: A pointer to a Game structure
* \returns No return value (void)
*/
void setAndInitializeGameStateTitlePrimary ( struct Game *game );



/**
* Sets title state to instructions title screen and initializes Title structure data.
*
* \param sequence: A pointer to a Game structure
* \returns No return value (void)
*/
void setAndInitializeGameStateTitleSecondary ( struct Game *game );



/**
* Sets title state to the points title screen and initializes Title structure data.
*
* \param sequence: A pointer to a Game structure
* \returns No return value (void)
*/
void setAndInitializeGameStateTitleTertiary ( struct Game *game );



/**
* Sets title state to the controls title screen and initializes Title structure data.
*
* \param sequence: A pointer to a Game structure
* \returns No return value (void)
*/
void setAndInitializeGameStateTitleQuaternary ( struct Game *game );



/**
* Updates the main title screen.
*
* \param sequence: A pointer to a Game structure
* \returns No return value (void)
*/
void updateGameStateTitlePrimary ( struct Game *game );



/**
* Updates the instructions title screen.
*
* \param sequence: A pointer to a Game structure
* \returns No return value (void)
*/
void updateGameStateTitleSecondary ( struct Game *game );



/**
* Updates the points title screen.
*
* \param sequence: A pointer to a Game structure
* \returns No return value (void)
*/
void updateGameStateTitleTertiary ( struct Game *game );



/**
* Updates the controls title screen.
*
* \param sequence: A pointer to a Game structure
* \returns No return value (void)
*/
void updateGameStateTitleQuaternary ( struct Game *game );



/**
* Sets a tiled border around the perimeter of the video map display.
*
* \param sequence: A pointer to a Game structure
* \returns No return value (void)
*/
void drawTitleBorder ( struct Game *game );



#endif
