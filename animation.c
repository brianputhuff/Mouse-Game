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



#include "animation.h"


struct Animation *createAnimation ( )
{
	struct Animation *animation;



	animation = NULL;
	animation = malloc ( sizeof ( struct Animation ) );
	if ( animation == NULL )
	{
		return NULL;
	}

	animation->sequence_index = 0;
	animation->frame = 0;
	animation->timeout = 0;
	animation->timer = 0;

	return ( animation );
}



void destroyAnimation ( struct Animation *animation )
{
	if ( animation == NULL )
	{
		return;
	}

	free ( animation );
}



void updateAnimation ( struct AnimationSequences *animationsequences, struct Animation *animation )
{
	if ( animationsequences->sequences [ animation->sequence_index ]->data == NULL )
	{
		return;
	}

	if ( animation->timer == 0 )
	{
		animation->frame++;
		if ( animation->frame >= animationsequences->sequences [ animation->sequence_index ]->count )
		{
			animation->frame = 0;
		}

		animation->timer = animation->timeout;
	}
	else
	{
		animation->timer--;
	}
}



void setAnimationSequenceIndex ( struct AnimationSequences *animationsequences, struct Animation *animation, uint8_t sequence_index )
{
	if (sequence_index >= animationsequences->count )
	{
		return;
	}

	animation->sequence_index = sequence_index;
}



void setAnimationFrame ( struct AnimationSequences *animationsequences, struct Animation *animation, uint8_t frame )
{
	if ( ( animationsequences->sequences [ animation->sequence_index ] == NULL ) || ( frame >= animationsequences->sequences [ animation->sequence_index ]->count ) )
	{
		return;
	}

	animation->frame = frame;
}



void setAnimationTimeout ( struct Animation *animation, uint8_t timeout )
{
	animation->timeout = timeout;
}



void setAnimationTimer ( struct Animation *animation, uint8_t timer )
{
	animation->timer = timer;
}



uint8_t getAnimationSequenceIndex ( struct Animation *animation )
{
	return animation->sequence_index;
}



uint8_t getAnimationFrame ( struct Animation *animation )
{
	return animation->frame;
}



uint16_t getAnimationSpriteID ( struct AnimationSequences *animationsequences, struct Animation *animation )
{
	return ( animationsequences->sequences [ animation->sequence_index]->data [ animation->frame ] );
}




struct AnimationSequences *createAnimationSequences ( uint16_t number_of_sequences )
{
	uint16_t i;
	struct AnimationSequences *animationsequences;
	struct Sequence **sequences;



	if ( number_of_sequences < 1 )
	{
		return NULL;
	}

	sequences = NULL;
	sequences = malloc ( sizeof ( struct Sequence * ) * number_of_sequences );
	if ( sequences == NULL )
	{
		return NULL;
	}

	animationsequences = NULL;
	animationsequences = malloc ( sizeof ( struct AnimationSequences ) );
	if ( animationsequences == NULL )
	{
		free ( sequences );
		return NULL;
	}

	for ( i = 0; i < number_of_sequences; i++ )
	{
		sequences [ i ] = NULL;
	}

	animationsequences->sequences = sequences;
	animationsequences->count = number_of_sequences;

	return animationsequences;
}



void destroyAnimationSequences ( struct AnimationSequences *animationsequences )
{
	uint16_t i;

	if ( animationsequences == NULL )
	{
		return;
	}

	for ( i = 0; i < animationsequences->count; i++ )
	{
		destroySequence ( animationsequences->sequences [ i ] );
	}

	free ( animationsequences );

}



void setAnimationSequence ( struct AnimationSequences *animationsequences, uint16_t sequence_index, struct Sequence *sequence )
{
	if ( ( animationsequences == NULL ) || ( sequence_index > animationsequences->count ) )
	{
		return;
	}

	animationsequences->sequences [ sequence_index ] = sequence;
}