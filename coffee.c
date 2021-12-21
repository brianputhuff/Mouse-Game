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



#include "coffee.h"



void setAndInitializeCoffee ( struct Game *game )
{
	/* set state */
	game->coffee->state = STATE_COFFEE_WAITING_TO_APPEAR;

	/* reset velocity */
	setMOBVelocity ( game->coffee, 0.0f, 0.0f );

	/* reset collision box */
	game->coffee->collision_box_offset.x = 2;
	game->coffee->collision_box_offset.y = 2;
	game->coffee->collision_box.w = 12;
	game->coffee->collision_box.h = 12;

	/* reset playfield position */
	setCoffeePositionOnPlayfield ( game );

	/* reset timers */
	game->coffee->timer = TIMEOUT_COFFEE_WAITING_TO_APPEAR;
	game->coffee->timeout = TIMEOUT_COFFEE_WAITING_TO_APPEAR;

	/* reset animation */
	setAnimationTimer ( game->coffee->animation, ANIMATION_TIMEOUT_COFFEE );
	setAnimationTimeout ( game->coffee->animation, ANIMATION_TIMEOUT_COFFEE );
	setAnimationSequenceIndex ( game->animationsequences, game->coffee->animation, 14 );
	setAnimationFrame ( game->animationsequences, game->coffee->animation, 0 );
}



uint8_t nextCoffeeState ( struct Game *game )
{
	if ( game->coffee->state < STATE_COFFEE_DONE )
	{
		game->coffee->state++;

		if ( game->coffee->state == STATE_COFFEE_SHOWN )
		{
			setCoffeePositionOnPlayfield ( game );
		}

		if ( game->coffee->state == STATE_COFFEE_EFFECT )
		{
			game->coffee->timer = TIMEOUT_COFFEE_EFFECT;
		}

		return 1;
	}

	return 0;
}



uint8_t updateCoffeeState ( struct Game *game )
{
	switch ( game->coffee->state )
	{
		case STATE_COFFEE_WAITING_TO_APPEAR:
			if ( game->coffee->timer == 0 )
			{
				nextCoffeeState ( game );
			}
			else
			{
				game->coffee->timer--;
			}
			break;

		case STATE_COFFEE_SHOWN:
			updateAnimation ( game->animationsequences, game->coffee->animation );
			break;

		case STATE_COFFEE_EFFECT:
			if ( game->coffee->timer == 0 )
			{
				nextCoffeeState ( game );
				return 1;
			}
			else
			{
				game->coffee->timer--;
			}
			break;

		default:
		case STATE_COFFEE_DONE:
			break;
	}

	return 0;
}



void setCoffeePositionOnPlayfield ( struct Game *game )
{
	uint8_t exception;
	SDL_Rect exclusion_box;



	/* set exclusion box around mouse tile_position */
	exclusion_box.x = game->mouse->playfield_position.x - 3;
	exclusion_box.y = game->mouse->playfield_position.y - 3;
	exclusion_box.w = 7;
	exclusion_box.h = 7;
	exception = 0;
	/* choose random location that is outside the exclusion zone and not a wall */
	do
	{
		game->coffee->playfield_position.x = ( rand ( ) % ( game->stage->playfield->w - 2 ) ) + 1;
		game->coffee->playfield_position.y = ( rand ( ) % ( game->stage->playfield->h - 2 ) ) + 1;

		if ( getPlayfieldCell ( game->stage->playfield, game->coffee->playfield_position.x, game->coffee->playfield_position.y ) == TILE_WALL )
		{
			exception = 1;
		}
		else if ( getPlayfieldCell ( game->stage->playfield, game->coffee->playfield_position.x, game->coffee->playfield_position.y ) == TILE_CHEESE )
		{
			exception = 1;
		}
		else if ( ( SDL_PointInRect ( &game->coffee->playfield_position, &exclusion_box ) == SDL_TRUE ) )
		{
			exception = 1;
		}
		else
		{
			exception = 0;
		}
	} while ( exception == 1 );

	/* set position based on tile selection */
	game->coffee->position.x = ( float ) ( game->coffee->playfield_position.x * 16 );
	game->coffee->position.y = ( float ) ( game->coffee->playfield_position.y * 16 );
	game->coffee->position.y += 8;

	/* update collision box */
	centerMOBCollisionBox ( game->coffee );
}



void renderCoffee ( struct Game *game )
{
	if ( game->coffee->state == STATE_COFFEE_SHOWN )
	{
		addSpriteToSpriteBatch
		(
			game->spritebatch,
			getAnimationSpriteID ( game->animationsequences, game->coffee->animation ),
			( int16_t ) game->coffee->position.x,
			( int16_t ) game->coffee->position.y,
			1,
			-1
		);
	}
}
