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



#ifndef ANIMATION_H
#define ANIMATION_H



#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include "sequence.h"



/**
The Animation structure defines the general data required for handling an
animation sequence for a game object.
*/
struct Animation
{
	uint8_t timer;
	uint8_t timeout;
	uint8_t frame;
	uint8_t sequence_index;
};



/**
The AnimationSequences structure contains a collection of sequences that can be
referenced by Animation structures.
*/
struct AnimationSequences
{
	struct Sequence **sequences;
	uint16_t count;
};



/**
* Allocates memory on the heap for an Animation structure.
*
* \param No input parameters (void)
* \returns A pointer to the allocated Animation structure
*/
struct Animation *createAnimation ( void );



/**
* Frees memory from the heap of a previously allocated Animation structure.
* 
* \param animation: A pointer to an Animation structure
* \returns No return value (void)
*/
void destroyAnimation ( struct Animation *animation );



/**
* Updates animation structure data (e.g. sets next frame if possible).
* 
* \param animationsequences: A pointer to an AnimationSequences structure
* \param animation: A pointer to an Animation structure
* \returns No return value (void)
*/
void updateAnimation ( struct AnimationSequences *animationsequences, struct Animation *animation );



/**
* Sets the animation sequence index data in an Animation structure.
* 
* \param animationsequences: A pointer to an AnimationSequences structure
* \param animation: A pointer to an Animation structure
* \param sequence_index: The animation sequence index to set from the AnimationSequences collection.
* \returns No return value (void)
*/
void setAnimationSequenceIndex ( struct AnimationSequences *animationsequences, struct Animation *animation, uint8_t sequence_index );



/**
* Sets the animation frame data in an Animation structure.
* 
* \param animationsequences: A pointer to an AnimationSequences structure
* \param animation: A pointer to an Animation structure
* \param frame: The animation frame value to set
* \returns No return value (void)
*/
void setAnimationFrame ( struct AnimationSequences *animationsequences, struct Animation *animation, uint8_t frame );



/**
* Sets the animation timeout value.
* 
* \param animation: A pointer to an Animation structure
* \param timeout: A timeout value (the number of frames to count)
* \returns No return value (void)
*/
void setAnimationTimeout ( struct Animation *animation, uint8_t timeout );



/**
* Sets the animation timer value.
* 
* \param animation: A pointer to an Animation structure
* \param timer: A countdown timer value
* \returns No return value (void)
*/
void setAnimationTimer ( struct Animation *animation, uint8_t timer );



/**
* Gets the animation sequence index value.
* 
* \param animation: A pointer to an Animation structure
* \returns An Animation sequence index value (uint8_t)
*/
uint8_t getAnimationSequenceIndex ( struct Animation *animation );



/**
* Gets the animation frame index value.
* 
* \param animation: A pointer to an Animation structure
* \returns An animation frame index value (uint8_t)
*/
uint8_t getAnimationFrame ( struct Animation *animation );



/**
* Gets the animation sprite index value.
* 
* \param animationsequences: A pointer to an AnimationSequences structure
* \param animation: A pointer to an Animation structure
* \returns An animation sprite ID (index) value (uint16_t)
*/
uint16_t getAnimationSpriteID ( struct AnimationSequences *animationsequences, struct Animation *animation );






/**
* Allocates memory on the heap for an AnimationSequences structure.
* 
* \param number_of_sequences: The number of Animation structures to contain in the AnimationSequences collection
* \returns A pointer to the AnimationSequences structure
*/
struct AnimationSequences *createAnimationSequences ( uint16_t number_of_sequences );



/**
* Frees memory from the heap of a previously allocated AnimationSequences structure.
* 
* \param animation: A pointer to an AnimationSequences structure
* \returns No return value (void)
*/
void destroyAnimationSequences ( struct AnimationSequences *animationsequences );



/**
* Sets a sequence structure address to one of the sequence pointers in the AnimationSequences structure.
* 
* \param animation: A pointer to an AnimationSequences structure
* \returns No return value (void)
*/
void setAnimationSequence ( struct AnimationSequences *animationsequences, uint16_t sequence_index, struct Sequence *sequence );



#endif
