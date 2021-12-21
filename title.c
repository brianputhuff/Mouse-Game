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



#include "title.h"



struct Title *createTitle ( void )
{
	struct Title *title;


	title = NULL;
	title = malloc ( sizeof ( struct Title ) );

	return title;
}



void destroyTitle ( struct Title *title )
{
	if ( title == NULL )
	{
		return;
	}

	free ( title );
}



void setAndInitializeGameStateTitlePrimary ( struct Game *game )
{
	uint16_t i;
	uint16_t j;



	/* clear screen */
	setAllVideoMapTiles ( game->videomap, 0 );

	/* draw border */
	drawTitleBorder ( game );

	/* display title block */
	for ( j = 0; j < 3; j++ )
	{
		for ( i = 0; i < 20; i++ )
		{
			setVideoMapTile ( game->videomap, ( i + 584 ) + ( j * 36 ), i + 8, ( j + 2 ) );
		}
	}

	/* display mouse image block */
	for ( j = 0; j < 8; j++ )
	{
		for ( i = 0; i < 8; i++ )
		{
			setVideoMapTile ( game->videomap, ( i + 576 ) + ( j * 36 ), i + 14, ( j + 8 ) );
		}
	}

	/* top and bottom row */
	for ( i = 1; i < 35; i++ )
	{
		setVideoMapTile ( game->videomap, 216, i, 7 );
		setVideoMapTile ( game->videomap, 216, i, 16);
	}
	for ( j = 0; j < 8; j++ )
	{
		for ( i = 1; i < 14; i++ )
		{
			setVideoMapTile ( game->videomap, 216, i, ( j + 8 ) );
			setVideoMapTile ( game->videomap, 216, ( 35 - i ), ( j + 8 ) );
		}
	}

	/* display copyright */
	putStringOnVideoMap ( game->videomap, "COPYRIGHT c 2021 BRIAN PUTHUFF", 31, 3, 24, 0 );

	game->title->state_flashing_message = STATE_FLASHING_MESSAGE_NOT_SHOWN;
	game->title->timer_flashing_message = TIMEOUT_FLASHING_MESSAGE;
	game->title->timer_step_screen = TIMEOUT_TITLE_STEP_SCREEN;


	/* game is not paused */
	game->paused = 0;

	/* if music isn't already playing, play it */
	if ( Mix_PlayingMusic ( ) == 0 )
	{
		playMusic ( game->audio, MUS_TITLE, -1, 128 );
	}
}



void setAndInitializeGameStateTitleSecondary ( struct Game *game )
{
	/* clear screen */
	setAllVideoMapTiles ( game->videomap, 0 );

	/* draw border */
	drawTitleBorder ( game );

	/* initialize timer and step */
	game->title->timer_step_message = TIMEOUT_TITLE_STEP_MESSAGE / 4;
	game->title->step_message = 0;
}



void setAndInitializeGameStateTitleTertiary ( struct Game *game )
{
	/* clear screen */
	setAllVideoMapTiles ( game->videomap, 0 );

	/* draw border */
	drawTitleBorder ( game );

	/* initialize timer and step */
	game->title->timer_step_message = TIMEOUT_TITLE_STEP_MESSAGE / 4;
	game->title->step_message = 0;
}



void setAndInitializeGameStateTitleQuaternary ( struct Game *game )
{
	/* clear screen */
	setAllVideoMapTiles ( game->videomap, 0 );
		
	/* draw border */
	drawTitleBorder ( game );

	/* initialize timer and step */
	game->title->timer_step_message = TIMEOUT_TITLE_STEP_MESSAGE / 4;
	game->title->step_message = 0;
}



void updateGameStateTitlePrimary ( struct Game *game )
{
	if ( game->title->timer_step_screen == 0 )
	{
		setAndInitializeGameState ( game, STATE_GAME_TITLE_SECONDARY );
	}
	else
	{
		game->title->timer_step_screen--;

		if ( game->title->timer_flashing_message == 0 )
		{
			if ( game->title->state_flashing_message == STATE_FLASHING_MESSAGE_NOT_SHOWN )
			{
				putStringOnVideoMap ( game->videomap, "PRESS Z TO START", 17, 10, 20, 0 );
				game->title->state_flashing_message = STATE_FLASHING_MESSAGE_SHOWN;
				game->title->timer_flashing_message = TIMEOUT_FLASHING_MESSAGE;
			}
			else
			{
				putStringOnVideoMap ( game->videomap, "                ", 17, 10, 20, 0 );
				game->title->state_flashing_message = STATE_FLASHING_MESSAGE_NOT_SHOWN;
				game->title->timer_flashing_message = TIMEOUT_FLASHING_MESSAGE;
			}
		}
		else
		{
			game->title->timer_flashing_message--;
		}

		/* check if button A has been pressed */
		if ( game->input->BUTTON_A == 1 )
		{
			/* silence title music */
			if ( Mix_PlayingMusic ( ) > 0 )
			{
				stopMusic ( );
			}
			game->input->BUTTON_A = 0;
			newGame ( game );
			setAndInitializeGameState ( game, STATE_GAME_STAGE_IN );
		}
	}
}



void updateGameStateTitleSecondary ( struct Game *game )
{
	/* check if button A has been pressed */
	if ( game->input->BUTTON_A == 1 )
	{
		game->input->BUTTON_A = 0;
		setAndInitializeGameState ( game, STATE_GAME_TITLE_PRIMARY );
	}

	/* if timout, display messages, or exit */
	if ( game->title->timer_step_message == 0 )
	{
		game->title->step_message++;
		if ( game->title->step_message < 5 )
		{
			game->title->timer_step_message = TIMEOUT_TITLE_STEP_MESSAGE;
		}
		else
		{
			game->title->timer_step_message = TIMEOUT_TITLE_STEP_MESSAGE * 2;
		}

		switch ( game->title->step_message )
		{
			default:
				setAndInitializeGameState ( game, STATE_GAME_TITLE_TERTIARY );
				break;

			case 1:
				/* display messages  */
				putStringOnVideoMap ( game->videomap, "INSTRUCTIONS:", 14, 2, 2, 0 );
				break;

			case 2:
				/* display messages  */
				putStringOnVideoMap ( game->videomap, "1.   EAT ALL THE CHEESE.", 25, 2, 5, 0 );

				/* MOUSE*/
				setVideoMapTile ( game->videomap, 80, 7, 7 );
				setVideoMapTile ( game->videomap, 81, 8, 7 );
				setVideoMapTile ( game->videomap, 116, 7, 8 );
				setVideoMapTile ( game->videomap, 117, 8, 8 );

				/* RIGHT ARROW */
				setVideoMapTile ( game->videomap, 174, 11, 7 );
				setVideoMapTile ( game->videomap, 175, 12, 7 );
				setVideoMapTile ( game->videomap, 210, 11, 8 );
				setVideoMapTile ( game->videomap, 211, 12, 8 );

				/* CHEESE */
				setVideoMapTile ( game->videomap, 72, 15, 7 );
				setVideoMapTile ( game->videomap, 73, 16, 7 );
				setVideoMapTile ( game->videomap, 108, 15, 8 );
				setVideoMapTile ( game->videomap, 109, 16, 8 );
				break;

			case 3:
				/* display messages  */
				putStringOnVideoMap ( game->videomap, "2.   AVOID THE CATS!", 21, 2, 10, 0 );

				/* CAT*/
				setVideoMapTile ( game->videomap, 98, 7, 12 );
				setVideoMapTile ( game->videomap, 99, 8, 12 );
				setVideoMapTile ( game->videomap, 134, 7, 13 );
				setVideoMapTile ( game->videomap, 135, 8, 13 );

				/* RIGHT ARROW */
				setVideoMapTile ( game->videomap, 174, 11, 12 );
				setVideoMapTile ( game->videomap, 175, 12, 12 );
				setVideoMapTile ( game->videomap, 210, 11, 13 );
				setVideoMapTile ( game->videomap, 211, 12, 13 );

				/* MOUSE */
				setVideoMapTile ( game->videomap, 82, 15, 12 );
				setVideoMapTile ( game->videomap, 83, 16, 12 );
				setVideoMapTile ( game->videomap, 118, 15, 13 );
				setVideoMapTile ( game->videomap, 119, 16, 13 );
				break;

			case 4:
				/* display messages  */
				putStringOnVideoMap ( game->videomap, "3.   GRAB A COFFEE FOR A BOOST.", 32, 2, 15, 0 );

				/* MOUSE*/
				setVideoMapTile ( game->videomap, 80, 7, 17 );
				setVideoMapTile ( game->videomap, 81, 8, 17 );
				setVideoMapTile ( game->videomap, 116, 7, 18 );
				setVideoMapTile ( game->videomap, 117, 8, 18 );

				/* RIGHT ARROW */
				setVideoMapTile ( game->videomap, 174, 11, 17 );
				setVideoMapTile ( game->videomap, 175, 12, 17 );
				setVideoMapTile ( game->videomap, 210, 11, 18 );
				setVideoMapTile ( game->videomap, 211, 12, 18 );

				/* COFFEE */
				setVideoMapTile ( game->videomap, 150, 15, 17 );
				setVideoMapTile ( game->videomap, 151, 16, 17 );
				setVideoMapTile ( game->videomap, 186, 15, 18 );
				setVideoMapTile ( game->videomap, 187, 16, 18 );
				break;

			case 5:
				/* display messages  */
				putStringOnVideoMap ( game->videomap, "4.   COLLECT BONUS ITEMS.", 26, 2, 20, 0 );

				/* MOUSE*/
				setVideoMapTile ( game->videomap, 80, 7, 22 );
				setVideoMapTile ( game->videomap, 81, 8, 22 );
				setVideoMapTile ( game->videomap, 116, 7, 23 );
				setVideoMapTile ( game->videomap, 117, 8, 23 );

				/* RIGHT ARROW */
				setVideoMapTile ( game->videomap, 174, 11, 22 );
				setVideoMapTile ( game->videomap, 175, 12, 22 );
				setVideoMapTile ( game->videomap, 210, 11, 23 );
				setVideoMapTile ( game->videomap, 211, 12, 23 );

				/* BONUS ITEM */
				setVideoMapTile ( game->videomap, 234, 15, 22 );
				setVideoMapTile ( game->videomap, 235, 16, 22 );
				setVideoMapTile ( game->videomap, 270, 15, 23 );
				setVideoMapTile ( game->videomap, 271, 16, 23 );
				break;
			}
		}
		else
		{
			game->title->timer_step_message--;
		}
}






void updateGameStateTitleTertiary ( struct Game *game )
{
	/* check if button A has been pressed */
	if ( game->input->BUTTON_A == 1 )
	{
		game->input->BUTTON_A = 0;
		setAndInitializeGameState ( game, STATE_GAME_TITLE_PRIMARY );
	}

		/* if timout, display messages, or exit */
	if ( game->title->timer_step_message == 0 )
	{
		game->title->step_message++;
		if ( game->title->step_message < 7 )
		{
			game->title->timer_step_message = TIMEOUT_TITLE_STEP_MESSAGE;
		}
		else
		{
			game->title->timer_step_message = TIMEOUT_TITLE_STEP_MESSAGE * 2;
		}

		switch ( game->title->step_message )
		{
			default:
				setAndInitializeGameState ( game, STATE_GAME_TITLE_QUATERNARY );
				break;

			case 1:
				/* display messages  */
				putStringOnVideoMap ( game->videomap, "POINTS:", 8, 2, 2, 0 );
				break;

			case 2:
				/* display messages  */
				putStringOnVideoMap ( game->videomap, "CHEESE ................ 5", 26, 7, 5, 0 );
				
				/* CHEESE */
				setVideoMapTile ( game->videomap, 72, 4, 4 );
				setVideoMapTile ( game->videomap, 73, 5, 4 );
				setVideoMapTile ( game->videomap, 108, 4, 5 );
				setVideoMapTile ( game->videomap, 109, 5, 5 );
				break;

			case 3:
				/* display messages  */
				putStringOnVideoMap ( game->videomap, "COFFEE ............... 50", 26, 7, 8, 0 );
				
				/* COFFEE */
				setVideoMapTile ( game->videomap, 150, 4, 7 );
				setVideoMapTile ( game->videomap, 151, 5, 7 );
				setVideoMapTile ( game->videomap, 186, 4, 8 );
				setVideoMapTile ( game->videomap, 187, 5, 8 );
				break;

			case 4:
				/* display messages  */
				putStringOnVideoMap ( game->videomap, "BONUS ITEM ......... 1000", 26, 7, 11, 0 );

				/* BONUS ITEM */
				setVideoMapTile ( game->videomap, 234, 4, 10 );
				setVideoMapTile ( game->videomap, 235, 5, 10 );
				setVideoMapTile ( game->videomap, 270, 4, 11 );
				setVideoMapTile ( game->videomap, 271, 5, 11 );
				break;

			case 5:
				/* display messages  */
				putStringOnVideoMap ( game->videomap, "STAGE COMPLETION ....... 100", 29, 4, 14, 0 );
				break;

			case 6:
				/* display messages  */
				putStringOnVideoMap ( game->videomap, "STAGE COMPLETION WITH", 22, 4, 16, 0 );
				putStringOnVideoMap ( game->videomap, "NO COFFEE CONSUMED .... 2500", 29, 4, 17, 0 );
				break;

			case 7:
				/* display messages  */
				putStringOnVideoMap ( game->videomap, "EXTRA LIFE AWARDED", 19, 4, 22, 0 );
				putStringOnVideoMap ( game->videomap, "EVERY 10000 POINTS.", 20, 4, 23, 0 );
				break;
		}
	}
	else
	{
		game->title->timer_step_message--;
	}
}



void updateGameStateTitleQuaternary ( struct Game *game )
{
	/* check if button A has been pressed */
	if ( game->input->BUTTON_A == 1 )
	{
		game->input->BUTTON_A = 0;
		setAndInitializeGameState ( game, STATE_GAME_TITLE_PRIMARY );
	}

	/* if timout, display messages, or exit */
	if ( game->title->timer_step_message == 0 )
	{
		game->title->step_message++;
		if ( game->title->step_message < 7 )
		{
			game->title->timer_step_message = TIMEOUT_TITLE_STEP_MESSAGE;
		}
		else
		{
			game->title->timer_step_message = TIMEOUT_TITLE_STEP_MESSAGE * 2;
		}

		switch ( game->title->step_message )
		{
			default:
				setAndInitializeGameState ( game, STATE_GAME_TITLE_PRIMARY );
				break;

			case 1:
				/* display messages  */
				putStringOnVideoMap ( game->videomap, "CONTROLS:", 10, 2, 2, 0 );
				break;

			case 2:
				/* display messages  */
				putStringOnVideoMap ( game->videomap, "KEY", 4, 20, 4, 0 );
				putStringOnVideoMap ( game->videomap, "GAMEPAD", 8, 27, 4, 0 );
				putStringOnVideoMap ( game->videomap, "MOVE", 5, 2, 7, 0 );
				setVideoMapTile ( game->videomap, 55, 21, 6 ); /* W */
				setVideoMapTile ( game->videomap, 33, 20, 7 ); /* A */
				setVideoMapTile ( game->videomap, 217, 21, 7 ); /* DPAD PLUS */
				setVideoMapTile ( game->videomap, 36, 22, 7 ); /* D */
				setVideoMapTile ( game->videomap, 51, 21, 8 ); /* S */
				setVideoMapTile ( game->videomap, 258, 30, 6 ); /* U ARROW */
				setVideoMapTile ( game->videomap, 256, 29, 7 ); /* L ARROW */
				setVideoMapTile ( game->videomap, 217, 30, 7 ); /* DPAD PLUS */
				setVideoMapTile ( game->videomap, 257, 31, 7 ); /* R ARROW */
				setVideoMapTile ( game->videomap, 259, 30, 8 ); /* D ARROW */
				break;

			case 3:
				/* display messages  */
				putStringOnVideoMap ( game->videomap, "SELECT", 7, 2, 10, 0 );
				setVideoMapTile ( game->videomap, 58, 21, 10 ); /* Z */
				setVideoMapTile ( game->videomap, 252, 30, 10 ); /* BUTTON A */
				break;

			case 4:
				/* display messages  */
				putStringOnVideoMap ( game->videomap, "SCREENSHOT", 11, 2, 13, 0 );
				setVideoMapTile ( game->videomap, 54, 21, 13 ); /* V */
				setVideoMapTile ( game->videomap, 255, 30, 13 ); /* BUTTON Y */
				break;

			case 5:
				/* display messages  */
				putStringOnVideoMap ( game->videomap, "CHANGE PALETTE", 15, 2, 16, 0 );
				setVideoMapTile ( game->videomap, 12, 20, 16 ); /* , */
				setVideoMapTile ( game->videomap, 14, 22, 16 ); /* . */
				setVideoMapTile ( game->videomap, 262, 28, 16 ); /* BUTTON LEFT 1 */
				setVideoMapTile ( game->videomap, 263, 29, 16 ); /* BUTTON LEFT 2 */
				setVideoMapTile ( game->videomap, 264, 31, 16 ); /* BUTTON RIGHT 1 */
				setVideoMapTile ( game->videomap, 265, 32, 16 ); /* BUTTON RIGHT 2 */
				break;

			case 6:
				/* display messages  */
				putStringOnVideoMap ( game->videomap, "PAUSE / RESUME", 15, 2, 19, 0 );
				putStringOnVideoMap ( game->videomap, "TAB", 4, 20, 19, 0 );
				setVideoMapTile ( game->videomap, 260, 30, 19 ); /* BUTTON GUIDE */
				break;

			case 7:
				/* display messages  */
				putStringOnVideoMap ( game->videomap, "EXIT GAME", 10, 2, 24, 0 );
				putStringOnVideoMap ( game->videomap, "ESC", 4, 20, 24, 0 );
				break;

		}
	}
	else
	{
		game->title->timer_step_message--;
	}
}



void drawTitleBorder ( struct Game *game )
{
	uint16_t i;



	/* draw top and bottom borders */
	for ( i = 0; i < game->videomap->w; i++ )
	{
		setVideoMapTile ( game->videomap, 74, i, 0 );
		setVideoMapTile ( game->videomap, 74, i, game->videomap->h - 1 );
	}

	/* draw right and left borders */
	for ( i = 1; i < game->videomap->h - 1; i++ )
	{
		setVideoMapTile ( game->videomap, 74, 0, i );
		setVideoMapTile ( game->videomap, 74, game->videomap->w - 1, i );
	}
}