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



#include "mob.h"



struct MOB *createMOB ( void )
{
	struct MOB *mob;


	mob = NULL;
	mob = malloc ( sizeof ( struct MOB ) );
	if ( mob == NULL )
	{
		return NULL;
	}

	/* zero out things */
	mob->state = 0;
	mob->direction = DIRECTION_UP;
	mob->position.x = 0.0f;
	mob->position.y = 0.0f;
	mob->velocity.x = 0.0f;
	mob->velocity.y = 0.0f;
	mob->collision_box_offset.x = 0;
	mob->collision_box_offset.y = 0;
	mob->collision_box.w = 8;
	mob->collision_box.h = 8;
	mob->collision_box.x = 0;
	mob->collision_box.y = 0;
	mob->playfield_position.x = 0;
	mob->playfield_position.y = 0;
	mob->target_position.x = 0;
	mob->target_position.y = 0;
	mob->timer = 0;
	mob->timeout = 0;
	mob->animation = createAnimation ( );

	return mob;
}



void destroyMOB ( struct MOB *mob )
{
	if ( mob == NULL )
	{
		return;
	}

	destroyAnimation ( mob->animation );
	free ( mob );
}



void updateMOBPosition ( struct MOB *mob )
{
	mob->position.x += mob->velocity.x;
	mob->position.y += mob->velocity.y;
	updateMOBPlayfieldPosition ( mob );
	centerMOBCollisionBox ( mob );
}



void updateMOBPlayfieldPosition ( struct MOB *mob )
{
	mob->playfield_position.x = ( uint16_t ) floor ( mob->position.x / 16 );
	mob->playfield_position.y = ( uint16_t ) floor ( ( mob->position.y - 8 ) / 16 );
}



void centerMOBCollisionBox ( struct MOB *mob )
{
	mob->collision_box.x = ( int16_t ) mob->position.x + mob->collision_box_offset.x;
	mob->collision_box.y = ( int16_t ) mob->position.y + mob->collision_box_offset.y;
}



uint8_t checkMOBTimeout ( struct MOB *mob )
{
	if ( mob->timer == 0 )
	{
		mob->timer = mob->timeout;
		return 1;
	}

	mob->timer--;
	return 0;
}



void setMOBVelocity ( struct MOB *mob, float vx, float vy )
{
	mob->velocity.x = vx;
	mob->velocity.y = vy;
}



void setMOBPosition ( struct MOB *mob, float x, float y )
{
	mob->position.x = x;
	mob->position.y = y;
}



void setMOBTargetPosition ( struct MOB *mob, int16_t x, int16_t y )
{
	mob->target_position.x = x;
	mob->target_position.y = y;
}



void setMOBPlayfieldPosition ( struct MOB *mob, int16_t x, int16_t y )
{
	mob->playfield_position.x = x;
	mob->playfield_position.y = y;
}