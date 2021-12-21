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



#include "cat.h"



void setAndInitializeCats ( struct Game *game )
{
	uint8_t i;



	game->cats_velocity = VELOCITY_CATS_NORMAL;
	setCatsStartPosition ( game );
	for ( i = 0; i < NUMBER_OF_CATS; i++ )
	{
		/* reset position and velocity */
		setMOBTargetPosition ( game->cats [ i ], 0, 0 );
		setMOBPlayfieldPosition ( game->cats [ i ], 0, 0 );
		game->cats [ i ]->collision_box.w = 12;
		game->cats [ i ]->collision_box.h = 12;
		game->cats [ i ]->collision_box_offset.x = 2;
		game->cats [ i ]->collision_box_offset.y = 2;
		centerMOBCollisionBox ( game->cats [ i ] );
		selectCatDirection ( game, i );

		/* reset general purpose counter */
		game->cats [ i ]->timer = 0;

		/* reset animation */
		setAnimationSequenceIndex ( game->animationsequences, game->cats [ i ]->animation, ANIMATION_SEQUENCE_CAT_MOVING_RIGHT );
		setAnimationFrame ( game->animationsequences, game->cats [ i ]->animation, 0 );
		setAnimationTimer ( game->cats [ i ]->animation, ANIMATION_TIMEOUT_CATS_NORMAL );
		setAnimationTimeout ( game->cats [ i ]->animation, ANIMATION_TIMEOUT_CATS_NORMAL );
	}

}



void setAndInitializeCatStateIdle ( struct Game *game, uint8_t cat )
{
	game->cats [ cat ]->state = STATE_CAT_IDLE;
	setMOBVelocity ( game->cats [ cat ], 0.0f, 0.0f );
}



void setAndInitializeCatStateMovingUp ( struct Game *game, uint8_t cat, uint16_t distance )
{
	game->cats [ cat ]->state = STATE_CAT_MOVING_UP;
	setMOBTargetPosition ( game->cats [ cat ], ( uint16_t ) game->cats [ cat ]->position.x, ( ( uint16_t ) game->cats [ cat ]->position.y - ( distance * 16 ) ) );
	setMOBVelocity ( game->cats [ cat ], 0.0f, -( game->cats_velocity ) );
}



void setAndInitializeCatStateMovingRight ( struct Game *game, uint8_t cat, uint16_t distance )
{
	game->cats [ cat ]->state = STATE_CAT_MOVING_RIGHT;
	game->cats [ cat ]->direction = RIGHT;
	setMOBTargetPosition ( game->cats [ cat ], ( ( uint16_t ) game->cats [ cat ]->position.x + ( distance * 16 ) ), ( uint16_t ) game->cats [ cat ]->position.y );
	setMOBVelocity ( game->cats [ cat ], ( game->cats_velocity ), 0.0f );
	setAnimationSequenceIndex ( game->animationsequences, game->cats [ cat ]->animation, ANIMATION_SEQUENCE_CAT_MOVING_RIGHT );
}



void setAndInitializeCatStateMovingDown ( struct Game *game, uint8_t cat, uint16_t distance )
{
	game->cats [ cat ]->state = STATE_CAT_MOVING_DOWN;
	setMOBTargetPosition ( game->cats [ cat ], ( uint16_t ) game->cats [ cat ]->position.x, ( ( uint16_t ) game->cats [ cat ]->position.y + ( distance * 16 ) ) );
	setMOBVelocity ( game->cats [ cat ], 0.0f, ( game->cats_velocity ) );
}



void setAndInitializeCatStateMovingLeft ( struct Game *game, uint8_t cat, uint16_t distance )
{
	game->cats [ cat ]->state = STATE_CAT_MOVING_LEFT;
	game->cats [ cat ]->direction = LEFT;
	setMOBTargetPosition ( game->cats [ cat ], ( ( uint16_t ) game->cats [ cat ]->position.x - ( distance * 16 ) ), ( uint16_t ) game->cats [ cat ]->position.y );
	setMOBVelocity ( game->cats [ cat ], -( game->cats_velocity ), 0.0f );
	setAnimationSequenceIndex ( game->animationsequences, game->cats [ cat ]->animation, ANIMATION_SEQUENCE_CAT_MOVING_LEFT );
}



void setAndInitializeCatsStateDancing ( struct Game *game )
{
	uint8_t i;



	for ( i = 0; i < NUMBER_OF_CATS; i++ )
	{
		game->cats [ i ]->state = STATE_CAT_DANCING;
		setMOBVelocity ( game->cats [ i ], 0.0f, 0.0f );
		updateMOBPosition ( game->cats [ i ] );
		setAnimationSequenceIndex ( game->animationsequences, game->cats [ i ]->animation, ANIMATION_SEQUENCE_CAT_DANCING );
		setAnimationTimeout ( game->cats [ i ]->animation, ANIMATION_TIMEOUT_CATS_DANCING );
		setAnimationTimer ( game->cats [ i ]->animation, ANIMATION_TIMEOUT_CATS_DANCING );
	}
}



void setAndInitializeCatsStateSleeping ( struct Game *game )
{
	uint8_t i;



	for ( i = 0; i < NUMBER_OF_CATS; i++ )
	{
		game->cats [ i ]->state = STATE_CAT_SLEEPING;
		setMOBVelocity ( game->cats [ i ], 0.0f, 0.0f );
		updateMOBPosition ( game->cats [ i ] );
		if ( game->cats [ i ]->direction == RIGHT )
		{
			setAnimationSequenceIndex ( game->animationsequences, game->cats [ i ]->animation, ANIMATION_SEQUENCE_CAT_SLEEPING_RIGHT );
		}
		else
		{
			setAnimationSequenceIndex ( game->animationsequences, game->cats [ i ]->animation, ANIMATION_SEQUENCE_CAT_SLEEPING_LEFT );
		}
		setAnimationTimeout ( game->cats [ i ]->animation, ANIMATION_TIMEOUT_CATS_SLEEPING );
		setAnimationTimer ( game->cats [ i ]->animation, ANIMATION_TIMEOUT_CATS_SLEEPING );
	}
}



/* update loops */
void updateCats ( struct Game *game )
{
	uint8_t i;



	/* process for each cat */
	for ( i = 0; i < NUMBER_OF_CATS; i++ )
	{
		/* update animation */
		updateAnimation ( game->animationsequences, game->cats [ i ]->animation );
		switch ( game->cats [ i ]->state )
		{
			case STATE_CAT_MOVING_UP:
				updateCatStateMovingUp ( game, i );
				break;

			case STATE_CAT_MOVING_RIGHT:
				updateCatStateMovingRight ( game, i );
				break;

			case STATE_CAT_MOVING_DOWN:
				updateCatStateMovingDown ( game, i );
				break;

			case STATE_CAT_MOVING_LEFT:
				updateCatStateMovingLeft ( game, i );
				break;

			case STATE_CAT_DANCING:
			case STATE_CAT_SLEEPING:
			default:
				break;
		}
	}
}



void updateCatStateMovingUp ( struct Game *game, uint8_t cat )
{
	updateMOBPosition ( game->cats [ cat ] );
	if ( ( uint16_t ) game->cats [ cat ]->position.y <= game->cats [ cat ]->target_position.y )
	{
		game->cats [ cat ]->position.y = ( float ) game->cats [ cat ]->target_position.y;
		selectCatDirection ( game, cat );
	}
}



void updateCatStateMovingRight ( struct Game *game, uint8_t cat )
{
	updateMOBPosition ( game->cats [ cat ] );
	if ( ( uint16_t ) game->cats [ cat ]->position.x >= game->cats [ cat ]->target_position.x )
	{
		game->cats [ cat ]->position.x = ( float ) game->cats[ cat ]->target_position.x;
		selectCatDirection ( game, cat );
	}
}



void updateCatStateMovingDown ( struct Game *game, uint8_t cat )
{
	updateMOBPosition ( game->cats [ cat ] );
	if ( ( uint16_t ) game->cats [ cat ]->position.y >= game->cats [ cat ]->target_position.y )
	{
		game->cats [ cat ]->position.y = ( float ) game->cats [ cat ]->target_position.y;
		selectCatDirection ( game, cat );
	}
}



void updateCatStateMovingLeft ( struct Game *game, uint8_t cat )
{
	updateMOBPosition ( game->cats [ cat ] );
	if ( ( uint16_t ) game->cats [ cat ]->position.x <= game->cats [ cat ]->target_position.x )
	{
		game->cats [ cat ]->position.x = ( float ) game->cats [ cat ]->target_position.x;
		selectCatDirection ( game, cat );
	}
}



void updateCatsStateDancing ( struct Game *game )
{

}



void updateCatsStateSleeping ( struct Game *game )
{ 

}



void setCatsStartPosition ( struct Game *game )
{
	uint8_t i;
	uint8_t exception;
	SDL_Point target;
	SDL_Rect exclusion_range;



	/* set exlusion box, mouse based around mouse start position */
	exclusion_range.x = 6;
	exclusion_range.y = 4;
	exclusion_range.w = 7;
	exclusion_range.h = 7;

	for ( i = 0; i < NUMBER_OF_CATS; i++ )
	{
		/* initialize target to 0 */
		target.x = 0;
		target.y = 0;

		exception = 0;
		/* select a cell outside the exclusion box that is empty */
		do
		{
			target.x = ( rand ( ) % ( game->stage->playfield->w - 2 ) ) + 1;
			target.y = ( rand ( ) % ( game->stage->playfield->h - 2 ) ) + 1;

			if ( getPlayfieldCell ( game->stage->playfield, target.x, target.y ) == TILE_WALL )
			{
				exception = 1;
			}
			else if ( SDL_PointInRect ( &target, &exclusion_range ) == SDL_TRUE )
			{
				exception = 1;
			}
			else
			{
				exception = 0;
			}
		} while ( exception == 1 );

		/* set cat position */
		setMOBPosition ( game->cats [ i ], ( ( float ) target.x * 16 ), ( ( float ) ( 8 + ( target.y * 16 ) ) ) );
		setMOBTargetPosition ( game->cats [ i ], target.x, target.y );
		centerMOBCollisionBox ( game->cats [ i ] );
	}
}



void setCatsVelocity ( struct Game *game, float velocity_setting )
{
	uint8_t i;


	game->cats_velocity = velocity_setting;
	for ( i = 0; i < NUMBER_OF_CATS; i++ )
	{
		/* set animation rate */
		if ( velocity_setting == VELOCITY_CATS_SLOW )
		{
			setAnimationTimeout ( game->cats [ i ]->animation, ANIMATION_TIMEOUT_CATS_SLOW );
			setAnimationTimer ( game->cats [ i ]->animation, ANIMATION_TIMEOUT_CATS_SLOW );
		}
		else if ( velocity_setting == VELOCITY_CATS_FAST )
		{
			setAnimationTimeout ( game->cats [ i ]->animation, ANIMATION_TIMEOUT_CATS_FAST );
			setAnimationTimer ( game->cats [ i ]->animation, ANIMATION_TIMEOUT_CATS_FAST );
		}
		else
		{
			setAnimationTimeout ( game->cats [ i ]->animation, ANIMATION_TIMEOUT_CATS_NORMAL );
			setAnimationTimer ( game->cats [ i ]->animation, ANIMATION_TIMEOUT_CATS_NORMAL );
		}

		switch ( game->cats [ i ]->state )
		{
			case STATE_CAT_MOVING_DOWN:
				setMOBVelocity ( game->cats [ i ], 0.0f, game->cats_velocity );
				break;

			case STATE_CAT_MOVING_UP:
				setMOBVelocity ( game->cats [ i ], 0.0f, -( game->cats_velocity ) );
				break;

			case STATE_CAT_MOVING_LEFT:
				setMOBVelocity ( game->cats [ i ], -( game->cats_velocity ), 0.0f );
				break;

			case STATE_CAT_MOVING_RIGHT:
				setMOBVelocity ( game->cats [ i ], ( game->cats_velocity ), 0.0f );
				break;

			default:
				break;
		}
	}
}



/* special */
uint8_t checkCatMove ( struct Game *game, uint8_t cat, uint8_t direction )
{
	uint16_t position;



	updateMOBPlayfieldPosition ( game->cats [ cat ] );
	position = ( game->cats [ cat ]->playfield_position.y * game->stage->playfield->w ) + game->cats [ cat ]->playfield_position.x;

	switch ( direction )
	{
		case UP:
			position -= game->stage->playfield->w;
			break;

		case DOWN:
			position += game->stage->playfield->w;
			break;

		case LEFT:
			position -= 1;
			break;

		case RIGHT:
			position += 1;
			break;

		default:
			break;
	}

	if ( game->stage->playfield->data [ position ] == TILE_WALL )
	{
		return 0;
	}

	return 1;
}



void selectCatDirection ( struct Game *game, uint8_t cat )
{
	uint8_t i;
	uint8_t r;
	uint16_t c;
	uint8_t open [ 4 ];



	/* clear buffer */
	for ( i = 0; i < 4; i++ )
	{
		open [ i ] = 0;
	}

	/* populate buffer and calculate size ( 1 - 4 ) */
	i = 0;
	if ( checkCatMove ( game, cat, UP ) == 1 )
	{
		open [ i ] = UP;
		i++;
	}
	if ( checkCatMove ( game, cat, RIGHT ) == 1 )
	{
		open [ i ] = RIGHT;
		i++;
	}
	if ( checkCatMove ( game, cat, DOWN ) == 1 )
	{
		open [ i ] = DOWN;
		i++;
	}
	if ( checkCatMove ( game, cat, LEFT ) == 1 )
	{
		open [ i ] = LEFT;
		i++;
	}

	/* select a random move */
	r = rand ( ) % i;

	/* we have a set direction, lets set initiate the move */
	c = ( rand ( ) % ( getCatLinearDistance ( game, cat, open [ r ] ) ) ) + 1;

	/* set the new move state */
	switch ( open [ r ] )
	{
		case UP:
			setAndInitializeCatStateMovingUp ( game, cat, c );
			break;

		case RIGHT:
			setAndInitializeCatStateMovingRight ( game, cat, c );
			break;

		case DOWN:
			setAndInitializeCatStateMovingDown ( game, cat, c );
			break;

		case LEFT:
			setAndInitializeCatStateMovingLeft ( game, cat, c );
			break;

		default:
			setAndInitializeCatStateIdle ( game, cat );
			break;
	}
}



uint16_t getCatLinearDistance ( struct Game *game, uint8_t cat, uint8_t direction )
{
	uint16_t distance;
	uint16_t x;
	uint16_t y;



	updateMOBPlayfieldPosition ( game->cats [ cat ] );
	x = game->cats [ cat ]->playfield_position.x;
	y = game->cats [ cat ]->playfield_position.y;
	distance = 1;

	switch ( direction )
	{
		case UP:
			while ( getPlayfieldCell ( game->stage->playfield, x, ( y - distance ) ) != TILE_WALL )
			{
				distance++;
			}
			break;

		case RIGHT:
			while ( getPlayfieldCell ( game->stage->playfield, ( x + distance ), y ) != TILE_WALL )
			{
				distance++;
			}
			break;

		case DOWN:
			while ( getPlayfieldCell ( game->stage->playfield, x, ( y + distance ) ) != TILE_WALL )
			{
				distance++;
			}
			break;

		case LEFT:
			while ( getPlayfieldCell ( game->stage->playfield, ( x - distance ), y ) != TILE_WALL )
			{
				distance++;
			}
			break;

		default:
			break;

	}

	return ( distance - 1 );
}



/* render */
void renderCats ( struct Game *game )
{
	uint8_t i;
	uint8_t s;



	for ( i = 0; i < NUMBER_OF_CATS; i++ )
	{
		s = getAnimationSequenceIndex ( game->cats [ i ]->animation );
		/* render main image */
		addSpriteToSpriteBatch
		(
			game->spritebatch,
			getAnimationSpriteID ( game->animationsequences, game->cats [ i ]->animation ),
			( uint16_t ) game->cats [ i ]->position.x,
			( uint16_t ) game->cats [ i ]->position.y,
			1,
			-1
		);

		/* render mask image */
		setAnimationSequenceIndex ( game->animationsequences, game->cats [ i ]->animation, ( s + 1 ) );
		addSpriteToSpriteBatch
		(
			game->spritebatch,
			getAnimationSpriteID ( game->animationsequences, game->cats [ i ]->animation ),
			( uint16_t ) game->cats [ i ]->position.x,
			( uint16_t ) game->cats [ i ]->position.y,
			-1,
			1
		);
		setAnimationSequenceIndex ( game->animationsequences, game->cats [ i ]->animation, ( s ) );
	}
}