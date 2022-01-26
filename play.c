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



#include "play.h"



void setAndInitializeGameStatePlay ( struct Game *game )
{
        setAndInitializeMouse ( game );
        setAndInitializeCats ( game );
        setAndInitializeCoffee ( game );
        setAndInitializeBonus ( game );
        game->state = STATE_GAME_PLAY;
}



void updateGameStatePlay ( struct Game *game )
{
        if ( game->paused == 0 )
        {
                /* UPDATE THINGS */
                updatePlayer ( game );
                updateCats ( game );
                if ( updateCoffeeState ( game ) == 1 )
                {
                        /* if coffee is done with effect, revert cats speed to normal */
                        setCatsVelocity ( game, VELOCITY_CATS_NORMAL );
                }
                if ( updateBonusState ( game ) == 1 )
                {
                        setCatsVelocity ( game, VELOCITY_CATS_NORMAL );
                }

                /* CHECK THINGS */
                if ( game->remaining_cheese == 0 )
                {
                        setAndInitializeGameState ( game, STATE_GAME_STAGE_COMPLETE );
                }
                else
                {
                        /* ... if not, check for collisions */
                        collisionCheck ( game );
                }
        }
        /* RENDER THINGS */
        renderBonus ( game );
        renderCoffee ( game );
        renderCats ( game );
        renderMouse ( game );
}



void updatePlayer ( struct Game *game )
{
        /* if mouse is idle, and we have input, lets see if we can act on it */
        if ( game->mouse->state == STATE_MOUSE_IDLE )
        {
                /* check if DPAD UP is ACTIVE */
                if ( game->input->DPAD_UP == 1 )
                {
                        if ( checkMouseMove ( game, UP ) == 1 )
                        {
                                setAndInitializeMouseStateMovingUp ( game );
                        }
                }
                else if ( game->input->DPAD_RIGHT == 1 )
                {
                        if ( checkMouseMove ( game, RIGHT ) == 1 )
                        {
                                setAndInitializeMouseStateMovingRight ( game );
                        }
                }
                else if ( game->input->DPAD_DOWN == 1 )
                {
                        if ( checkMouseMove ( game, DOWN ) == 1 )
                        {
                                setAndInitializeMouseStateMovingDown ( game );
                        }
                }
                else if ( game->input->DPAD_LEFT == 1 )
                {
                        if ( checkMouseMove ( game, LEFT ) == 1 )
                        {
                                setAndInitializeMouseStateMovingLeft ( game );
                        }
                }

                else;
        }

        /* check if the mouse ate a cheese */
        if ( updateMouseState ( game ) == 1 )
        {
                if ( getPlayfieldCell ( game->stage->playfield, game->mouse->playfield_position.x, game->mouse->playfield_position.y ) == TILE_CHEESE )
                {
                        setPlayfieldCell ( game->stage->playfield, game->mouse->playfield_position.x, game->mouse->playfield_position.y, TILE_FLOOR );
                        subtractCheese ( game );
                        game->total_cheese_eaten++;
                        addPoints ( game, POINTS_CHEESE );
                        copyPlayfieldCellToVideoMap ( game->stage->playfield, game->mouse->playfield_position.x, game->mouse->playfield_position.y, game->videomap, game->stage->wall_tile );
                        playSound ( game->audio, SFX_EAT, 0, 128 );
                }
        }
}



void collisionCheck ( struct Game *game )
{
        collisionCheckMouseVCoffee ( game );
        collisionCheckMouseVBonus ( game );
        collisionCheckMouseVCats ( game );
}



void collisionCheckMouseVCoffee ( struct Game *game )
{
        /* mouse vs. coffee */
        if ( game->coffee->state == STATE_COFFEE_SHOWN )
        {
                if ( SDL_HasIntersection ( &game->mouse->collision_box, &game->coffee->collision_box ) == SDL_TRUE )
                {
                        nextCoffeeState ( game );
                        /* if bonus effect was active, lets cancel that */
                        if ( game->bonus->state == STATE_BONUS_EFFECT )
                        {
                                nextBonusState ( game );
                        }
                        game->coffee_flag = 1;
                        addPoints ( game, POINTS_COFFEE );
                        setCatsVelocity ( game, VELOCITY_CATS_SLOW );
                        playSound ( game->audio, SFX_COFFEE, 0, 128 );
                }
        }
}



void collisionCheckMouseVBonus( struct Game *game )
{
        /* mouse vs. bonus */
        if ( game->bonus->state == STATE_BONUS_SHOWN )
        {
                if ( SDL_HasIntersection ( &game->mouse->collision_box, &game->bonus->collision_box ) == SDL_TRUE )
                {
                        nextBonusState ( game );
                        if ( game->coffee->state == STATE_COFFEE_EFFECT )
                        {
                                nextCoffeeState ( game );
                        }
                        addPoints ( game, POINTS_BONUS );
                        setCatsVelocity ( game, VELOCITY_CATS_FAST);
                        playSound ( game->audio, SFX_BONUS, 0, 128 );
                }
        }
}



void collisionCheckMouseVCats ( struct Game *game )
{
        uint8_t i;



        for ( i = 0; i < NUMBER_OF_CATS; i++ )
        {
                if ( SDL_HasIntersection ( &game->mouse->collision_box, &game->cats [ i ]->collision_box ) == SDL_TRUE )
                {
                        setAndInitializeGameState ( game, STATE_GAME_DEATH );
                }
        }
}