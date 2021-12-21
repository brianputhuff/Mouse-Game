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



#include "input.h"



struct Input *createInput ( )
{
	struct Input *input;



	input = NULL;
	input = malloc ( sizeof ( struct Input ) );
	if ( input == NULL )
	{
		return NULL;
	}

	/* check for controller */
	input->game_controller = NULL;
	input->game_controller = SDL_GameControllerOpen ( 0 );
	if ( input->game_controller != NULL )
	{
		printf ( "Game controller opened.\n" );
	}
	else
	{
		printf ( "Game controller could not be opened.\n" );
	}
	resetInputRegisters ( input );

	return input;
}



void destroyInput ( struct Input *input )
{
	if ( input == NULL )
	{
		return;
	}

	if ( input->game_controller != NULL )
	{
		SDL_GameControllerClose ( input->game_controller );
	}

	free ( input );
}



void resetInputRegisters ( struct Input *input )
{
	input->BUTTON_A = 0;
	input->BUTTON_B = 0;
	input->BUTTON_X = 0;
	input->BUTTON_Y = 0;
	input->BUTTON_L = 0;
	input->BUTTON_R = 0;
	input->BUTTON_GUIDE = 0;
	input->BUTTON_BACK = 0;
	input->DPAD_DOWN = 0;
	input->DPAD_LEFT = 0;
	input->DPAD_RIGHT = 0;
	input->DPAD_UP = 0;
	input->TAB = 0;
	input->ESCAPE = 0;
}



void updateInputRegisters ( struct Input *input )
{
	SDL_Event event;



	while ( SDL_PollEvent ( &event ) > 0 )
	{
		switch ( event.type )
		{
			default:
				break;

			case SDL_QUIT:
				input->ESCAPE = 1;
				break;

			case SDL_CONTROLLERBUTTONDOWN:
			case SDL_CONTROLLERBUTTONUP:
				handleGameControllerButtonEvent ( input, &event );
				break;

			case SDL_CONTROLLERAXISMOTION:
				handleGameControllerAxisMotionEvent ( input, &event );
				break;

			case SDL_KEYDOWN:
			case SDL_KEYUP:
				handleKeyboardEvent ( input, &event );
				break;
		}

	}

}



void handleKeyboardEvent ( struct Input *input, SDL_Event *event )
{
	uint8_t state;



	state = 0;
	if ( ( event->type ) == SDL_KEYDOWN )
	{
		state = 1;
	}
	else
	{
		state = 0;
	}

	switch ( event->key.keysym.sym )
	{
		default:
			break;

		case SDLK_UP:
		case SDLK_w:
			input->DPAD_UP = state;
			break;

		case SDLK_DOWN:
		case SDLK_s:
			input->DPAD_DOWN = state;
			break;

		case SDLK_LEFT:
		case SDLK_a:
			input->DPAD_LEFT = state;
			break;

		case SDLK_RIGHT:
		case SDLK_d:
			input->DPAD_RIGHT = state;
			break;

		case SDLK_z:
		case SDLK_h:
			input->BUTTON_A = state;
			break;

		case SDLK_x:
		case SDLK_j:
			input->BUTTON_B = state;
			break;

		case SDLK_c:
		case SDLK_k:
			input->BUTTON_X = state;
			break;

		case SDLK_v:
		case SDLK_l:
			input->BUTTON_Y = state;
			break;

		case SDLK_TAB:
			input->TAB = state;
			input->BUTTON_GUIDE = state;
			break;

		case SDLK_ESCAPE:
			input->ESCAPE = state;
			break;

		case SDLK_COMMA:
			input->BUTTON_L = state;
			break;

		case SDLK_PERIOD:
			input->BUTTON_R = state;
			break;
	}
}



void handleGameControllerButtonEvent ( struct Input *input, SDL_Event *event )
{
	uint8_t state;
	


	state = 0;
	if ( ( event->type ) == SDL_CONTROLLERBUTTONDOWN )
	{
		state = 1;
	}
	else
	{
		state = 0;
	}

	switch ( event->cbutton.button )
	{
		default:
			break;

		/* DPAD */
		case SDL_CONTROLLER_BUTTON_DPAD_UP:
			input->DPAD_UP = state;
			break;

		case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
			input->DPAD_RIGHT = state;
			break;

		case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
			input->DPAD_DOWN = state;
			break;

		case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
			input->DPAD_LEFT = state;
			break;

		/* BUTTONS */
		case SDL_CONTROLLER_BUTTON_A:
			input->BUTTON_A = state;
			break;

		case SDL_CONTROLLER_BUTTON_B:
			input->BUTTON_B = state;
			break;

		case SDL_CONTROLLER_BUTTON_X:
			input->BUTTON_X = state;
			break;

		case SDL_CONTROLLER_BUTTON_Y:
			input->BUTTON_Y = state;
			break;

		case SDL_CONTROLLER_BUTTON_LEFTSHOULDER:
			input->BUTTON_L = state;
			break;

		case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
			input->BUTTON_R = state;
			break;

		case SDL_CONTROLLER_BUTTON_GUIDE:
			input->BUTTON_GUIDE = state;
			input->TAB = state;
			break;

		case SDL_CONTROLLER_BUTTON_BACK:
			input->BUTTON_BACK = state;
			break;

		case SDL_CONTROLLER_BUTTON_START:
			input->BUTTON_START = state;
			input->TAB = state;
			break;
	}
}



void handleGameControllerAxisMotionEvent ( struct Input *input, SDL_Event *event )
{
	if ( event->caxis.axis == SDL_CONTROLLER_AXIS_LEFTX )
	{
		if ( event->caxis.value <= ( -( DEADZONE ) ) )
		{
			input->DPAD_LEFT = 1;
			input->DPAD_RIGHT = 0;
		}
		else if ( event->caxis.value >= ( DEADZONE ) )
		{
			input->DPAD_LEFT = 0;
			input->DPAD_RIGHT = 1;
		}
		else
		{
			input->DPAD_LEFT = 0;
			input->DPAD_RIGHT = 0;
		}
	}
	else if ( event->caxis.axis == SDL_CONTROLLER_AXIS_LEFTY )
	{
		if ( event->caxis.value <= ( -( DEADZONE ) ) )
		{
			input->DPAD_UP = 1;
			input->DPAD_DOWN = 0;
		}
		else if ( event->caxis.value >= ( DEADZONE ) )
		{
			input->DPAD_UP = 0;
			input->DPAD_DOWN = 1;
		}
		else
		{
			input->DPAD_UP = 0;
			input->DPAD_DOWN = 0;
		}
	}
	else
	{
		;
	}
}

