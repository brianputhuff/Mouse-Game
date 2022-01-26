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



#ifndef AUDIO_H
#define AUDIO_H



#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <SDL2/SDL_mixer.h>



#define NUMBER_OF_SOUNDS 9
#define NUMBER_OF_TRACKS 6
#define SOUND_CHANNELS 6



#define AUDIO_FADE_RATE_SLOW 4000
#define AUDIO_FADE_RATE_NORMAL 1000
#define AUDIO_FADE_RATE_FAST 500



enum
{
	SFX_EAT = 0,
	SFX_BONUS = 1,
	SFX_COFFEE = 2,
	SFX_STAGE = 3,
	SFX_CAUGHT = 4,
	SFX_COMPLETE = 5,
	SFX_NO_COFFEE_BONUS = 6,
	SFX_STAGE_COMPLETE_BONUS = 7,
	SFX_ONE_UP = 8
};



enum
{
	MUS_TITLE = 0,
	MUS_BGM_1 = 1,
	MUS_BGM_2 = 2,
	MUS_BGM_3 = 3,
	MUS_BGM_4 = 4,
	MUS_ENDING = 5 
};



struct Audio
{
	Mix_Chunk *sounds [ NUMBER_OF_SOUNDS ];
	Mix_Music *tracks [ NUMBER_OF_TRACKS ];
	uint8_t channel;
};



/**
* Allocates memory on the heap for an Audio structure.
*
* \param No input parameters (void)
* \returns A pointer to the Audio structure
*/
struct Audio *createAudio ( void );



/**
* Frees memory from the heap of a previously allocated Audio structure.
*
* \param audio: A pointer to an Audio structure
* \returns No return value (void)
*/
void destroyAudio ( struct Audio *audio );



/**
* Plays a sound file.
*
* \param audio: A pointer to an Audio structure
* \param sound_id: An index to a sound file
* \param loops: The number of times to repeat the playback (-1 = infinite, 0 = once, >0 = number of loops)
* \param volume: The volume to play back the sound at (0 - 127)
* \returns No return value (void)
*/
void playSound ( struct Audio *audio, uint8_t sound_id, uint16_t loops, uint16_t volume );



/**
* Plays a music track file.
*
* \param audio: A pointer to an Audio structure
* \param sound_id: An index to a music track file
* \param loops: The number of times to repeat the playback (-1 = infinite, 0 = once, >0 = number of loops)
* \param volume: The volume to play back the sound at (0 - 127)
* \returns No return value (void)
*/
void playMusic ( struct Audio *audio, uint8_t track_id, int16_t loops, uint16_t volume );



/**
* Stop playing a music track file.
*
* \param No input parameters (void)
* \returns No return value (void)
*/
void stopMusic ( void );



/**
* Fade out currently playing music track file at a specifed rate.
*
* \param fade_rate: Rate (in milliseconds) to fade out track audio volume
* \returns No return value (void)
*/
void fadeOutMusic ( uint32_t fade_rate );



#endif
