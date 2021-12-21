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



#include "audio.h"



struct Audio *createAudio ( )
{
	struct Audio *audio;


	/* create audio */
	audio = NULL;
	audio = malloc ( sizeof ( struct Audio ) );
	if ( audio == NULL )
	{
		return NULL;
	}

	audio->channel = 0;


	/* initialize mixer and start audio stream */
	Mix_Init ( MIX_INIT_OGG );
	Mix_OpenAudio ( 44100, MIX_DEFAULT_FORMAT, 2, 1024 );


	/* load sound effects files */
	audio->sounds [ 0 ] = Mix_LoadWAV ( "eat.ogg" );
	audio->sounds [ 1 ] = Mix_LoadWAV ( "bonus.ogg" );
	audio->sounds [ 2 ] = Mix_LoadWAV ( "coffee.ogg" );
	audio->sounds [ 3 ] = Mix_LoadWAV ( "stage.ogg" );
	audio->sounds [ 4 ] = Mix_LoadWAV ( "caught.ogg" );
	audio->sounds [ 5 ] = Mix_LoadWAV ( "complete.ogg" );
	audio->sounds [ 6 ] = Mix_LoadWAV ( "nocoffeebonus.ogg" );
	audio->sounds [ 7 ] = Mix_LoadWAV ( "stagecompletebonus.ogg" );
	audio->sounds [ 8 ] = Mix_LoadWAV ( "oneup.ogg" );

	/* load music files */
	audio->tracks [ 0 ] = Mix_LoadMUS ( "bgm_title.ogg" );
	audio->tracks [ 1 ] = Mix_LoadMUS ( "bgm_01.ogg" );
	audio->tracks [ 2 ] = Mix_LoadMUS ( "bgm_02.ogg" );
	audio->tracks [ 3 ] = Mix_LoadMUS ( "bgm_03.ogg" );
	audio->tracks [ 4 ] = Mix_LoadMUS ( "bgm_04.ogg" );
	audio->tracks [ 5 ] = Mix_LoadMUS ( "bgm_ending.ogg" );

	return audio;
}



void destroyAudio ( struct Audio *audio )
{
	uint8_t i;



	/* free sound (chunk) data */
	for ( i = 0; i < NUMBER_OF_SOUNDS; i++ )
	{
		Mix_FreeChunk ( audio->sounds [ i ] );
	}

	/* free music data */
	for ( i = 0; i < NUMBER_OF_TRACKS; i++ )
	{
		Mix_FreeMusic ( audio->tracks [ i ] );
	}

	free ( audio );

	/* close audio stream and exit mixer */
	Mix_CloseAudio ( );
	Mix_Quit ( );
}



void playSound ( struct Audio *audio, uint8_t sound_id, uint16_t loops, uint16_t volume )
{
	/* set volume for sound */
	Mix_Volume ( audio->channel, volume );

	/* play sound */
	Mix_PlayChannel ( audio->channel, audio->sounds [ sound_id ], loops );

	/* alternate sound channel */
	audio->channel++;
	if ( audio->channel == SOUND_CHANNELS )
	{
		audio->channel = 0;
	}
}



void playMusic ( struct Audio *audio, uint8_t track_id, int16_t loops, uint16_t volume )
{
	/* set volume for music */
	Mix_VolumeMusic ( volume );

	/* play track */
	Mix_PlayMusic ( audio->tracks [ track_id ], loops );
}



void stopMusic ( void )
{
	/* stop playing track */
	if ( Mix_PlayingMusic ( ) > 0 )
	{
		Mix_HaltMusic ( );
	}
}



void fadeOutMusic ( uint32_t fade_rate )
{
	/* fade track */
	if ( Mix_PlayingMusic ( ) > 0 )
	{
		Mix_FadeOutMusic ( fade_rate );
	}
}
