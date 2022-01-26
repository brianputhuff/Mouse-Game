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



#include "ending.h"



void setAndInitializeGameStateEnding ( struct Game *game )
{
	/* clear screen */
	setAllVideoMapTiles ( game->videomap, 0 );

	/* silence bgm music */
	if ( Mix_PlayingMusic ( ) > 0 )
	{
		stopMusic ( );
	}

	/* play ending theme */
	playMusic ( game->audio, MUS_ENDING, -1, 128 );

	/* game is not paused */
	game->paused = 0;

	game->step_message = 0;
	game->timer = TIMEOUT_ENDING_MESSAGE_STEP / 4;
}



void updateGameStateEnding ( struct Game *game )
{
	uint16_t i;
	uint16_t j;



	/* check if button A has been pressed after ending sequence */
	if ( ( game->input->BUTTON_A == 1 ) && game->step_message > 10 )
	{
		/* silence title music */
		if ( Mix_PlayingMusic ( ) > 0 )
		{
			stopMusic ( );
		}
		game->input->BUTTON_A = 0;
		setAndInitializeGameState ( game, STATE_GAME_TITLE_PRIMARY );
	}


	/* if timout, display messages, or exit */
	if ( game->timer == 0 )
	{
		game->step_message++;
		if ( game->step_message < 10 )
		{
			game->timer = TIMEOUT_ENDING_MESSAGE_STEP;
		}
		else
		{
			game->timer = TIMEOUT_ENDING_MESSAGE_STEP * 2;
		}

		switch ( game->step_message )
		{
			default:
				break;

			case 1:
				/* display messages  */
				putStringOnVideoMap ( game->videomap, "CONGRATULATIONS!!!", 19, 1, 1, 0 );
				break;

			case 2:
				/* display messages  */
				putStringOnVideoMap ( game->videomap, "YOU HAVE COMPLETED XX STAGES!", 30, 1, 3, 0 );
				putIntOnVideoMap ( game->videomap, game->stage->stage_number, 2, 20, 3, 0, 16 );
				break;

			case 3:
				/* display messages  */
				putStringOnVideoMap ( game->videomap, "TAKE A BREAK . . .", 19, 1, 5, 0 );
				break;

			case 4:
				/* display messages  */
				putStringOnVideoMap ( game->videomap, "YOU'VE EARNED IT.", 18, 3, 7, 0 );
				break;

			case 5:
				/* display messages  */
				putStringOnVideoMap ( game->videomap, "NO, REALLY, YOU HAVE.", 22, 5, 9, 0 );
				break;

			case 6:
				/* display messages  */
				putStringOnVideoMap ( game->videomap, "THIS ACCOMPLISHMENT IS", 23, 7, 11, 0 );
				putStringOnVideoMap ( game->videomap, "THE RESULT OF YOUR", 19, 7, 12, 0 );
				putStringOnVideoMap ( game->videomap, "TREMENDOUS EFFORT.", 19, 7, 13, 0 );
				break;

			case 7:
				/* display messages  */
				putStringOnVideoMap ( game->videomap, "KUDOS TO YOU!", 14, 7, 15, 0 );
				break;

			case 8:
				/* display image  */
				/* draw image border */
				/* TOP */
				setVideoMapTile ( game->videomap, 872, 25, 16 );
				for ( i = 0; i < 8; i++ )
				{
					setVideoMapTile ( game->videomap, 873, 26 + i, 16 );
				}
				setVideoMapTile ( game->videomap, 874, 34, 16 );

				/* SIDE */
				for ( i = 0; i < 8; i++ )
				{
					setVideoMapTile ( game->videomap, 908, 25, 17 + i );
					setVideoMapTile ( game->videomap, 910, 34, 17 + i );
				}

				/* BOTTOM */
				setVideoMapTile ( game->videomap, 944, 25, 25 );
				for ( i = 0; i < 8; i++ )
				{
					setVideoMapTile ( game->videomap, 945, 26 + i, 25 );
				}
				setVideoMapTile ( game->videomap, 946, 34, 25 );

				/* draw image */
				for ( j = 0; j < 8; j++ )
				{
					for ( i = 0; i < 8; i++ )
					{
						setVideoMapTile ( game->videomap, 864 + ( j * 36 ) + i, 26 + i, j + 17 );
					}
				}
				break;

			case 9:
				/* display messages  */
				putStringOnVideoMap ( game->videomap, "FINAL SCORE", 12, 7, 19, 0 );
				putIntOnVideoMap ( game->videomap, game->score, 6, 7, 20, 0, 16 );
				break;

			case 10:
				/* display messages  */
				putStringOnVideoMap ( game->videomap, "THANK YOU", 10, 7, 24, 0 );
				putStringOnVideoMap ( game->videomap, "FOR PLAYING.", 13, 7, 25, 0 );
				break;
		}
	}
	else
	{
		game->timer--;
	}
}