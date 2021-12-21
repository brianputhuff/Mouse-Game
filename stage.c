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



#include "stage.h"



struct Playfield *createPlayfield ( uint8_t width, uint8_t height )
{
        uint8_t *data;
        uint16_t a;
        struct Playfield *playfield;



        if ( ( width == 0 ) || ( height == 0 ) )
        {
                return NULL;
        }

        a = width * height;
        data = NULL;
        data = malloc ( sizeof ( uint8_t ) * a );
        if ( data == NULL )
        {
                return NULL;
        }

        playfield = NULL;
        playfield = malloc ( sizeof ( struct Playfield ) );
        if ( playfield == NULL )
        {
                free ( data );
                return NULL;
        }

        playfield->a = a;
        playfield->w = width;
        playfield->h = height;
        playfield->data = data;
        initializeSnail ( &playfield->snail );

        return playfield;
}



void destroyPlayfield ( struct Playfield *playfield )
{
        if ( playfield == NULL )
        {
                /* NO BUENO */
                return;
        }

        free ( playfield->data );
        free ( playfield );
}



void generatePlayfield ( struct Playfield *playfield )
{
        uint8_t x;
        uint8_t y;
        uint8_t i;
        uint8_t exception;



        x = 0;
        y = 0;
        exception = 0;

        /* generate walls */
        for ( i = 0; i < WALLS_TO_GENERATE_PER_STAGE; i++ )
        {
                do
                {
                        x = ( rand ( ) % ( playfield->w - 2 ) ) + 1;
                        y = ( rand ( ) % ( playfield->h - 2 ) ) + 1;

                        if ( playfield->data [ ( y * playfield->w ) + x ] == TILE_WALL )
                        {
                                exception = 1;
                        }
                        else if ( verifyCornersAreClear ( playfield, ( ( y * playfield->w ) + x ) ) == 0 )
                        {
                                exception = 1;
                        }
                        else if ( ( ( ( y * playfield->w ) + x ) == 116 ) || ( ( ( y * playfield->w ) + x ) == 117 ) )
                        {
                                exception = 1;
                        }
                        else if ( greatWallHorizontalCheck ( playfield, x, y ) == 1 )
                        {
                                exception = 1;
                        }
                        else if ( greatWallVerticalCheck ( playfield, x, y ) == 1 )
                        {
                                exception = 1;
                        }
                        else
                        {
                                exception = 0;
                        }

                } while ( exception == 1 );
                setPlayfieldCell ( playfield, x, y, TILE_WALL );
        }

        /* border walls */
        for ( y = 0; y < 13; y++ )
        {
                setPlayfieldCell ( playfield, 0, y, TILE_WALL );
                setPlayfieldCell ( playfield, playfield->w - 1, y, TILE_WALL );
        }

        for ( x = 1; x < 17; x++ )
        {
                setPlayfieldCell ( playfield, x, 0, TILE_WALL );
                setPlayfieldCell ( playfield, x, ( playfield->h - 1 ), TILE_WALL );
        }

        /* generate cheese */
        for ( i = 0; i < CHEESE_TO_EAT_PER_STAGE; i++ )
        {
                do
                {
                        x = ( rand ( ) % ( playfield->w - 2 ) ) + 1;
                        y = ( rand ( ) % ( playfield->h - 2 ) ) + 1;

                        if ( getPlayfieldCell ( playfield, x, y ) == TILE_WALL )
                        {
                                exception = 1;
                        }
                        else if ( getPlayfieldCell ( playfield, x, y ) == TILE_CHEESE )
                        {
                                exception = 1;
                        }
                        else if ( ( ( ( y * playfield->w ) + x ) == 116 ) || ( ( ( y * playfield->w ) + x ) == 117 ) )
                        {
                                exception = 1;
                        }
                        else
                        {
                                exception = 0;
                        }

                } while ( exception == 1 );
                setPlayfieldCell ( playfield, x, y, TILE_CHEESE );
        }
}



uint8_t verifyCornersAreClear ( struct Playfield *playfield, uint16_t i )
{
        if ( playfield->data [ i - ( playfield->w + 1 ) ] == TILE_WALL )
        {
                return 0;
        }

        if ( playfield->data [ i - ( playfield->w - 1 ) ] == TILE_WALL )
        {
                return 0;
        }

        if ( playfield->data [ i + ( playfield->w - 1 ) ] == TILE_WALL )
        {
                return 0;
        }

        if ( playfield->data [ i + ( playfield->w + 1 ) ] == TILE_WALL )
        {
                return 0;
        }

        return 1;
}



void initializeSnail ( struct Snail *snail )
{
        snail->i = 0;
        snail->counter = TIMEOUT_SNAIL_UPDATE;
        snail->direction = RIGHT;
        snail->node.x = 0;
        snail->node.y = 0;
        snail->shift.x = 0;
        snail->shift.y = 0;
}



uint8_t updateSnail ( struct Game *game )
{
        if ( game->stage->playfield->snail.counter == 0 )
        {
                game->stage->playfield->snail.i++;

                copyPlayfieldCellToVideoMap
                (
                        game->stage->playfield,
                        game->stage->playfield->snail.node.x,
                        game->stage->playfield->snail.node.y,
                        game->videomap,
                        game->stage->wall_tile
                );

                if ( game->stage->playfield->snail.i == 235 )
                {
                        return 1;
                }

                switch ( game->stage->playfield->snail.direction )
                {
                        case RIGHT:
                                game->stage->playfield->snail.node.x++;
                                if ( game->stage->playfield->snail.node.x == game->stage->playfield->w - 1 - game->stage->playfield->snail.shift.x )
                                {
                                        game->stage->playfield->snail.direction = DOWN;
                                        game->stage->playfield->snail.counter = TIMEOUT_SNAIL_UPDATE;
                                }
                                break;

                        case DOWN:
                                game->stage->playfield->snail.node.y++;
                                if ( game->stage->playfield->snail.node.y == game->stage->playfield->h - 1 - game->stage->playfield->snail.shift.y )
                                {
                                        game->stage->playfield->snail.shift.y++;
                                        game->stage->playfield->snail.direction = LEFT;
                                        game->stage->playfield->snail.counter = TIMEOUT_SNAIL_UPDATE;
                                }
                                break;

                        case LEFT:
                                game->stage->playfield->snail.node.x--;
                                if ( game->stage->playfield->snail.node.x == game->stage->playfield->snail.shift.x )
                                {
                                        game->stage->playfield->snail.shift.x++;
                                        game->stage->playfield->snail.direction = UP;
                                        game->stage->playfield->snail.counter = TIMEOUT_SNAIL_UPDATE;
                                }
                                break;

                        case UP:
                                game->stage->playfield->snail.node.y--;
                                if ( game->stage->playfield->snail.node.y == game->stage->playfield->snail.shift.y )
                                {
                                        game->stage->playfield->snail.direction = RIGHT;
                                        game->stage->playfield->snail.counter = TIMEOUT_SNAIL_UPDATE;
                                }
                                break;

                        default:
                                break;
                }

        }
        else
        {
                game->stage->playfield->snail.counter--;
        }

        return 0;
}



void copyPlayFieldToVideoMap ( struct Playfield *playfield, struct VideoMap *videomap, uint8_t wall_type )
{
        uint8_t r;
        uint8_t c;



        for ( r = 0; r < playfield->h; r++ )
        {
                for ( c = 0; c < playfield->w; c++ )
                {
                        copyPlayfieldCellToVideoMap ( playfield, c, r, videomap, wall_type );
                }
        }
}



void copyPlayfieldCellToVideoMap ( struct Playfield *playfield, uint16_t px, uint16_t py, struct VideoMap *videomap, uint8_t wall_type )
{
        if ( ( videomap == NULL ) || ( playfield == NULL ) || ( px >= playfield->w ) || ( py >= playfield->h ) )
        {
                return;
        }

        switch ( playfield->data [ ( py * playfield->w ) + px ] )
        {
                case TILE_WALL:
                        switch ( wall_type )
                        {
                                default:
                                case 0:
                                        setVideoMapTile ( videomap, 748, ( px * 2 ), ( py * 2 ) + 1 );
                                        setVideoMapTile ( videomap, 749, ( px * 2 ) + 1, ( py * 2 ) + 1 );
                                        setVideoMapTile ( videomap, 784, ( px * 2 ), ( py * 2 ) + 2 );
                                        setVideoMapTile ( videomap, 785, ( px * 2 ) + 1, ( py * 2 ) + 2 );
                                        break;
                                case 1:
                                        setVideoMapTile ( videomap, 750, ( px * 2 ), ( py * 2 ) + 1 );
                                        setVideoMapTile ( videomap, 751, ( px * 2 ) + 1, ( py * 2 ) + 1 );
                                        setVideoMapTile ( videomap, 786, ( px * 2 ), ( py * 2 ) + 2 );
                                        setVideoMapTile ( videomap, 787, ( px * 2 ) + 1, ( py * 2 ) + 2 );
                                        break;
                                case 2:
                                        setVideoMapTile ( videomap, 752, ( px * 2 ), ( py * 2 ) + 1 );
                                        setVideoMapTile ( videomap, 753, ( px * 2 ) + 1, ( py * 2 ) + 1 );
                                        setVideoMapTile ( videomap, 788, ( px * 2 ), ( py * 2 ) + 2 );
                                        setVideoMapTile ( videomap, 789, ( px * 2 ) + 1, ( py * 2 ) + 2 );
                                        break;
                                case 3:
                                        setVideoMapTile ( videomap, 754, ( px * 2 ), ( py * 2 ) + 1 );
                                        setVideoMapTile ( videomap, 755, ( px * 2 ) + 1, ( py * 2 ) + 1 );
                                        setVideoMapTile ( videomap, 790, ( px * 2 ), ( py * 2 ) + 2 );
                                        setVideoMapTile ( videomap, 791, ( px * 2 ) + 1, ( py * 2 ) + 2 );
                                        break;
                        }
                        break;

                case TILE_CHEESE:
                        setVideoMapTile ( videomap, 72, ( px * 2 ), ( py * 2 ) + 1 );
                        setVideoMapTile ( videomap, 73, ( px * 2 ) + 1, ( py * 2 ) + 1 );
                        setVideoMapTile ( videomap, 108, ( px * 2 ), ( py * 2 ) + 2 );
                        setVideoMapTile ( videomap, 109, ( px * 2 ) + 1, ( py * 2 ) + 2 );
                        break;

                case TILE_FLOOR:
                        setVideoMapTile ( videomap, 0, ( px * 2 ), ( py * 2 ) + 1 );
                        setVideoMapTile ( videomap, 0, ( px * 2 ) + 1, ( py * 2 ) + 1 );
                        setVideoMapTile ( videomap, 0, ( px * 2 ), ( py * 2 ) + 2 );
                        setVideoMapTile ( videomap, 0, ( px * 2 ) + 1, ( py * 2 ) + 2 );
                        break;

                case TILE_BONUS:
                        setVideoMapTile ( videomap, 692, ( px * 2 ), ( py * 2 ) + 1 );
                        setVideoMapTile ( videomap, 693, ( px * 2 ) + 1, ( py * 2 ) + 1 );
                        setVideoMapTile ( videomap, 728, ( px * 2 ), ( py * 2 ) + 2 );
                        setVideoMapTile ( videomap, 729, ( px * 2 ) + 1, ( py * 2 ) + 2 );
                        break;

                default:
                        break;
        }
}



uint8_t getPlayfieldCell ( struct Playfield *playfield, uint16_t x, uint16_t y )
{
        if ( ( playfield == NULL ) || ( x >= playfield->w ) || ( y >= playfield->h ) )
        {
                return 0;
        }

        return ( playfield->data [ ( playfield->w * y ) + x ] );
}



void setPlayfieldCell ( struct Playfield *playfield, uint16_t x, uint16_t y, uint8_t value )
{
        if ( ( playfield == NULL ) || ( x >= playfield->w ) || ( y >= playfield->h ) )
        {
                return;
        }

        playfield->data [ ( playfield->w * y ) + x ] = value;
}




void clearPlayfield ( struct Playfield *playfield )
{
        uint32_t i;



        if ( playfield == NULL )
        {
                return;
        }

        for ( i = 0; i < playfield->a; i++ )
        {
                playfield->data [ i ] = TILE_FLOOR;
        }
}




uint8_t greatWallHorizontalCheck ( struct Playfield *playfield, uint16_t x, uint16_t y )
{
        uint16_t i;



        for ( i = 0; i < playfield->w; i++ )
        {
                if ( i != x )
                {
                        if ( getPlayfieldCell ( playfield, i, y ) == TILE_FLOOR )
                        {
                                return 0;
                        }
                }
        }

        return 1;
}



uint8_t greatWallVerticalCheck ( struct Playfield *playfield, uint16_t x, uint16_t y )
{
        uint16_t i;



        for ( i = 0; i < playfield->h; i++ )
        {
                if ( i != y )
                {
                        if ( getPlayfieldCell ( playfield, x, i ) == TILE_FLOOR )
                        {
                                return 0;
                        }
                }
        }

        return 1;
}



void setAndInitializeGameStateStageIn ( struct Game *game )
{
        /* clear screen */
        setAllVideoMapTiles ( game->videomap, 0 );

        /* reset stage data */
        game->remaining_cheese = CHEESE_TO_EAT_PER_STAGE;
        setAndInitializeScoreBoard ( game );
        if ( game->stage->stage_number > 0 )
        {
                playSound ( game->audio, SFX_STAGE, 0, 128 );
        }

        /* change wall tile, if applicable */
        if ( ( game->stage->stage_number != 0 ) && game->stage->stage_number % 4 == 0 )
        {
                game->stage->wall_tile++;
                if ( game->stage->wall_tile == 4 )
                {
                        game->stage->wall_tile = 0;
                }
        }

        /* generate playfield */
        /* NOTE: must be done after mouse resets but before cats reset */
        generatePlayfield ( game->stage->playfield );
        initializeSnail ( &game->stage->playfield->snail );

        /* start BGM if not already playing */
        if ( Mix_PlayingMusic ( ) == 0 )
        {
                playMusic ( game->audio, game->stage->bgm, -1, 128 );
        }
}



struct Stage *createStage ( void )
{
        struct Stage *stage;



        stage = NULL;
        stage = malloc ( sizeof ( struct Stage ) );
        if ( stage == NULL )
        {
                return NULL;
        }
        
        stage->stage_number = 0;
        stage->playfield = createPlayfield ( 18, 13 );
        stage->wall_tile = 0;
        stage->bgm = 0;

        return stage;
}



void destroyStage ( struct Stage *stage )
{
        if ( stage == NULL )
        {
                return;
        }

        destroyPlayfield ( stage->playfield );
        free ( stage );
}



void setAndInitializeGameStateStageOut ( struct Game *game )
{
        clearPlayfield ( game->stage->playfield );
        initializeSnail ( &game->stage->playfield->snail );
        if ( ( game->stage->stage_number + 1 ) % 4 == 0 )
        {
                /* next track */
                game->stage->bgm++;
                if ( game->stage->bgm == MUS_ENDING )
                {
                        game->stage->bgm = MUS_BGM_1;
                }
                fadeOutMusic ( AUDIO_FADE_RATE_SLOW );
        }
}



void setAndInitializeGameStateStageComplete ( struct Game *game )
{
        setAndInitializeMouseStateDancing ( game );
        setAndInitializeCatsStateSleeping ( game );
        playSound ( game->audio, SFX_COMPLETE, 0, 128 );
}



void updateGameStateStageIn ( struct Game *game )
{
        if ( updateSnail ( game ) == 1 )
        {
                setAndInitializeGameState ( game, STATE_GAME_PLAY );
        }
}



void updateGameStateStageOut ( struct Game *game )
{

        if ( updateSnail ( game ) == 1 )
        {
                addStage ( game );
                if ( game->stage->stage_number == NUMBER_OF_STAGES )
                {
                        setAndInitializeGameState ( game, STATE_GAME_ENDING );
                }
                else
                {
                        setAndInitializeGameState ( game, STATE_GAME_STAGE_IN );
                }
        }
}



void updateGameStateStageComplete ( struct Game *game )
{
        if ( updateMouseState ( game ) == 1 )
        {
                if ( game->coffee->state == STATE_COFFEE_DONE )
                {
                        addPoints ( game, POINTS_STAGE_COMPLETE );
                        playSound ( game->audio, SFX_STAGE_COMPLETE_BONUS, 0, 128 );
                }
                else
                {
                        addPoints ( game, POINTS_STAGE_COMPLETE_NO_COFFEE );
                        playSound ( game->audio, SFX_NO_COFFEE_BONUS, 0, 128 );
                }
                setAndInitializeGameState ( game, STATE_GAME_STAGE_OUT );
        }
        else
        {
                /* update other objects */
                updateCats ( game );
                updateCoffeeState ( game );

                /* render objects */
                renderBonus ( game );
                renderCoffee ( game );
                renderCats ( game );
                renderMouse ( game ); 
        }
}
