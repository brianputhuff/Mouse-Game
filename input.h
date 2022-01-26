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



#ifndef INPUT_H
#define INPUT_H



#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <SDL2/SDL.h>



#define DEADZONE 15000



struct Input
{
	/* input registers */
	uint16_t DPAD_UP      : 1;
	uint16_t DPAD_DOWN    : 1;
	uint16_t DPAD_LEFT    : 1;
	uint16_t DPAD_RIGHT   : 1;
	uint16_t BUTTON_A     : 1;
	uint16_t BUTTON_B     : 1;
	uint16_t BUTTON_X     : 1;
	uint16_t BUTTON_Y     : 1;
	uint16_t BUTTON_L     : 1;
	uint16_t BUTTON_R     : 1;
	uint16_t BUTTON_START : 1;
	uint16_t BUTTON_GUIDE : 1;
	uint16_t BUTTON_BACK  : 1;
	uint16_t ESCAPE       : 1;
	uint16_t TAB          : 1;
	uint16_t UNUSED       : 1;

	/* game controller */
	SDL_GameController *game_controller;
};



/**
* Allocates memory on the heap for an Input structure.
*
* \param No input parameters
* \returns A pointer to the allocated Input structure
*/
struct Input *createInput ( );



/**
* Frees memory from the heap of a previously allocated Input structure.
*
* \param graphics: A pointer to an Input structure
* \returns No return value (void)
*/
void destroyInput ( struct Input *input );



/**
* Resets all the bitfields in the Input structure registers to 0 (off).
*
* \param graphics: A pointer to an Input structure
* \returns No return value (void)
*/
void resetInputRegisters ( struct Input *input );



/**
* Checks events for input signals and updates Input structure bitfield registers accordingly.
*
* \param graphics: A pointer to an Input structure
* \returns No return value (void)
*/
void updateInputRegisters ( struct Input *input );



/**
* Checks keyboard events for specific input signals and updates Input structure bitfield registers accordingly.
*
* \param graphics: A pointer to an Input structure
* \returns No return value (void)
*/
void handleKeyboardEvent ( struct Input *input, SDL_Event *event );



/**
* Checks game controller button events for specific input signals and updates Input structure bitfield registers accordingly.
*
* \param graphics: A pointer to an Input structure
* \returns No return value (void)
*/
void handleGameControllerButtonEvent ( struct Input *input, SDL_Event *event );



/**
* Checks game controller analog joystick events for specific input signals and updates Input structure bitfield registers accordingly.
*
* \param graphics: A pointer to an Input structure
* \returns No return value (void)
*/
void handleGameControllerAxisMotionEvent ( struct Input *input, SDL_Event *event );



#endif
