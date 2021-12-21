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



#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include "game.h"



int main ( int argc, char **argv )
{
	struct Game *game;
	time_t current_time;



	/* initialize SDL2 */
	if ( SDL_Init ( SDL_INIT_EVERYTHING ) < 0 )
	{
		printf ( "SDL2 did not initialize.\n" );
		printf ( "%s\n", SDL_GetError ( ) );
		return 1;
	}
	printf ( "SDL initialized.\n" );

	/* initialize random seed */
	current_time = time ( NULL );
	srand ( ( int32_t ) current_time );
	printf ( "Seed: %lld\n", ( long long int ) current_time );

	/* create game structure  */
	game = NULL;
	game = createGame ( );
	if ( game != NULL )
	{
		printf ( "Game created.\nRunning game.\n" );

		/* run game  */
		runGame ( game );
		
		/* destroy game structure  */
		destroyGame ( game );
		printf ( "Game destroyed.\n" );
	}
	else
	{
		printf ( "Game not created.\n" );
	}

	/* exit SDL2 */
	SDL_Quit ( );
	printf ( "SDL exited.\n" );

	return 0;
}
