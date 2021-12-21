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



#include "score.h"



void setAndInitializeScoreBoard ( struct Game *game )
{
        /* display score*/
        putStringOnVideoMap ( game->videomap, "SCORE ", 7, 0, 0, 0 );
        updateScoreOnScoreBoard ( game );

        /* display cheese remaining count */
        setVideoMapTile ( game->videomap, 68, 19, 0 );
        setVideoMapTile ( game->videomap, 69, 20, 0 );
        updateCheeseOnScoreBoard ( game );

        /* display remaining meeces */
        setVideoMapTile ( game->videomap, 70, 26, 0 );
        setVideoMapTile ( game->videomap, 69, 27, 0 );
        updateMiceOnScoreBoard ( game );

        /* display stage number */
        setVideoMapTile ( game->videomap, 71, 33, 0 );
        updateStageOnScoreBoard ( game );
}



void updateScoreOnScoreBoard ( struct Game *game )
{
        putIntOnVideoMap ( game->videomap, game->score, 6, 6, 0, 0, 16 );
}



void updateMiceOnScoreBoard ( struct Game *game )
{
        putIntOnVideoMap ( game->videomap, game->remaining_mice, 2, 28, 0, 0, 16 );
}



void updateStageOnScoreBoard ( struct Game *game )
{
        putIntOnVideoMap ( game->videomap, ( game->stage->stage_number + 1 ), 2, 34, 0, 0, 16 );
}



void updateCheeseOnScoreBoard ( struct Game *game )
{
        putIntOnVideoMap ( game->videomap, game->remaining_cheese, 2, 21, 0, 0, 16 );
}