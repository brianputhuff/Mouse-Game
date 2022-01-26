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



#include "gameover.h"



void setAndInitializeGameStateDeath ( struct Game *game )
{
	setAndInitializeMouseStateDeath ( game );
	setAndInitializeCatsStateDancing ( game );
	playSound ( game->audio, SFX_CAUGHT, 0, 128 );
}



void updateGameStateDeath ( struct Game *game )
{
	updateCats ( game );
	if ( updateMouseStateDeath ( game ) == 1 )
	{
		if ( game->remaining_mice > 0 )
		{
			subtractMouse ( game );
			setAndInitializeGameState ( game, STATE_GAME_PLAY );
		}
		else
		{
			setAndInitializeGameState ( game, STATE_GAME_GAME_OVER );
		}
	}

	renderMouse ( game );
	renderCats ( game );
}



void setAndInitializeGameStateGameOver ( struct Game *game )
{
	uint8_t i;



	/* set timeout */
	game->timer = TIMEOUT_GAME_OVER;

	/* display game over graphics onto screen */
	for ( i = 0; i < 20; i++ )
	{
		setVideoMapTile ( game->videomap, ( 728 + i ), ( i + 8 ), 11 );
		setVideoMapTile ( game->videomap, ( 764 + i ), ( i + 8 ), 12 );
		setVideoMapTile ( game->videomap, ( 800 + i ), ( i + 8 ), 13 );
	}
	if ( Mix_PlayingMusic ( ) > 0 )
	{
		fadeOutMusic ( AUDIO_FADE_RATE_SLOW );
	}
}



void updateGameStateGameOver ( struct Game *game )
{
	if ( game->timer == 0 )
	{
		/* reset game */
		setAndInitializeGameState ( game, STATE_GAME_TITLE_PRIMARY );
	}
	else
	{
		game->timer--;
	}
}
