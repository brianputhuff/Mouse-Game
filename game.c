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



#include "game.h"



struct Game *createGame ( void )
{
	uint8_t i;
	struct Game *game;



	game = NULL;
	game = malloc ( sizeof ( struct Game ) );
	if ( game == NULL )
	{
		return NULL;
	}
	
	/* allocate system structs */
	game->audio = createAudio ( );
	game->graphics = createGraphics ( );
	game->input = createInput ( );

	/* allocate resource structs */
	game->animationsequences = createAnimationSequences ( 33 );
	game->spritebatch = createSpriteBatch ( );
	game->sprites = createSprites ( );
	game->tiles = createTiles ( );
	game->videomap = createVideoMap ( 36, 27 );

	/* allocate object structs */
	game->mouse = createMOB ( );
	for ( i = 0; i < NUMBER_OF_CATS; i++ )
	{
		game->cats [ i ] = createMOB ( );
	}
	game->coffee = createMOB ( );
	game->bonus = createMOB ( );
	game->stage = createStage ( );

	/* allocate state objects */
	game->title = createTitle ( );

	/* initializers */
	initializeSprites ( game->sprites );
	initializeAnimationSequences ( game->animationsequences );

	return game;
}



void destroyGame ( struct Game *game )
{
	uint8_t i;



	if ( game == NULL )
	{
		return;
	}

	destroyAudio ( game->audio );
	destroyGraphics ( game->graphics );
	destroyInput ( game->input );
	destroyAnimationSequences ( game->animationsequences );
	destroySpriteBatch ( game->spritebatch );
	destroySprites ( game->sprites );
	destroyTiles ( game->tiles );
	destroyVideoMap ( game->videomap );
	destroyStage ( game->stage );
	destroyTitle ( game->title );
	destroyMOB ( game->bonus );
	destroyMOB ( game->coffee );
	destroyMOB ( game->mouse );
	for ( i = 0; i < NUMBER_OF_CATS; i++ )
	{
		destroyMOB ( game->cats [ i ] );
	}

	free ( game );
}



void runGame ( struct Game *game )
{
	uint8_t is_running;
	uint32_t timer;
	uint32_t delta;

	/* set initial start state */
	setAndInitializeGameState ( game, STATE_GAME_VERSION );

	is_running = 1;
	timer = SDL_GetTicks ( );
	while ( is_running == 1 )
	{
		delta = SDL_GetTicks ( ) - timer;
		if ( delta >= 16 )
		{
			/* update input */
			updateInputRegisters ( game->input );

			/* main exit option */
			if ( game->input->ESCAPE == 1 )
			{
				is_running = 0;
			}

			/* palette cycle */
			if ( game->input->BUTTON_R == 1 )
			{
				game->input->BUTTON_R = 0;
				game->graphics->palette++;
				if ( game->graphics->palette == NUMBER_OF_PALETTES )
				{
					game->graphics->palette = 0;
				}
			}

			if ( game->input->BUTTON_L == 1 )
			{
				game->input->BUTTON_L = 0;
				if ( game->graphics->palette > 0 )
				{
					game->graphics->palette--;
				}
				else
				{
					game->graphics->palette = ( NUMBER_OF_PALETTES - 1 );
				}
			}

			if ( game->input->TAB == 1 )
			{
				if ( game->state == STATE_GAME_PLAY )
				{
					game->input->TAB = 0;
					game->paused = !( game->paused );
				}
			}

			if ( game->input->BUTTON_Y == 1 )
			{
				game->input->BUTTON_Y = 0;
				screenShot ( game->graphics );
			}

			/* update game state */
			updateGameState ( game );

			/* render the things */
			renderGame ( game );
			timer = SDL_GetTicks ( );
		}
		else
		{
			SDL_Delay ( 16 - delta );
		}
	}
}


void testGame ( struct Game *game )
{
	updateCoffeeState ( game );
	renderCoffee ( game );
}



void initializeSprites ( struct Sprites *sprites )
{
	/* MOUSE MOVING UP */
	/* main: 000, 002 */
	/* mask: 001, 003 */
	/* 000, 001: frame 1 */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 610, 611, 646, 647 ) ); /* main */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 682, 683, 718, 719 ) ); /* mask */

	/* 002, 003: frame 2 */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 608, 609, 644, 645 ) ); /* main */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 680, 681, 716, 717 ) ); /* mask */

	/* MOUSE MOVING RIGHT */
	/* main: 004, 006 */
	/* mask: 005, 007 */
	/* 004, 005: frame 1 */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 80, 81, 116, 117 ) ); /* main */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 88, 89, 124, 125 ) ); /* mask */

	/* 006, 007: frame 2 */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 82, 83, 118, 119 ) ); /* main */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 90, 91, 126, 127 ) ); /* mask */

	/* MOUSE MOVING DOWN */
	/* main: 008, 010 */
	/* mask: 009, 011 */
	/* 008, 009: frame 1 */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 606, 607, 642, 643 ) ); /* main */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 678, 679, 714, 715 ) ); /* mask */

	/* 010, 011: frame 2 */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 604, 605, 640, 641 ) ); /* main */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 676, 677, 712, 713 ) ); /* mask */

	/* MOUSE MOVING LEFT*/
	/* main: 012, 014 */
	/* mask: 013, 015 */
	/* 012, 013; frame 1 */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 76, 77, 112, 113 ) ); /* main */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 84, 85, 120, 121 ) ); /* mask */

	/* 014, 015; frame 2 */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 78, 79, 114, 115 ) ); /* main */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 86, 87, 122, 123 ) ); /* mask */

	/* MOUSE DANCING */
	/* main: 016, 018 */
	/* mask: 017, 019 */
	/* 016, 017; frame 1 */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 156, 157, 192, 193 ) ); /* main */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 160, 161, 196, 197 ) ); /* mask */

	/* 018, 019; frame 2 */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 158, 159, 194, 195 ) ); /* main */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 162, 163, 198, 199 ) ); /* mask */

	/* MOUSE DEATH LEFT */
	/* main: 020, 022, 024, 026, 028, 030, 032, 034 */
	/* mask: 021, 023, 025, 027, 029, 031, 033, 035 */
	/* 020, 021; frame 1 */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 308, 309, 344, 345 ) ); /* main */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 380, 381, 416, 417 ) ); /* mask */

	/* 022, 023; frame 2 */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 310, 311, 346, 347 ) ); /* main */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 382, 383, 418, 419 ) ); /* mask */

	/* 024, 025; frame 3 */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 312, 313, 348, 349 ) ); /* main */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 384, 385, 420, 421 ) ); /* mask */

	/* 026, 027; frame 4 */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 314, 315, 350, 351 ) ); /* main */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 386, 387, 422, 423 ) ); /* mask */

	/* 028, 029; frame 5 */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 316, 317, 352, 353 ) ); /* main */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 388, 389, 424, 425 ) ); /* mask */

	/* 030, 031; frame 6 */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 318, 319, 354, 355 ) ); /* main */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 390, 391, 426, 427 ) ); /* mask */

	/* 032, 033; frame 7 */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 320, 321, 356, 357 ) ); /* main */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 392, 393, 428, 429 ) ); /* mask */

	/* 034, 035; frame 8 */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 322, 323, 358, 359 ) ); /* main */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 394, 395, 430, 431 ) ); /* mask */

	/* MOUSE DEATH RIGHT */
	/* main: 036, 038, 040, 042, 044, 046, 048, 050 */
	/* mask: 037, 039, 041, 043, 045, 047, 049, 051 */
	/* 036, 037; frame 1 */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 452, 453, 488, 489 ) ); /* main */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 524, 525, 560, 561 ) ); /* mask */

	/* 038, 039; frame 2 */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 454, 455, 490, 491 ) ); /* main */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 526, 527, 562, 563 ) ); /* mask */

	/* 040, 041; frame 3 */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 456, 457, 492, 493 ) ); /* main */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 528, 529, 564, 565 ) ); /* mask */

	/* 042, 043; frame 4 */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 458, 459, 494, 495 ) ); /* main */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 530, 531, 566, 567 ) ); /* mask */

	/* 044, 045; frame 5 */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 460, 461, 496, 497 ) ); /* main */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 532, 533, 568, 569 ) ); /* mask */

	/* 046, 047; frame 6 */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 462, 463, 498, 499 ) ); /* main */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 534, 535, 570, 571 ) ); /* mask */

	/* 048, 049; frame 7 */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 464, 465, 500, 501 ) ); /* main */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 536, 537, 572, 573 ) ); /* mask */

	/* 050, 051; frame 8 */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 466, 467, 502, 503 ) ); /* main */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 538, 539, 574, 575 ) ); /* mask */

	/* COFFEE */
	/* coffee frames: 052 - 057 */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 144, 145, 180, 181 ) );
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 146, 147, 182, 183 ) );
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 148, 149, 184, 185 ) );
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 150, 151, 186, 187 ) );
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 152, 153, 188, 189 ) );
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 154, 155, 190, 191 ) );

	/* BONUS */
	/* 058, 059; bonus type 1: floppy disk */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 234, 235, 270, 271 ) ); /* main */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 236, 237, 272, 273 ) ); /* mask */
	
	/* 060, 061; bonus type 2: kaiju toy */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 238, 239, 274, 275 ) ); /* main */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 240, 241, 276, 277 ) ); /* mask */

	/* 062, 063; bonus type 3: headset */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 242, 243, 278, 279 ) ); /* main */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 244, 245, 280, 281 ) ); /* mask */

	/* 064, 065; bonus type 4: joystick */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 246, 247, 282, 283 ) ); /* main */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 248, 249, 284, 285 ) ); /* mask */

	/* CAT LEFT */
	/* main: 066, 068 */
	/* mask: 067, 069 */
	/* 66, 67; cat left frame 1 */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 92, 93, 128, 129 ) ); /* main */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 100, 101, 136, 137 ) ); /* mask */

	/* 68, 69; cat left frame 2 */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 94, 95, 130, 131 ) ); /* main */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 102, 103, 138, 139 ) ); /* mask */

	/* CAT RIGHT */
	/* main: 070, 072 */
	/* mask: 071, 073 */
	/* 70, 71; cat right frame 1 */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 96, 97, 132, 133 ) ); /* main */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 104, 105, 140, 141 ) ); /* mask */

	/* 72, 73; cat right frame 2 */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 98, 99, 134, 135 ) ); /* main */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 106, 107, 142, 143 ) ); /* mask */

	/* CAT DANCING */
	/* main: 074, 076 */
	/* mask: 075, 077 */
	/* 74, 75; cat dance frame 1 */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 164, 165, 200, 201 ) ); /* main */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 168, 169, 204, 205 ) ); /* mask */

	/* 76, 77; cat dance frame 2 */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 166, 167, 202, 203 ) ); /* main */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 170, 171, 206, 207 ) ); /* mask */

	/* CAT SLEEPING LEFT */
	/* main: 078, 080, 082, 084, 086, 088, 090, 092, 094, 096 */
	/* mask: 079, 081, 083, 085, 087, 089, 091, 093, 095, 097 */
	/* 78, 79; cat sleeping left frame 1 */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 432, 433, 468, 469 ) ); /* main */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 504, 505, 540, 541 ) ); /* mask */

	/* 80, 81; cat sleeping left frame 2 */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 434, 435, 470, 471 ) ); /* main */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 506, 507, 542, 543 ) ); /* mask */

	/* 82, 83; cat sleeping left frame 3 */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 436, 437, 472, 473 ) ); /* main */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 508, 509, 544, 545 ) ); /* mask */

	/* 84, 85; cat sleeping left frame 4 */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 438, 439, 474, 475 ) ); /* main */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 510, 511, 546, 547 ) ); /* mask */

	/* 86, 87; cat sleeping left frame 5 */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 440, 441, 476, 477 ) ); /* main */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 512, 513, 548, 549 ) ); /* mask */

	/* 88, 89; cat sleeping left frame 6 */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 442, 443, 478, 479 ) ); /* main */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 514, 515, 550, 551 ) ); /* mask */

	/* 90, 91; cat sleeping left frame 7 */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 444, 445, 480, 481 ) ); /* main */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 516, 517, 552, 553 ) ); /* mask */

	/* 92, 93; cat sleeping left frame 8 */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 446, 447, 482, 483 ) ); /* main */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 518, 519, 554, 555 ) ); /* mask */

	/* 94, 95; cat sleeping left frame 9 */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 448, 449, 484, 485 ) ); /* main */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 520, 521, 556, 557 ) ); /* mask */

	/* 96, 97; cat sleeping left frame 10 */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 450, 451, 486, 487 ) ); /* main */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 522, 523, 558, 559 ) ); /* mask */

	/* CAT SLEEPING RIGHT */
	/* main: 098, 100, 102, 104, 106, 108, 110, 112, 114, 116 */
	/* mask: 099, 101, 103, 105, 107, 109, 111, 113, 115, 117 */
	/* 98, 99; cat sleeping right frame 1 */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 288, 289, 324, 325 ) ); /* main */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 360, 361, 396, 397 ) ); /* mask */

	/* 100, 101; cat sleeping right frame 2 */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 290, 291, 326, 327 ) ); /* main */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 362, 363, 398, 399 ) ); /* mask */

	/* 102, 103; cat sleeping right frame 3 */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 292, 293, 328, 329 ) ); /* main */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 364, 365, 400, 401 ) ); /* mask */

	/* 104, 105; cat sleeping right frame 4 */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 294, 295, 330, 331 ) ); /* main */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 366, 367, 402, 403 ) ); /* mask */

	/* 106, 107; cat sleeping right frame 5 */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 296, 297, 332, 333 ) ); /* main */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 368, 369, 404, 405 ) ); /* mask */

	/* 108, 109; cat sleeping right frame 6 */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 298, 299, 334, 335 ) ); /* main */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 370, 371, 406, 407 ) ); /* mask */

	/* 110, 111; cat sleeping right frame 7 */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 300, 301, 336, 337 ) ); /* main */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 372, 373, 408, 409 ) ); /* mask */

	/* 112, 113; cat sleeping right frame 8 */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 302, 303, 338, 339 ) ); /* main */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 374, 375, 410, 411 ) ); /* mask */

	/* 114, 115; cat sleeping right frame 9 */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 304, 305, 340, 341 ) ); /* main */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 376, 377, 412, 413 ) ); /* mask */

	/* 116, 117; cat sleeping right frame 10 */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 306, 307, 342, 343 ) ); /* main */
	addSpriteToSprites ( sprites, createSprite ( 2, 2, 378, 379, 414, 415 ) ); /* mask */
}



void initializeAnimationSequences ( struct AnimationSequences *animationsequences )
{
	/* MOUSE MOVING UP */
	/* 0 (main), 1 (mask) */
	setAnimationSequence ( animationsequences, 0, createSequence ( 2, 0, 2 ) ); /* main */
	setAnimationSequence ( animationsequences, 1, createSequence ( 2, 1, 3 ) ); /* mask */

	/* MOUSE MOVING RIGHT */
	/* 2 (main), 3 (mask) */
	setAnimationSequence ( animationsequences, 2, createSequence ( 2, 4, 6 ) ); /* main */
	setAnimationSequence ( animationsequences, 3, createSequence ( 2, 5, 7 ) ); /* mask */

	/* MOUSE MOVING DOWN */
	/* 4 (main), 5 (mask) */
	setAnimationSequence ( animationsequences, 4, createSequence ( 2, 8, 10 ) ); /* main */
	setAnimationSequence ( animationsequences, 5, createSequence ( 2, 9, 11 ) ); /* mask */

	/* MOUSE MOVING LEFT */
	/* 6 (main), 7 (mask) */
	setAnimationSequence ( animationsequences, 6, createSequence ( 2, 12, 14 ) ); /* main */
	setAnimationSequence ( animationsequences, 7, createSequence ( 2, 13, 15 ) ); /* mask */

	/* MOUSE DANCING */
	/* 8 (main), 9 (mask) */
	setAnimationSequence ( animationsequences, 8, createSequence ( 2, 16, 18 ) ); /* main */
	setAnimationSequence ( animationsequences, 9, createSequence ( 2, 17, 19 ) ); /* mask */

	/* MOUSE DEATH LEFT */
	/* 10 (main), 11 (mask) */
	setAnimationSequence ( animationsequences, 10, createSequence ( 8, 20, 22, 24, 26, 28, 30, 32, 34 ) ); /* main */
	setAnimationSequence ( animationsequences, 11, createSequence ( 8, 21, 23, 25, 27, 29, 31, 33, 35 ) ); /* mask */

	/* MOUSE DEATH RIGHT */
	/* 12 (main), 13 (mask) */
	setAnimationSequence ( animationsequences, 12, createSequence ( 8, 36, 38, 40, 42, 44, 46, 48, 50 ) ); /* main */
	setAnimationSequence ( animationsequences, 13, createSequence ( 8, 37, 39, 41, 43, 45, 47, 49, 51 ) ); /* mask */

	/* 14 COFFEE */
	setAnimationSequence ( animationsequences, 14, createSequence ( 6, 52, 53, 54, 55, 56, 57 ) );

	/* BONUS TYPE 1 */
	/* 15 (main), 16 (mask) */
	setAnimationSequence ( animationsequences, 15, createSequence ( 1, 58 ) ); /* main */
	setAnimationSequence ( animationsequences, 16, createSequence ( 1, 59 ) ); /* mask */

	/* BONUS TYPE 2 */
	/* 17 (main), 18 (mask) */
	setAnimationSequence ( animationsequences, 17, createSequence ( 1, 60 ) ); /* main */
	setAnimationSequence ( animationsequences, 18, createSequence ( 1, 61 ) ); /* mask */

	/* BONUS TYPE 3 */
	/* 19 (main), 20 (mask) */
	setAnimationSequence ( animationsequences, 19, createSequence ( 1, 62 ) ); /* main */
	setAnimationSequence ( animationsequences, 20, createSequence ( 1, 63 ) ); /* mask */

	/* BONUS TYPE 4 */
	/* 21 (main), 22 (mask) */
	setAnimationSequence ( animationsequences, 21, createSequence ( 1, 64 ) ); /* main */
	setAnimationSequence ( animationsequences, 22, createSequence ( 1, 65 ) ); /* mask */

	/* CAT LEFT */
	/* 23 (main), 24 (mask) */
	setAnimationSequence ( animationsequences, 23, createSequence ( 2, 66, 68 ) ); /* main */
	setAnimationSequence ( animationsequences, 24, createSequence ( 2, 67, 69 ) ); /* mask */

	/* CAT RIGHT */
	/* 25 (main), 26 (mask) */
	setAnimationSequence ( animationsequences, 25, createSequence ( 2, 70, 72 ) ); /* main */
	setAnimationSequence ( animationsequences, 26, createSequence ( 2, 71, 73 ) ); /* mask */

	/* CAT DANCING */
	/* 27 (main), 28 (mask) */
	setAnimationSequence ( animationsequences, 27, createSequence ( 2, 74, 76 ) ); /* main */
	setAnimationSequence ( animationsequences, 28, createSequence ( 2, 75, 77 ) ); /* mask */

	/* CAT SLEEPING LEFT */
	/* 29 (main), 30 (mask) */
	setAnimationSequence ( animationsequences, 29, createSequence ( 10, 78, 80, 82, 84, 86, 88, 90, 92, 94, 96 ) ); /* main */
	setAnimationSequence ( animationsequences, 30, createSequence ( 10, 79, 81, 83, 85, 87, 89, 91, 93, 95, 97 ) ); /* mask */

	/* CAT SLEEPING RIGHT */
	/* 31 (main), 32 (mask) */
	setAnimationSequence ( animationsequences, 31, createSequence ( 10, 98, 100, 102, 104, 106, 108, 110, 112, 114, 116 ) ); /* main */
	setAnimationSequence ( animationsequences, 32, createSequence ( 10, 99, 101, 103, 105, 107, 109, 111, 113, 115, 117 ) ); /* mask */
}



void setAndInitializeGameState ( struct Game *game, uint8_t state )
{
	game->state = state;
	switch ( state )
	{
		default:
			break;

		case STATE_GAME_TITLE_PRIMARY:
			setAndInitializeGameStateTitlePrimary ( game );
			break;

		case STATE_GAME_TITLE_SECONDARY:
			setAndInitializeGameStateTitleSecondary ( game );
			break;

		case STATE_GAME_TITLE_TERTIARY:
			setAndInitializeGameStateTitleTertiary( game );
			break;

		case STATE_GAME_TITLE_QUATERNARY:
			setAndInitializeGameStateTitleQuaternary ( game );
			break;

		case STATE_GAME_STAGE_IN:
			setAndInitializeGameStateStageIn ( game );
			break;

		case STATE_GAME_PLAY:
			setAndInitializeGameStatePlay ( game );
			break;

		case STATE_GAME_STAGE_COMPLETE:
			setAndInitializeGameStateStageComplete ( game );
			break;

		case STATE_GAME_STAGE_OUT:
			setAndInitializeGameStateStageOut ( game );
			break;

		case STATE_GAME_DEATH:
			setAndInitializeGameStateDeath ( game );
			break;

		case STATE_GAME_GAME_OVER:
			setAndInitializeGameStateGameOver ( game );
			break;

		case STATE_GAME_ENDING:
			setAndInitializeGameStateEnding ( game );
			break;	

		case STATE_GAME_VERSION:
			setAndInitializeGameStateVersion ( game );
			break;
	}
}



void updateGameState ( struct Game *game )
{
	switch ( game->state )
	{
		default:
			testGame ( game );
			break;

		case STATE_GAME_TITLE_PRIMARY:
			updateGameStateTitlePrimary ( game );
			break;

		case STATE_GAME_TITLE_SECONDARY:
			updateGameStateTitleSecondary ( game );
			break;

		case STATE_GAME_TITLE_TERTIARY:
			updateGameStateTitleTertiary ( game );
			break;

		case STATE_GAME_TITLE_QUATERNARY:
			updateGameStateTitleQuaternary ( game );
			break;

		case STATE_GAME_STAGE_IN:
			updateGameStateStageIn ( game );
			break;

		case STATE_GAME_PLAY:
			updateGameStatePlay ( game );
			break;

		case STATE_GAME_STAGE_COMPLETE:
			updateGameStateStageComplete ( game );
			break;

		case STATE_GAME_STAGE_OUT:
			updateGameStateStageOut ( game );
			break;

		case STATE_GAME_DEATH:
			updateGameStateDeath ( game );
			break;

		case STATE_GAME_GAME_OVER:
			updateGameStateGameOver ( game );
			break;

		case STATE_GAME_ENDING:
			updateGameStateEnding ( game );
			break;

		case STATE_GAME_VERSION:
			updateGameStateVersion ( game );
			break;
	}
}



void newGame ( struct Game *game )
{
	game->paused = 0;
	game->score = 0;
	game->remaining_mice = DATA_START_REMAINING_MICE;
	game->remaining_cheese = CHEESE_TO_EAT_PER_STAGE;
	game->total_cheese_eaten = 0;
	game->coffee_flag = 0;
	game->extra_mouse = EXTRA_MOUSE;
	
	game->stage->wall_tile = 0;
	game->stage->bgm = MUS_BGM_1;
	game->stage->stage_number = 0;
	clearPlayfield ( game->stage->playfield );
}



void addPoints ( struct Game *game, uint32_t points )
{
	/* update score */
	game->score += points;
	updateScoreOnScoreBoard ( game );

	/* check to see if extra life target is met */
	if ( game->score >= game->extra_mouse )
	{
		game->extra_mouse += EXTRA_MOUSE;
		addMouse ( game );
		playSound ( game->audio, SFX_ONE_UP, 0, 128 );
	}
}



void addMouse ( struct Game *game )
{
	game->remaining_mice++;
	updateMiceOnScoreBoard ( game );
}



void subtractMouse ( struct Game *game )
{
	game->remaining_mice--;
	updateMiceOnScoreBoard ( game );
}



void addStage ( struct Game *game )
{
	game->stage->stage_number++;
	updateStageOnScoreBoard ( game );
}



void subtractCheese ( struct Game *game )
{
	game->remaining_cheese--;
	updateCheeseOnScoreBoard ( game );
}



void setAndInitializeGameStateVersion ( struct Game *game )
{
	/* display version */
	putStringOnVideoMap ( game->videomap, "MOUSE GAME", 11, 4, 6, 0 );
	putStringOnVideoMap ( game->videomap, "VERSION", 7, 4, 7, 0 );
	putStringOnVideoMap ( game->videomap, "--.--.--", 9, 13, 7, 0 );
	putIntOnVideoMap ( game->videomap, VERSION_MAJOR, 2, 13, 7, 0, 16 );
	putIntOnVideoMap ( game->videomap, VERSION_MINOR, 2, 16, 7, 0, 16 );
	putIntOnVideoMap ( game->videomap, VERSION_PATCH, 2, 19, 7, 0, 16 );

	if ( VERSION_MAJOR < 1 )
	{
		putStringOnVideoMap ( game->videomap, "BETA VERSION", 13, 4, 9, 0 );
	}
	else
	{
		putStringOnVideoMap ( game->videomap, "RELEASE VERSION", 16, 4, 9, 0 );
	}
	game->timer = TIMEOUT_VERSION_DISPLAY;
}



void updateGameStateVersion ( struct Game *game )
{
	if ( game->timer == 0 )
	{
		setAndInitializeGameState ( game, STATE_GAME_TITLE_PRIMARY );
	}
	else
	{
		game->timer--;
	}
}
