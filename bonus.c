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



#include "bonus.h"



void setAndInitializeBonus ( struct Game *game )
{
	uint8_t type;



	/* reset state and timers */
	game->bonus->state = STATE_BONUS_WAITING_TO_APPEAR;
	game->bonus->timer = TIMEOUT_BONUS_WAITING_TO_APPEAR;

	/* select a type */
	type = rand ( ) % 4;

	/* reset animation */
	setAnimationSequenceIndex ( game->animationsequences, game->bonus->animation, ANIMATION_SEQUENCE_BONUS_START + ( 2 * type ) );
	setAnimationFrame ( game->animationsequences, game->bonus->animation, 0 );

	/* reset position and collision box */
	game->bonus->collision_box_offset.x = 2;
	game->bonus->collision_box_offset.y = 2;
	game->bonus->collision_box.w = 12;
	game->bonus->collision_box.h = 12;
}



uint8_t nextBonusState ( struct Game *game )
{
	if ( game->bonus->state < STATE_BONUS_DONE )
	{
		game->bonus->state++;

		if ( game->bonus->state == STATE_BONUS_SHOWN )
		{
			setBonusPosition ( game );
		}

		if ( game->bonus->state == STATE_BONUS_EFFECT )
		{
			game->bonus->timer = TIMEOUT_BONUS_EFFECT;
		}

		return 1;
	}

	return 0;
}



uint8_t updateBonusState ( struct Game *game )
{
	switch ( game->bonus->state )
	{
		case STATE_BONUS_WAITING_TO_APPEAR:
			if ( game->bonus->timer == 0 )
			{
				nextBonusState ( game );
			}
			else
			{
				game->bonus->timer--;
			}
			break;

		case STATE_BONUS_EFFECT:
			if ( game->bonus->timer == 0 )
			{
				nextBonusState ( game );
				return 1;
			}
			else
			{
				game->bonus->timer--;
			}
			break;

		default:
		case STATE_BONUS_SHOWN:
		case STATE_BONUS_DONE:
			break;
	}

	return 0;
}



void setBonusPosition ( struct Game *game )
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
		game->bonus->playfield_position.x = ( rand ( ) % ( game->stage->playfield->w - 2 ) ) + 1;
		game->bonus->playfield_position.y = ( rand ( ) % ( game->stage->playfield->h - 2 ) ) + 1;

		/* if coffee is shown, ensure the bonus doesn't overlap */
		if ( ( game->coffee->state == STATE_BONUS_SHOWN ) && 
			( ( game->bonus->playfield_position.x == game->coffee->playfield_position.x ) &&
			( game->bonus->playfield_position.y == game->coffee->playfield_position.y ) ) )
		{
			exception = 1;
		}
		else if ( getPlayfieldCell ( game->stage->playfield, game->bonus->playfield_position.x, game->bonus->playfield_position.y ) == TILE_WALL )
		{
			exception = 1;
		}
		else if ( getPlayfieldCell ( game->stage->playfield, game->bonus->playfield_position.x, game->bonus->playfield_position.y ) == TILE_CHEESE )
		{
			exception = 1;
		}
		else if ( ( SDL_PointInRect ( &game->bonus->playfield_position, &exclusion_box ) == SDL_TRUE ) )
		{
			exception = 1;
		}
		else
		{
			exception = 0;
		}
	} while ( exception == 1 );

	/* set position based on tile selection */
	game->bonus->position.x = ( float ) ( game->bonus->playfield_position.x * 16 );
	game->bonus->position.y = ( float ) ( game->bonus->playfield_position.y * 16 );
	game->bonus->position.y += 8;

	/* update collision box */
	centerMOBCollisionBox ( game->bonus );
}



void renderBonus ( struct Game *game )
{
	uint8_t s;


	if ( game->bonus->state == STATE_BONUS_SHOWN )
	{
		s = getAnimationSequenceIndex ( game->bonus->animation );
		/* render main image */
		addSpriteToSpriteBatch
		(
			game->spritebatch,
			getAnimationSpriteID ( game->animationsequences, game->bonus->animation ),
			( uint16_t ) game->bonus->position.x,
			( uint16_t ) game->bonus->position.y,
			1,
			-1
		);

		/* render mask image */
		setAnimationSequenceIndex ( game->animationsequences, game->bonus->animation, ( s + 1 ) );
		addSpriteToSpriteBatch
		(
			game->spritebatch,
			getAnimationSpriteID ( game->animationsequences, game->bonus->animation ),
			( uint16_t ) game->bonus->position.x,
			( uint16_t ) game->bonus->position.y,
			-1,
			1
		);
		setAnimationSequenceIndex ( game->animationsequences, game->bonus->animation, ( s ) );
	}
}