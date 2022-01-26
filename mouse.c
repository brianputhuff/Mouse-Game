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



#include "mouse.h"



void setAndInitializeMouse ( struct Game *game )
{
	game->mouse->direction = LEFT;

	/* reset velocity and position */
	setMOBVelocity ( game->mouse, 0.0f, 0.0f );
	setMOBPosition ( game->mouse, 144.0f, 104.0f );
	setMOBTargetPosition ( game->mouse, 0, 0 );

	/* collision box*/
	game->mouse->collision_box_offset.x = 0;
	game->mouse->collision_box_offset.y = 0;
	game->mouse->collision_box.h = 16;
	game->mouse->collision_box.w = 16;
	updateMOBPosition ( game->mouse );

	/* reset animation */
	setAnimationFrame ( game->animationsequences, game->mouse->animation, 0 );
	setAnimationSequenceIndex ( game->animationsequences, game->mouse->animation, ANIMATION_SEQUENCE_MOUSE_LEFT );
	setAnimationTimeout ( game->mouse->animation, ANIMATION_TIMEOUT_MOUSE_MOVE );

	/* set state to IDLE */
	setAndInitializeMouseStateIdle ( game );
}



void setAndInitializeMouseStateIdle ( struct Game *game )
{
	/* set state and counter (timeout) */
	game->mouse->state = STATE_MOUSE_IDLE;
	game->mouse->timer = 16;
	game->mouse->timeout = 16;

	/* set velocity and position */
	setMOBVelocity ( game->mouse, 0.0f, 0.0f );
	updateMOBPosition ( game->mouse );

	/* set animation  */
	setAnimationFrame ( game->animationsequences, game->mouse->animation, 0 );
}



void setAndInitializeMouseStateMovingUp ( struct Game *game )
{
	/* set state to MOVING UP */
	game->mouse->state = STATE_MOUSE_MOVING_UP;

	/* set velocity and position */
	setMOBVelocity ( game->mouse, 0.0f, -4.0f );
	game->mouse->target_position.x = ( int16_t ) game->mouse->position.x;
	game->mouse->target_position.y = ( int16_t ) game->mouse->position.y - 16;
	updateMOBPosition ( game->mouse );

	/* set animation  */
	setAnimationFrame ( game->animationsequences, game->mouse->animation, 0 );
	setAnimationSequenceIndex ( game->animationsequences, game->mouse->animation, ANIMATION_SEQUENCE_MOUSE_UP );
	setAnimationTimeout ( game->mouse->animation, ANIMATION_TIMEOUT_MOUSE_MOVE );
	setAnimationTimer ( game->mouse->animation, ANIMATION_TIMEOUT_MOUSE_MOVE );
}



void setAndInitializeMouseStateMovingRight ( struct Game *game )
{
	/* set state to MOVING RIGHT */
	game->mouse->state = STATE_MOUSE_MOVING_RIGHT;
	game->mouse->direction = DIRECTION_RIGHT;

	/* set velocity and position */
	setMOBVelocity ( game->mouse, 4.0f, 0.0f );
	game->mouse->target_position.x = ( int16_t ) ( game->mouse->position.x + 16.0f );
	game->mouse->target_position.y = ( int16_t ) game->mouse->position.y;
	updateMOBPosition ( game->mouse );

	/* set animation  */
	setAnimationFrame ( game->animationsequences, game->mouse->animation, 0 );
	setAnimationSequenceIndex ( game->animationsequences, game->mouse->animation, ANIMATION_SEQUENCE_MOUSE_RIGHT );
	setAnimationTimeout ( game->mouse->animation, ANIMATION_TIMEOUT_MOUSE_MOVE );
	setAnimationTimer ( game->mouse->animation, ANIMATION_TIMEOUT_MOUSE_MOVE );
}



void setAndInitializeMouseStateMovingDown ( struct Game *game )
{
	/* set state to MOVING DOWN */
	game->mouse->state = STATE_MOUSE_MOVING_DOWN;

	/* set velocity and position */
	setMOBVelocity ( game->mouse, 0.0f, 4.0f );
	game->mouse->target_position.x = ( int16_t ) game->mouse->position.x;
	game->mouse->target_position.y = ( int16_t ) ( game->mouse->position.y + 16.0f );
	updateMOBPosition ( game->mouse );

	/* set animation */
	setAnimationFrame ( game->animationsequences, game->mouse->animation, 0 );
	setAnimationSequenceIndex ( game->animationsequences, game->mouse->animation, ANIMATION_SEQUENCE_MOUSE_DOWN );
	setAnimationTimeout ( game->mouse->animation, ANIMATION_TIMEOUT_MOUSE_MOVE );
	setAnimationTimer ( game->mouse->animation, ANIMATION_TIMEOUT_MOUSE_MOVE );
}



void setAndInitializeMouseStateMovingLeft ( struct Game *game )
{

	/* set state to MOVING LEFT */
	game->mouse->state = STATE_MOUSE_MOVING_LEFT;
	game->mouse->direction = DIRECTION_LEFT;

	/* set velocity and position */
	setMOBVelocity ( game->mouse, -4.0f, 0.0f );
	game->mouse->target_position.x = ( int16_t ) ( game->mouse->position.x - 16.0f );
	game->mouse->target_position.y = ( int16_t ) game->mouse->position.y;
	updateMOBPosition ( game->mouse );

	/* set animation */
	setAnimationFrame ( game->animationsequences, game->mouse->animation, 0 );
	setAnimationSequenceIndex ( game->animationsequences, game->mouse->animation, ANIMATION_SEQUENCE_MOUSE_LEFT );
	setAnimationTimeout ( game->mouse->animation, ANIMATION_TIMEOUT_MOUSE_MOVE );
	setAnimationTimer ( game->mouse->animation, ANIMATION_TIMEOUT_MOUSE_MOVE );
}



void setAndInitializeMouseStateDancing ( struct Game *game )
{
	/* set state and counter (timeout) */
	game->mouse->state = STATE_MOUSE_DANCING;
	game->mouse->timer = 240;

	/* set velocity and position */
	setMOBVelocity ( game->mouse, 0.0f, 0.0f );
	updateMOBPosition ( game->mouse );

	/* set animation */
	setAnimationFrame ( game->animationsequences, game->mouse->animation, 0 );
	setAnimationSequenceIndex ( game->animationsequences, game->mouse->animation, ANIMATION_SEQUENCE_MOUSE_DANCING );
	setAnimationTimeout ( game->mouse->animation, ANIMATION_TIMEOUT_MOUSE_DANCING );
	setAnimationTimer ( game->mouse->animation, ANIMATION_TIMEOUT_MOUSE_DANCING );
}



void setAndInitializeMouseStateDeath ( struct Game *game )
{
	/* set state and counter (timeout) */
	game->mouse->state = STATE_MOUSE_DEATH;
	game->mouse->timer = 240;

	/* set velocity and position */
	setMOBVelocity ( game->mouse, 0.0f, 0.0f );
	updateMOBPosition ( game->mouse );

	/* set animation */
	setAnimationFrame ( game->animationsequences, game->mouse->animation, 0 );
	if ( game->mouse->direction == DIRECTION_LEFT )
	{
		setAnimationSequenceIndex ( game->animationsequences, game->mouse->animation, ANIMATION_SEQUENCE_MOUSE_DEATH_LEFT );
	}
	else
	{
		setAnimationSequenceIndex ( game->animationsequences, game->mouse->animation, ANIMATION_SEQUENCE_MOUSE_DEATH_RIGHT );
	}
	setAnimationTimeout ( game->mouse->animation, ANIMATION_TIMEOUT_MOUSE_DEATH );
	setAnimationTimer ( game->mouse->animation, ANIMATION_TIMEOUT_MOUSE_DEATH );
}




uint8_t updateMouseState ( struct Game *game )
{
	switch ( game->mouse->state )
	{
		case STATE_MOUSE_IDLE:
			break;

		case STATE_MOUSE_MOVING_UP:
			return updateMouseStateMovingUp ( game );
			break;

		case STATE_MOUSE_MOVING_RIGHT:
			return updateMouseStateMovingRight ( game );
			break;

		case STATE_MOUSE_MOVING_DOWN:
			return updateMouseStateMovingDown ( game );
			break;

		case STATE_MOUSE_MOVING_LEFT:
			return updateMouseStateMovingLeft ( game );
			break;

		case STATE_MOUSE_DANCING:
			return updateMouseStateDancing ( game );
			break;

		case STATE_MOUSE_DEATH:
			return updateMouseStateDeath ( game );
			break;
	}

	return 0;
}



uint8_t updateMouseStateMovingUp ( struct Game *game )
{
	/* update animation */
	updateAnimation ( game->animationsequences, game->mouse->animation );
	updateMOBPosition ( game->mouse );

	/* handle move */
	if ( ( int16_t ) game->mouse->position.y <= game->mouse->target_position.y )
	{
		game->mouse->position.y = ( float ) game->mouse->target_position.y;
		setAndInitializeMouseStateIdle ( game );
		return 1;
	}
	else
	{
		if ( game->mouse->velocity.y > -1.0f )
		{
			game->mouse->velocity.y = -1.0f;
		}
		else
		{
			game->mouse->velocity.y /= 2.0f;
		}
	}

	return 0;
}



uint8_t updateMouseStateMovingRight ( struct Game *game )
{
	/* update animation */
	updateAnimation ( game->animationsequences, game->mouse->animation );
	updateMOBPosition ( game->mouse );

	/* handle move */
	if ( ( int16_t ) game->mouse->position.x >= game->mouse->target_position.x )
	{
		game->mouse->position.x = ( float ) game->mouse->target_position.x;
		setAndInitializeMouseStateIdle ( game );
		return 1;
	}
	else
	{
		if ( game->mouse->velocity.x < 1.0f )
		{
			game->mouse->velocity.x = 1.0f;
		}
		else
		{
			game->mouse->velocity.x /= 2.0f;
		}
	}

	return 0;
}



uint8_t updateMouseStateMovingDown ( struct Game *game )
{
	/* update animation */
	updateAnimation ( game->animationsequences, game->mouse->animation );
	updateMOBPosition ( game->mouse );

	/* handle move */
	if ( ( int16_t ) game->mouse->position.y >= game->mouse->target_position.y )
	{
		game->mouse->position.y = ( float ) game->mouse->target_position.y;
		setAndInitializeMouseStateIdle ( game );
		return 1;
	}
	else
	{
		if ( game->mouse->velocity.y < 1.0f )
		{
			game->mouse->velocity.y = 1.0f;
		}
		else
		{
			game->mouse->velocity.y /= 2.0f;
		}
	}

	return 0;
}



uint8_t updateMouseStateMovingLeft ( struct Game *game )
{ 
	/* update animation */
	updateAnimation ( game->animationsequences, game->mouse->animation );
	updateMOBPosition ( game->mouse );
	/* handle move */
	if ( ( int16_t ) game->mouse->position.x <= game->mouse->target_position.x )
	{
		game->mouse->position.x = ( float ) game->mouse->target_position.x;
		setAndInitializeMouseStateIdle ( game );
		return 1;
	}
	else
	{
		if ( game->mouse->velocity.x > -1.0f )
		{
			game->mouse->velocity.x = -1.0f;
		}
		else
		{
			game->mouse->velocity.x /= 2.0f;
		}
	}

	return 0;
}



uint8_t updateMouseStateDancing ( struct Game *game )
{
	/* update animation */
	updateAnimation ( game->animationsequences, game->mouse->animation );

	/* sequence count */
	if ( game->mouse->timer == 0 )
	{
		return 1;
	}
	else
	{
		game->mouse->timer--;
	}

	return 0;
}



uint8_t updateMouseStateDeath ( struct Game *game )
{
	/* update animation */
	if ( getAnimationFrame ( game->mouse->animation ) < 7 )
	{
		updateAnimation ( game->animationsequences, game->mouse->animation );
	}

	/* timout to end */
	if ( game->mouse->timer == 0 )
	{
		return 1;
	}
	else
	{
		game->mouse->timer--;
	}

	return 0;
}



uint8_t checkMouseMove ( struct Game *game, uint8_t direction )
{
	switch ( direction )
	{
		case UP:
			if ( getPlayfieldCell ( game->stage->playfield, ( game->mouse->playfield_position.x ), ( game->mouse->playfield_position.y - 1) ) == TILE_WALL )
			{
				return 0;
			}
			break;

		case RIGHT:
			if ( getPlayfieldCell ( game->stage->playfield, ( game->mouse->playfield_position.x + 1 ), ( game->mouse->playfield_position.y ) ) == TILE_WALL )
			{
				return 0;
			}
			break;

		case DOWN:
			if ( getPlayfieldCell ( game->stage->playfield, ( game->mouse->playfield_position.x ), ( game->mouse->playfield_position.y + 1 ) ) == TILE_WALL )
			{
				return 0;
			}
			break;

		case LEFT:
			if ( getPlayfieldCell ( game->stage->playfield, ( game->mouse->playfield_position.x - 1 ), ( game->mouse->playfield_position.y ) ) == TILE_WALL )
			{
				return 0;
			}
			break;

		default:
			return 0;
			break;
	}

	return 1;
}



void renderMouse ( struct Game *game )
{
	uint8_t s;



	s = getAnimationSequenceIndex ( game->mouse->animation );
	/* render main image */
	addSpriteToSpriteBatch
	(
		game->spritebatch,
		getAnimationSpriteID ( game->animationsequences, game->mouse->animation ),
		( uint16_t ) game->mouse->position.x,
		( uint16_t ) game->mouse->position.y,
		1,
		-1
	);

	/* render mask image */
	setAnimationSequenceIndex ( game->animationsequences, game->mouse->animation, ( s + 1 ) );
	addSpriteToSpriteBatch
	(
		game->spritebatch,
		getAnimationSpriteID ( game->animationsequences, game->mouse->animation ),
		( uint16_t ) game->mouse->position.x,
		( uint16_t ) game->mouse->position.y,
		-1,
		1
	);
	setAnimationSequenceIndex ( game->animationsequences, game->mouse->animation, ( s ) );
}



